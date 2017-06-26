// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
//


#include <time.h>
#include <stdio.h>
#include <vector>

#include "gSLICr_Lib/gSLICr.h"
#include "NVTimer.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
//Functions
#include "func_sm.hpp"



#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace gSLICr::objects;
using namespace gSLICr::engines;
using namespace gSLICr;
using namespace std;
using namespace cv;

void load_image(const Mat& inimg, gSLICr::UChar4Image* outimg)
{
	gSLICr::Vector4u* outimg_ptr = outimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < outimg->noDims.y;y++)
		for (int x = 0; x < outimg->noDims.x; x++)
		{
			int idx = x + y * outimg->noDims.x;
			outimg_ptr[idx].b = inimg.at<Vec3b>(y, x)[0];
			outimg_ptr[idx].g = inimg.at<Vec3b>(y, x)[1];
			outimg_ptr[idx].r = inimg.at<Vec3b>(y, x)[2];
		}
}

void load_image(const gSLICr::UChar4Image* inimg, Mat& outimg)
{
	const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < inimg->noDims.y; y++)
		for (int x = 0; x < inimg->noDims.x; x++)
		{
			int idx = x + y * inimg->noDims.x;
			outimg.at<Vec3b>(y, x)[0] = inimg_ptr[idx].b;
			outimg.at<Vec3b>(y, x)[1] = inimg_ptr[idx].g;
			outimg.at<Vec3b>(y, x)[2] = inimg_ptr[idx].r;
		}
}


int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cerr << "unable to open camera!\n";
		return -1;
	}


	// gSLICr settings
	gSLICr::objects::settings my_settings;
	my_settings.img_size.x = 640;
	my_settings.img_size.y = 480;
	my_settings.no_segs = 2000;
	my_settings.spixel_size = 32;
	my_settings.coh_weight = 0.6f;
	my_settings.no_iters = 5;
	my_settings.color_space = gSLICr::XYZ; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
	my_settings.seg_method = gSLICr::GIVEN_SIZE; // or gSLICr::GIVEN_NUM for given number
	my_settings.do_enforce_connectivity = false; // whether or not run the enforce connectivity step


	// instantiate a core_engine
	gSLICr::engines::core_engine* gSLICr_engine = new gSLICr::engines::core_engine(my_settings);




	int spixel_size = my_settings.spixel_size;
	int spixel_per_col = (int)ceil(my_settings.img_size.x / spixel_size);
	int spixel_per_row = (int)ceil(my_settings.img_size.y / spixel_size);


	int width  = my_settings.img_size.x;
	int height = my_settings.img_size.y;
	//am_sz is the number of superpixels
	int am_sz = spixel_per_col*spixel_per_row;
	int im_sz = width*height;

	int *adj_mat = new int[am_sz*am_sz];



	// gSLICr takes gSLICr::UChar4Image as input and out put
	gSLICr::UChar4Image* in_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
	gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);

	Size s(my_settings.img_size.x, my_settings.img_size.y);
	Mat oldFrame, frame;
	Mat boundry_draw_frame; boundry_draw_frame.create(s, CV_8UC3);
	Mat labels;
    Mat frame2(Size(width,height),CV_8UC3);

    StopWatchInterface *my_timer; sdkCreateTimer(&my_timer);
    //Reserve memory space for labels m*n
    const gSLICr::IntImage* Idx_im;

    const int* data_ptr;
    int* data_ptr2;

    cv::namedWindow("SLIC prueba", WINDOW_AUTOSIZE);


    //adj_mat outs the adjacency matrix
    adjacency_mat(adj_mat, am_sz,spixel_per_col);
	ofstream lol;

/*
	lol.open("labels.csv");
	for(int dd=0;dd<am_sz;dd++){
		for(int ff=0; ff<am_sz; ff++){
			lol<< adj_mat[dd*am_sz+ff]<<",";
		}
		lol<<endl;


	}
	lol.close();*/

    //CONNECTIONS
    vector<vector<int>> conn_com;
    vector<int> kxy;
    vector<int> kr;
    vector<int> kg;
    vector<int> kb;
    vector<vector<int>> tails;
	vector<double> avg_r;
	vector<double> avg_g;
	vector<double> avg_b;

    int group;

    int n_sp;

	char key; int save_count = 0;

	while (cap.read(oldFrame)&&(key!='q'))
	{

		resize(oldFrame, frame, s);
		//gSLICr::objects::spixel_info

		load_image(frame, in_img);

		gSLICr_engine->Process_Frame(in_img);

        gSLICr_engine->Draw_Segmentation_Result(out_img);
     //LABELS
        Idx_im = gSLICr_engine->Get_Seg_Res();

        data_ptr = Idx_im->GetData(MEMORYDEVICE_CPU);


        create_connection_ref_mat(conn_com, am_sz);

        vector<vector<int>> fillmat (300);


        find_sp_coordinates(data_ptr, im_sz, kxy,n_sp, fillmat);


        if (n_sp==300){

            extract_colours(frame, kxy, kr, kg, kb, width);


            fill_connection_mat(adj_mat, conn_com, tails, data_ptr,am_sz,group,kr,kg, kb);


            execute_connections(group, tails, height, width, data_ptr, frame, avg_r, avg_g, avg_b, kxy);

        	sdkResetTimer(&my_timer); sdkStartTimer(&my_timer);
            fill_tool(frame2, tails, data_ptr, height, width, avg_r, avg_g, avg_b,fillmat);
            sdkStopTimer(&my_timer);
            cout<<"\rsegmentation in:["<<sdkGetTimerValue(&my_timer)<<"]ms"<<flush;

        }

        //Clean All
        fillmat.clear();
        conn_com.clear();
        tails.clear();
        kxy.clear();
        kr.clear();
        kg.clear();
        kb.clear();
       	avg_r.clear();
       	avg_g.clear();
       	avg_b.clear();

        //Falta vaciar conexxiones


		load_image(out_img, boundry_draw_frame);
		//imshow("SLIC prueba", boundry_draw_frame);
		imshow("SLIC prueba", frame2);

		key = waitKey(1);
		if (key == 's')
		{

			char out_name[100];
			sprintf(out_name, "seg_%04i.pgm", save_count);
			gSLICr_engine->Write_Seg_Res_To_PGM(out_name);
			sprintf(out_name, "edge_%04i.png", save_count);
			imwrite(out_name, boundry_draw_frame);
			sprintf(out_name, "img_%04i.png", save_count);
			imwrite(out_name, frame);
			printf("\nsaved segmentation %04i\n", save_count);
			save_count++;
		}
	}

	destroyAllWindows();
	conn_com.clear();
    return 0;
}

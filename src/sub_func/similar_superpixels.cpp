#include <vector>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


void execute_connections(
		int& 					group_i,
		vector<vector<int>>& 	tails,
		int& 					height,
		int& 					width,
		const int* 				klabels,
		Mat&					img,
		vector<double>&			avg_r,
		vector<double>&			avg_g,
		vector<double>&			avg_b,
		vector<int>&			kxy
		)
{

	double avg_lac=0;
	double avg_aac=0;
	double avg_bac=0;

	double tempcolor;

	int den;
	int seed;



	for (int i=0; i<(group_i-1); i++){
		//cout<<"Group: "<<i<<"|  ";
		den=tails[i].size();
		int conti=0;
		for(int j=0; j<den;j++){
			for(int i_1=0; i_1<15;i_1++){
				for(int j_1=0; j_1<20; j_1++){
					int ij=i_1*20+j_1;
					seed=kxy[ij];
					int col=seed%width;
					int row=seed/width;
					if(klabels[seed]==tails[i][j]){
						avg_lac=int(img.at<Vec3b>(row,col)[0])+avg_lac;
						avg_aac=int(img.at<Vec3b>(row,col)[1])+avg_aac;
						avg_bac=int(img.at<Vec3b>(row,col)[2])+avg_bac;
						conti++;
					}
				}
			}

		}

		tempcolor=avg_lac/conti;
		avg_r.push_back(tempcolor);
		tempcolor=avg_aac/conti;
		avg_g.push_back(tempcolor);
		tempcolor=avg_bac/conti;
		avg_b.push_back(tempcolor);
		avg_lac=0;
		avg_aac=0;
		avg_bac=0;
	}
}

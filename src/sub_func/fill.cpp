#include <vector>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <iomanip>


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void fill_tool(
		Mat&					img_seg2,
		vector<vector<int>>& 	tails,
		const int*				klabels,
		int&					height,
		int&					width,
		vector<double>& 		avg_r,
		vector<double>& 		avg_g,
		vector<double>& 		avg_b,
		vector<vector<int>>&	fillmat

		)
{

	int sp_size,pix, col, row, super_pixel;

	for(int SP=0; SP < tails.size(); SP++){
		for(int spi=0; spi<tails[SP].size();spi++){
			super_pixel=tails[SP][spi];
			sp_size=fillmat[super_pixel].size();
			for(int i=0; i<sp_size; i++){
				pix=fillmat[super_pixel][i];
				col=pix%width;
				row=pix/width;
				img_seg2.at<Vec3b>(row,col)[0] = avg_r[SP];
				img_seg2.at<Vec3b>(row,col)[1] = avg_g[SP];
				img_seg2.at<Vec3b>(row,col)[2] = avg_b[SP];
			}
		}
	}
}

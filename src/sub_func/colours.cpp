#include <time.h>
#include <stdio.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void extract_colours(
		Mat& 			img,
		vector<int>& 	kxy,
		vector<int>& 	kr,
		vector<int>&	kg,
		vector<int>&	kb,
		int& width
		)
{
	int sz=kxy.size();
	int col,row;

	for (int i=0; i<sz; i++){
		col=kxy[i]%width;
		row=kxy[i]/width;
		kb.push_back(img.at<Vec3b>(row,col)[0]);
		kg.push_back(img.at<Vec3b>(row,col)[1]);
		kr.push_back(img.at<Vec3b>(row,col)[2]);
	}
}

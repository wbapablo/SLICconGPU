//int ad_mat[k][k];
	//ad_mat-> adjacency matrix
	//k - > number of superpixels
	//rk -> number of columns
using namespace std;
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;


void adjacency_mat(int* ad_mat,int k, int rk);

void create_connection_ref_mat(vector<vector<int>>& con_mat, int k);

void find_sp_coordinates(const int* klabels,int& im_sz, vector<int>& kxy,  int& n_sp,  vector<vector<int>>&fillmat);

void extract_colours(
		Mat& 			img,
		vector<int>& 	kxy,
		vector<int>& 	kr,
		vector<int>&	kg,
		vector<int>&	kb,
		int& width
		);

void fill_connection_mat(
		int*						ad_mat,//cambiar el formato
		vector<vector<int>>& 		conexiones,
		vector<vector<int>>& 		tails,
		const int* 					klabels,
		int& 						numlabels,
		int& 						group_i,
		vector<int>& 				kr,//l
		vector<int>&				kg,//a
		vector<int>&				kb//b
		);

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
		);

void fill_tool(
		Mat&					img_seg2,
		vector<vector<int>>& 	tails,
		const int*					klabels,
		int&					height,
		int&					width,
		vector<double>& 		avg_r,
		vector<double>& 		avg_g,
		vector<double>& 		avg_b,
		vector<vector<int>>&	fillmat
		);



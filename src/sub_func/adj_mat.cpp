


#include <time.h>
#include <stdio.h>


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
//#include "func_sm.hpp"



void adjacency_mat(int* ad_mat,int k, int rk){
   	//int ad_mat[k][k];
	//ad_mat-> adjacency matrix
	//k - > number of superpixels
	//rk -> number of columns

	//Adjacency Matrix

	for(int i=0; i<k;i++){
		for(int j=0; j<k;j++){
			ad_mat[i*k+j]=0;
		}
	}
	//Fill The Adjacency Matrix Accordingly, this one works only for k=80 -> 10 cols, 8 rows and under the assumption that
	//the superpixels' labels are an incremental sequence of 1
	for(int i=0; i<k; i++){
		if((i+rk)<k){
			ad_mat[i*k+(rk+i)]=1;
			ad_mat[i+k*(i+rk)]=1;
		}

		int rm = (i+1)%rk;
		if((rm!=0)){
			ad_mat[i+1+(i)*k]=1;
			ad_mat[i+k*(i+1)]=1;
		}
	}

}

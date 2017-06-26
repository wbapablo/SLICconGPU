
#include <time.h>
#include <stdio.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void find_sp_coordinates(const int* klabels,int& im_sz, vector<int>& kxy, int& n_sp, vector<vector<int>>& fillmat){
	int cont=0;
	int curr=0;

	//fillmat.clear();

	kxy.clear();

	for(int i=0; i<im_sz; i++){
		// LLenar vector, con coordenadas de súper pixeles
		curr=klabels[i];
		if(curr==cont){
			kxy.push_back(i);
			cont++;
		}
		fillmat[curr].push_back(i);
		//Necesito...vector de vectores. Cada fila contendría
		//la coordenada de todos los pixeles de cada super pixel-->fillmat
	}
	n_sp=cont;
}



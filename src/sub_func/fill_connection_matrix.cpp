#include <time.h>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;


//INS
//connection matrix empty | image | labels | group index |
//
//
//OUTS
// tails | group index
//
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
		)
{
	int sz=numlabels;
	float d_r, d_g, d_b;
	float color_d;
	int v_son;
	int th=40;
	group_i=1;

	for(int ic=0; ic < numlabels; ic++){
		if(conexiones[ic][1]==0){
			conexiones[ic][1]=1;
			conexiones[ic][2]=group_i;
			vector<int> temp;
			//Cada vector Temp contará con todos los integrantes de cada grupo
			temp.push_back(conexiones[ic][0]);
			for(int ic2=0; ic2 < temp.size() ; ic2++){
				for(int ic3=0; ic3<=40; ic3 ++ ){
					if(ic<20){//1st Zone///////////////////////////////////////////////
						if((ad_mat[temp[ic2]*sz+(temp[ic2]+ic3)]==1)&&(conexiones[temp[ic2]+ic3][1]==0)){

							d_r=kr[ic]-kr[temp[ic2]+ic3];
							d_g=kg[ic]-kg[temp[ic2]+ic3];
							d_b=kb[ic]-kb[temp[ic2]+ic3];
							color_d=sqrt(pow(d_r,2) + pow(d_g,2) + pow(d_b,2));
							if (color_d<th){
								v_son = temp[ic2]+ic3;
								temp.push_back(v_son);
								conexiones[v_son][1]=1;
								conexiones[v_son][2]=group_i;
							}
						}

					}else if((ic>=20)&&(ic<280)){//2nd ZONE ************************************
						if((ad_mat[temp[ic2]*sz+(temp[ic2]+ic3-20)]==1)&&(conexiones[temp[ic2]+ic3-20][1]==0)){
							d_r=kr[ic]-kr[temp[ic2]+ic3-20];
							d_g=kg[ic]-kg[temp[ic2]+ic3-20];
							d_b=kb[ic]-kb[temp[ic2]+ic3-20];
							color_d=sqrt(pow(d_r,2) + pow(d_g,2) + pow(d_b,2));
							if (color_d<th){
								v_son = temp[ic2]+ic3-20;
								temp.push_back(v_son);
								conexiones[v_son][1]=1;
								conexiones[v_son][2]=group_i;
							}
						}
					}else if(ic>=280){//3rd ZONE ********************************************
						if((ad_mat[temp[ic2]*sz+(temp[ic2]+1)]==1)&&(conexiones[temp[ic2]+1][1]==0)){
							d_r=kr[ic]-kr[temp[ic2]+1];
							d_g=kg[ic]-kg[temp[ic2]+1];
							d_b=kb[ic]-kb[temp[ic2]+1];
							color_d=sqrt(pow(d_r,2) + pow(d_g,2) + pow(d_b,2));
							if (color_d<th){
								v_son = temp[ic2]+1;
								temp.push_back(v_son);
								conexiones[v_son][1]=1;
								conexiones[v_son][2]=group_i;
							}
						}
					}

				}

			}
			tails.push_back(temp);
			group_i++;
		}
	}


}


#include <time.h>
#include <stdio.h>
#include <vector>

using namespace std;

//con_mat , k
void create_connection_ref_mat(vector<vector<int>>& con_mat, int k){
	for (int i=0; i<k; i++){
		vector<int> temp;
		for ( int j=0; j<3; j++){
			temp.push_back(0);
		}
		con_mat.push_back(temp);
		con_mat[i][0]=i;
		temp.clear();
	}

}

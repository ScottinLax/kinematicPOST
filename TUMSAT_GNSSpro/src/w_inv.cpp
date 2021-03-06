/////////////////////////////////////////////////////////////////////
//
// 観測誤差共分散行列を求める部分
//
////////////////////////////////////////////////////////////////////
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "global_extern.h"

int minv(double[],double,int);

void w_inv(double w1[PRN*PRN], int satn, int flag, int nsvg, int nsvb)
{
	int i,j,l,m,n,o;
	double eps;
	double std1 = Carrier_noise;//最初に設定済みの搬送波位相の雑音
	double std2 = Code_noise;//最初に設定済みの擬似距離の雑音

	eps=1.0e-25;

	for(i=0;i<satn*4*satn*4;i++)
		w1[i]=0;

	l=0;m=0;n=0,o=0;

//	/*
	if(flag==1){
		//satnは観測衛星数-1
		//L1 のみの場合、[satn*2]*[satn*2]の行列
		for(i=0;i<satn*2*satn*2;i++){
			if((i+satn*2+1)%(satn*2+1)==0){
				if(i<satn*2*satn*2/2){

					w1[i]=4*OmomiC[l];
					l++;
					if(l>nsvg){
						w1[i]=4*OmomiCB[m];
						m++;
					}

//					w1[i]=4*std1*std1*OmomiP[l];
//					l++;
//					if(l>nsvg){
//						w1[i]=4*std1*std1*OmomiC[m];
//						m++;
//					}
				}
				if(i>=satn*2*satn*2/2){

					w1[i]=4*OmomiP[n];
					n++;
					if(n>nsvg){
						w1[i]=4*OmomiPB[o];
						o++;
					}

//					w1[i]=4*std2*std2*OmomiP[n];
//					n++;
//					if(n>nsvg){
//						w1[i]=4*std2*std2*OmomiC[o];
//						o++;
//					}
				}
			}
			else if(i<satn*2*satn){
				for(j=0;j<satn;j++){
					if(i<satn+j*satn*2 && i>=j*satn*2)
						w1[i]=2*std1*std1;
				}
			}
			else if(i>=satn*2*satn && i<satn*2*satn*2){
				for(j=0;j<satn;j++){
					if(i<satn+(j+satn)*satn*2+satn && i>=(j+satn)*satn*2+satn)
						w1[i]=2*std2*std2;
				}
			}
		}
	}
//*/

/*
	if(flag==1){
		//satnは観測衛星数-1
		//L1 のみの場合、[satn*2]*[satn*2]の行列
		for(i=0;i<satn*2*satn*2;i++){
			if((i+satn*2+1)%(satn*2+1)==0){
				if(i<satn*2*satn*2/2)
					w1[i]=4*std1*std1;
				if(i>=satn*2*satn*2/2)
					w1[i]=4*std2*std2;
			}
			else if(i<satn*2*satn){
				for(j=0;j<satn;j++){
					if(i<satn+j*satn*2 && i>=j*satn*2)
						w1[i]=2*std1*std1;
				}
			}
			else if(i>=satn*2*satn && i<satn*2*satn*2){
				for(j=0;j<satn;j++){
					if(i<satn+(j+satn)*satn*2+satn && i>=(j+satn)*satn*2+satn)
						w1[i]=2*std2*std2;
				}
			}
		}
	}
	*/

	//逆行列を求める部分
	int number = satn*2;

	minv(w1,eps,number);

}

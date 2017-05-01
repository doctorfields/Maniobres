#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../../lib/hdr/qrres.h"

int main(){
	/* 	Calcula l'error màxim en x donat un sistema random Ax=b de dimensio n amb solució (1,1,...,1)	*/
	/*	Entrada:
		  -> n : dimensió del sistema
		Sortida:
		  <- n error_max
	*/
	
	int i,j,n;
	double *A,*x,*b,*dr;
	srand(time(0)); // Posa un nombre aleatori de llavor
	while(scanf("%d",&n)==1){
		A = (double *) malloc(n*n*sizeof(double));
		x = (double *) malloc(n*sizeof(double));
		b = (double *) malloc(n*sizeof(double));
		dr = (double *) malloc(n*sizeof(double));
		for(i=0;i<n;i++){
			b[i]=0;
			for(j=0;j<n;j++){
				A[i+j*n]=((double)rand())/RAND_MAX;
				b[i]+=A[i+j*n];
			}
		}
		qrres(n,n,A,dr,b,x);
		double error_max = fabs(x[0]-1.);
		for(i=0;i<n;i++){
			if(fabs(x[i]-1.) > error_max){
				error_max = fabs(x[i]-1.);
			}
		}
		printf("%d %.20E \n",n, error_max);
		free(A);free(x);free(b);free(dr);
	}
	
	return 0;
}
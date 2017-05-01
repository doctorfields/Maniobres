#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/hdr/qrres.h"

int main(){
	/* 	Calcula el temps d'execució del mètode QR per matrius aleatòries de mida n	*/
	/*	Entrada:
		  -> n : dimensió del sistema
		Sortida:
		  <- n temps rediment_efectiu
	*/
	
	int i,j,n;
	double *A,*x,*dr;
	time_t t0,t1;
	double t,rendiment_efectiu;
	srand(time(0)); // Posa un nombre aleatori de llavor
	while(scanf("%d",&n)==1){
		A = (double *) malloc(n*n*sizeof(double));
		x = (double *) malloc(n*sizeof(double));
		dr = (double *) malloc(n*sizeof(double));
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				A[i+j*n]=((double)rand())/RAND_MAX;
			}
		}
		t0 = clock();
		qrres(n,n,A,dr,NULL,x);
		t1 = clock();
		t = ((double)(t1-t0))/CLOCKS_PER_SEC;
		rendiment_efectiu = (4./3.)*n*n*n/(t*2.6*1E9);
		printf("%d %.20E %.20E\n",n, t,rendiment_efectiu);
		free(A);free(x);free(dr);
	}
	
	return 0;
}

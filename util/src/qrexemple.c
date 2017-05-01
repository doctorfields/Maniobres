#include <stdio.h>
#include "../../lib/hdr/qrres.h"

void imprimir(double *A,int n, int m){
	int i; int j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%lf ",A[i+j*n]);
		}
		printf("\n");
	}
}

void escanear(int n, int m, double A[]){
	int i; int j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%lf",&A[i+j*n]);
		}
	}
}

int main(){
	int n,m;
	printf("m = "); scanf("%d",&m);
	printf("n = "); scanf("%d",&n);
	double A[n*m]; double b[m];
	printf("Entra la matriu A de dimensio %d x %d: \n", m, n);
	escanear(m,n,A);
	printf("Entra el vector b de dimensio %d x 1: \n", m);
	escanear(m,1,b);	
	double dr[n];
	double x[n];
	qrres(m,n,A,dr,b,x);
	printf("La sortida de A es: \n");
	imprimir(A,3,2);
	printf("La sortida de b es: \n");
	imprimir(b,3,1);
	printf("La sortida de dr es: \n");
	imprimir(dr,n,1);
	printf("La sortida de x es: \n");
	imprimir(x,n,1);
	return 0;
}
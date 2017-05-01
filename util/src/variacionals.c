#include <stdio.h>
#include <string.h>
#include "../../lib/hdr/flux.h"

#define N 2

int camp(int n, double t, double *x, double *f, void *prm){
	double alpha = *((double *) prm);	
	double r2 = x[0]*x[0]+x[1]*x[1]; 
	
	f[0] = alpha*(1-r2)*x[0]-x[1];
	f[1] = x[0]+alpha*(1-r2)*x[1];
	if(n==N){
		return 0;
	}
	else{		
		double d00 = alpha*(1-3*x[0]*x[0]-x[1]*x[1]);
		double d01 = -2*alpha*x[0]*x[1]-1;
		double d10 = -2*alpha*x[0]*x[1]+1;
		double d11 = alpha*(1-3*x[1]*x[1]-x[0]*x[0]);
		
		f[2] = d00*x[2]+d01*x[3];
		f[3] = d10*x[2]+d11*x[3];
		f[4] = d00*x[4]+d01*x[5];
		f[5] = d10*x[4]+d11*x[5];
		return 0;
	}
}

int main(int argc, char *argv[]){
	/* 	Calcula derivades del flux respecte condicions inicials de dos maneres
		(per variacionals primeres i numèricament) i calcula l'error entre els dos */
	/* 	Entrada:
			- delta : diferència per fer la derivada numèrica
		Sortida:
			- "e1 e2 e3 e4" error en les 4 components de la diferencial del flux
	*/	
	
	double h0 = 1e-8; double hmin = 1e-14; double hmax = 1;
	double tol = 1e-15; int np = 1000;
	
	// Condicions inicials
	double x[N];
	x[0] = 1; x[1] = 0;
	double alpha = 0.5; double t0 = 0; double T = 0.5;
	void *prm = (void *) &alpha;
	
	double D[N*N]; // Matriu amb derivades numeriques
	double y[N+N*N]; // Solucions del sistema ampliat
	double t; double h;
	int i; int j;
	
	double delta;
	while (scanf("%lf",&delta)==1) {
	  // Derivades numèriques
	  double xtilde[N]; // Treballem amb aquest vector per no alterar les condicions inicals a x
	  double antes; double despues; // Guardem el flux amb +delta i amb -delta
	  for(i=0;i<N;i++){
		  for(j=0;j<N;j++){
			// + Delta
			memcpy(xtilde,x,N*sizeof(double));
			xtilde[j] += delta;
			t=t0; h=h0;
			flux(&t,xtilde,&h,T,hmin,hmax,tol,np,N,camp,prm);
			despues = xtilde[i];
			// - Delta
			memcpy(xtilde,x,N*sizeof(double));
			xtilde[j] -= delta;
			t=t0; h=h0;
			flux(&t,xtilde,&h,T,hmin,hmax,tol,np,N,camp,prm);
			antes = xtilde[i];
			// D
			D[i+j*N] = (despues-antes)/(2*delta);
		  }
	  }
	  
	  // Amb variacionals primeres
	  y[0] = x[0]; y[1] = x[1]; y[2] = 1; y[3] = 0; y[4] = 0; y[5] = 1;
	  t=0; h=h0;
	  flux(&t,y,&h,T,hmin,hmax,tol,np,N+N*N,camp,prm);
	  printf("%lf %lf %lf %lf\n", D[0]-y[2], D[1]-y[3], D[2]-y[4], D[3]-y[5]);
	}	
	
	return 0;	
}
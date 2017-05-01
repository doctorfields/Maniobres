#include <stdio.h>
#include "../../lib/hdr/flux.h"
#include "../../lib/hdr/lorenz.h"

int main(int argc, char *argv[]){
	/* 	Calcula nt punts equiespaiats temporalment al camp de Lorenz */
	/*	Entrada:
		  -> "x0 y0 z0"
		Sortida:
		  <- nt linies "t x y h"
	*/
		
	double parametros[3];
	double tf; int nt;		
	if (argc!=6
	  || sscanf(argv[1], "%lf", &parametros[0])!=1
	  || sscanf(argv[2], "%lf", &parametros[1])!=1
	  || sscanf(argv[3], "%lf", &parametros[2])!=1
	  || sscanf(argv[4], "%lf", &tf)!=1
	  || sscanf(argv[5], "%d", &nt)!=1
	) {
	  printf("lorenz_int sgm rho bet tf nt\n");
	  return -1;
	} void *prm = parametros;
	
	double h0 = 1e-8; double hmin = 1e-14; double hmax = 1;
	double tol = 1e-15; int np = 1000;
	double t; double x[3]; double h; double T; int i;
	while (scanf("%lf %lf %lf",&x[0],&x[1],&x[2])==3) {
	  t=0; h=h0; T = tf/nt;
	  printf("%lf %lf %lf %lf\n", t, x[0], x[1], x[2]);
	  for (i=0; i<nt; i++) {
	    flux(&t,x,&h,T,hmin,hmax,tol,np,3,lorenz,prm);
	    printf("%lf %lf %lf %lf\n", t, x[0], x[1], x[2]);
	  }
	  printf("\n\n");
	}
	
	return 0;
}
#include <stdio.h>
#include <math.h>
#include "../../lib/hdr/flux.h"

int oscilador_harmonic(int n, double t, double x[], double f[], void *prm){
	f[0] = x[1];
	f[1] = -x[0];
	return 0;
}
 
int main (int argc, char *argv[]) {
  /* Per cada línia integra el camp 'oscilador_harmonic' i dóna l'error amb la solució exacta */
  /*	Entrada:
	  -> T
	Sortida:
	  <- t x_aprox y_aprox
	  <- x_exacte y_exacte
	  <- error_x error_y
  */
  
  double hmin, hmax, tol, t, x[2], h, T;
  int npasmax;
  if (argc!=5
      || sscanf(argv[1],"%lf",&hmin)!=1
      || sscanf(argv[2],"%lf",&hmax)!=1
      || sscanf(argv[3],"%lf",&tol)!=1
      || sscanf(argv[4],"%d",&npasmax)!=1
      ) {
      fprintf(stderr, "flux_check2 hmin hmax tol\n");
      return -1;
   }
   while (scanf("%lf",&T)==1) {
      t = 0; x[0] = 0; x[1] = 1; h = 1e-8;
	  flux(&t,x,&h,T,hmin,hmax,tol,npasmax,2,oscilador_harmonic,NULL);
	  printf("%.16G %.16G %.16G\n", t, x[0],x[1]);
	  printf("%.16G %.16G\n",sin(t),cos(t));
	  printf("%.16G %.16G\n",x[0]-sin(t),x[1]-cos(t));
      printf("\n");
   }
   
   return 0;
}
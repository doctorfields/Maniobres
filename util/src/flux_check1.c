#include <stdio.h>
#include "../../lib/hdr/flux.h"
 
int quadrat(int n, double t, double x[], double f[], void *prm){
	f[0]=2*x[0]/t;
	return 0;
}

int main (int argc, char *argv[]) {
  /* Per cada línia integra el camp 'quadrat' i dóna l'error amb la solució exacta */
  /*	Entrada:
	  -> T
	Sortida:
	  <- t x_aprox
	  <- x_exacte
	  <- error
  */
	
  double hmin, hmax, tol, t, x[1], h, T;
  int npasmax;
  if (argc!=5
        || sscanf(argv[1],"%lf",&hmin)!=1
        || sscanf(argv[2],"%lf",&hmax)!=1
        || sscanf(argv[3],"%lf",&tol)!=1
	|| sscanf(argv[4],"%d",&npasmax)!=1
     ) {
     fprintf(stderr, "flux_check1 hmin hmax tol\n");
     return -1;
  }
  while (scanf("%lf",&T)==1) {
     t = 1; x[0] = 1; h = 1e-8;
     flux(&t,x,&h,T,hmin,hmax,tol,npasmax,1,quadrat,NULL);
     printf("%.16G %.16G\n", t, x[0]);
     printf("%.16G\n",t*t);
     printf("%.16G\n",x[0]-t*t);
     printf("\n");
  }
  
  return 0;
}
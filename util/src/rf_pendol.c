#include <stdio.h>
#include "../../lib/hdr/rk78.h"
#include "../../lib/hdr/pendol.h"

int main (int argc, char *argv[]) {
  /* 	Calcula np pasos del RK78 sobre el camp del pendol simple partint de t = 0 */
  /*	Entrada:
	  -> "x0 y0 h0 np"
	Sortida:
	  <- np+1 linies amb "t x y h"
  */
   
   double h0, hmin, hmax, tol, t, x[2], h;
   int np, i;
   if (argc!=4
         || sscanf(argv[1],"%lf",&hmin)!=1
         || sscanf(argv[2],"%lf",&hmax)!=1
         || sscanf(argv[3],"%lf",&tol)!=1
      ) {
      fprintf(stderr, "rf_pendol hmin hmax tol\n");
      return -1;
   }
   while (scanf("%lf %lf %lf %d",&x[0],&x[1],&h0,&np)==4) {
      t=0; h=h0;
      printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);
      for (i=0; i<np; i++) {
         rk78(&t,x,&h,hmin,hmax,tol,2,pendol,NULL);
         printf("%.16G %.16G %.16G %G\n", t, x[0], x[1], h);
      }
      printf("\n");
   }
   
   return 0;
}

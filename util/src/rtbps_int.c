#include <stdio.h>
#include "../../lib/hdr/flux.h"
#include "../../lib/hdr/rtbps.h"

int main(int argc, char *argv[]){
	/* 	Calcula nt punts equiespaiats temporalment del RTBPS */
	/*	Entrada:
			-> "x0 y0 z0 v0x v0y v0z tf nt"
		Sortida:
			<- nt linies "t x y h"
	*/
	
	double h0 = 1e-8; double hmin = 1e-14; double hmax = 1;
	double tol = 1e-15; int np = 1000;
	
	double mu;		
	if (argc!=2
	    || sscanf(argv[1], "%lf", &mu)!=1
	) {
	    printf("rtbps_int mu\n");
	    return -1;
	} void *prm = (void *) &mu;
	
	double t; double h; double T; int i;
	double x[6]; double tf; int nt;
	while (scanf("%lf %lf %lf %lf %lf %lf %lf %d",&x[0],&x[1],&x[2], &x[3], &x[4], &x[5], &tf, &nt)==8) {
	  t=0; h=h0; T = tf/nt;
	  printf("%lf %lf %lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3], x[4], x[5]);
	  for (i=0; i<nt; i++) {
	    flux(&t,x,&h,T,hmin,hmax,tol,np,6,rtbps,prm);
	    printf("%lf %lf %lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3], x[4], x[5]);
	  }
	  printf("\n\n");
	}
	
	return 0;
}
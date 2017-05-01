#include <stdio.h>
#include "../../lib/hdr/cmani.h"
#include "../../lib/hdr/rtbps.h"

int main(int argc, char *argv[]){
	/* Calcula els dv0 dv1 que envien un objecte amb condicions x0 a xf en temps dt sotmes al camp RTBP */
	/*	Entrada:
			- "dt x0 y0 z0 v0x v0y v0z xf yf zf vfx vfy vfz" : temps, condicions inicials i condicions finals
		Sortida:
			- "dv0x dv0y dv0z dv1x dv1y dv1z" : dv0 i dv1 solucions
	*/
	
	double mu; double tolnwt; int maxitnwt;	
	if (argc!=4
	  || sscanf(argv[1], "%lf", &mu)!=1
	  || sscanf(argv[2], "%lf", &tolnwt)!=1
	  || sscanf(argv[3], "%d", &maxitnwt)!=1
	) {
	  printf("cmani_rtbp mu tolnwt maxitnwt\n");
	  return -1;
	} void *prm = (void *) &mu;
	
	int m = 3; int n = 2*m;
	double x0[n], xf[n], dv[n],dt;
	double pas0=1E-8, pasmin=1E-14, pasmax=1., tolfl=1E-15, npasmx=1000;
	
	while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&dt,&x0[0],&x0[1],&x0[2],&x0[3],&x0[4],&x0[5],&xf[0],&xf[1],&xf[2],&xf[3],&xf[4],&xf[5])==13) {
	  dv[0]=0.; dv[1]=0.; dv[2]=0.; dv[3]=0.; dv[4]=0.; dv[5]=0.;
	  cmani (m, x0, xf, dt, dv, tolnwt, maxitnwt,
		pas0, pasmin, pasmax, tolfl, npasmx,
		rtbps, prm);
	  printf("%10.5E %10.5E %10.5E %10.5E %10.5E %10.5E\n",dv[0],dv[1],dv[2],dv[3],dv[4],dv[5]);
	}
	
	return 0;
}

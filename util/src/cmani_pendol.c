#include <stdio.h>
#include <math.h>
#include "../../lib/hdr/cmani.h"
#include "../../lib/hdr/pendolampliat.h"

#define PI 3.14159265358979323846264338327

int main(){
	double x0[2], xf[2], dv[2];
	x0[0]=1.; x0[1]=0.;
	xf[0]=0.; xf[1]=-sqrt(2*(1-cos(1)));
	double dt=PI/2;
	double pas0=1E-8, pasmin=1E-14, pasmax=1., tolfl=1E-15, tol=1E-14;
	int npasmx = 100, maxit=1000;
	dv[0]=0.; dv[1]=0.;
	cmani (1, x0, xf, dt, dv, tol, maxit,
		pas0, pasmin, pasmax, tolfl, npasmx,
		pendol, NULL);
	
	return 0;
}
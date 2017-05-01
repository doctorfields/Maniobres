int lorenz(int n, double t, double *x, double *f, void *prm){
	double sgm = *((double *) prm);
	double rho = *((double *) prm+1);
	double bet = *((double *) prm+2);
	
	f[0] = sgm*(x[1]-x[0]);
	f[1] = -x[0]*x[2]+rho*x[0]-x[1];
	f[2] = x[0]*x[1]-bet*x[2];
	
	return 0;
}
int flux (
	double *t, double x[], double *h,
	double T, double pasmin, double pasmax,
	double tol, int npasmx, int n,
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm);
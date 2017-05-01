#include <stdio.h>
#include <math.h>

#define SGN(x) ((x)>=0?1:-1)

void qrres (int m, int n, double *a, double *dr, double *b, double *x){
	/* Aplica la descomposicio QR a una matriu A i resol Ax=b si b != NULL */
	/* Arguments:
		- m,n : dimensions de A
		- *a : matriu A guardada per columnes
		- *dr : (sortida) diagonal de la matriu R final
		- *b : terme independent
		- *x : (sortida) solució del sistema
	*/
	
	int k; double s; double beta; double alpha; 
	int i,j;
    for(k=0;k<n;k++){
		s=0;
		for(i=k;i<m;i++){
			s += a[i+k*m]*a[i+k*m];
		}
		s = sqrt(s)*SGN(a[k+k*m]);
		beta = 1./(s*s+s*a[k+k*m]);
		a[k+k*m] += s;
		dr[k]=-s;
		for(j=k+1;j<n;j++){
			alpha=0;
			for(i=k;i<m;i++){
				alpha += a[i+k*m]*a[i+j*m];
			}
			alpha *= beta;
			for(i=k;i<m;i++){
				a[i+j*m] -= alpha*a[i+k*m];
			}
		}
		if(b != NULL){
			alpha=0;
			for(i=k;i<m;i++){
				alpha += a[i+k*m]*b[i];
			}
			alpha = alpha*beta;
			for(i=k;i<m;i++){
				b[i] -= alpha*a[i+k*m];
			}
		}
		
	}
	
	if(b != NULL){
		double cont;
		for(i=n-1;i>=0;i--){
			cont=0.;
			for(j=n-1;j>i;j--){
				cont += a[i+j*m]*x[j];
			}
			x[i] = 1./(dr[i])*(b[i]-cont);
		}
	}
	
}

#undef SGN
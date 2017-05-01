#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../hdr/flux.h"
#include "../hdr/qrres.h"

// Defineixo un producte de matrius per no sobrecarregar el codi posterior
void multiplicar(double A[],double B[],int n,int m,int p,double M[]){
	int i; int j; int k;
	for(i=0;i<n;i++){
		for(j=0;j<p;j++){
			M[i+j*n] = 0;
			for(k=0;k<m;k++){
				M[i+j*n] += A[i+k*n]*B[k+j*m];
			}
		}
	}
}

int cmani_gdg (int m, double x0[], double xf[], double dt, double dv[],
	double g[], double dg[],
	double pas0, double pasmin, double pasmax, double tolfl, int npasmx,
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm
	){

		/* 	Calcularem pas a pas les quatre etapes del vol
				Primer impuls -> Vol Lliure -> Segon impuls -> Vol lliure
			Guardarem en un vector x (dim n+n*n) la posicio, velocitat (n primeres components)
			i diferencial del flux respecte condicions inicials (les n*n seguents). Les diferencials
			del flux les calculem a partir del sistema (8) del guio (per aixo el camp ha de tenir defines
			les derivades del camp quan n > N, com a rtbps) i per aixo cada vegada que fem el flux
			hem de posar les condicions inicials de la matriu diferencial que sigui la identitat.
			
			En acabar les quatre etapes, a les n primeres components de x tindrem la posicio
			i velocitat finals, que restades amb les rf i vf (argument xf) donen la funcio G
			per al dv entrat. ---> D'aqui en guardem a g
			
			Per DG seguim la notacio del guio separant en dos blocs que anomenem D1 i D2, i.e.
			DG = ( D1 | D2 ), on D1 es el producte de dos matrius que hem anomenat D11 i D12.
			Totes aquestes D's corresponen a derivades del flux en diversos instants (vegi's guio)
			i per tant les tenim al vector x despres des corresponents vols lliures.
		*/
		/*	Arguments:
				- m : dimensió del sistema
				- x0[],xf[]: condicions incials i finals desitjades
				- dt : temps entre punt final i punt incial desitjat
				- dv[] : array amb els dos impulsos que es volen avaluar
				- g[],dg[] : arrays per guardar respectivament G(dv) i DG(dv)
				- pas0, pasmin, pasmax, tolfl, npasmx, *camp, *prm : per passar a flux()
		*/
		
		int i,j; int n = 2*m;
		double x[n+n*n],D1[n*n],D2[n*n];
		double D11[n*n],D12[n*m];
		double t = 0; double h = pas0;
		
		/* -------- PRIMER IMPULS -------- */
		for(i=0;i<m;i++){
			x[i] = x0[i];
			x[i+m] = x0[i+m]+dv[i];
		}
				
		/* --------- VOL LLIURE ---------- */
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(i==j) x[n+i+j*n] = 1;
				else x[n+i+j*n] = 0;
			}
		}
		if(flux(&t,x,&h,dt/2,pasmin,pasmax,tolfl,npasmx,n+n*n,camp,prm)!=0)
			return -1;
		// Guardamos D12
		for(i=0;i<n*m;i++){
			D12[i] = x[n+n*m+i];
		}
		
		/* -------- SEGON IMPULS --------- */
		for(i=0;i<m;i++){
			x[i+m] += dv[i+m];
		}
		
		/* --------- VOL LLIURE ---------- */
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(i==j) x[n+i+j*n] = 1;
				else x[n+i+j*n] = 0;
			}
		}
		if(flux(&t,x,&h,dt/2,pasmin,pasmax,tolfl,npasmx,n+n*n,camp,prm)!=0)
			return -1;
		// Guardamos D12 y D2
		for(i=0;i<n*n;i++){
			D11[i] = x[n+i];
		}
		for(i=0;i<n*m;i++){
			D2[i] = x[n+n*m+i];
		}		
		
		/* CALCUL FINAL DE G i DG */
		for(i=0;i<2*m;i++){
			g[i] = x[i]-xf[i];
		}
		multiplicar(D11,D12,n,n,m,D1);
		for(i=0;i<n*m;i++){
			dg[i] = D1[i];
			dg[i+n*m] = D2[i];
		}		
		
		return 0;		
	}
	
int cmani(int m, double x0[], double xf[], double dt, double dv[],
	double tol, int maxit,
	double pas0, double pasmin, double pasmax, double tolfl, int npasmx,
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm){
		
		/*	Calcula la dv que anula G(dv) per mètode de Newton amb llavor dv donada.
			S'imprimeix per stderr la norma de g i de les correccions per a cada iteracio
			Finalment, s'imprimeix també les dues maniobres que son solucio, que queden
			guardades al vector dv que es donava.
		*/
		/*	Arguments:
				- m : dimensió del sistema
				- x0[],xf[]: condicions incials i finals desitjades
				- dt : temps entre punt final i punt incial desitjat
				- dv[] : llavor per començar el metodo de Newton
				- tol,maxit : tolerancia i nombre maxim d'iteracions pel metode de Newton
				- pas0, pasmin, pasmax, tolfl, npasmx, *camp, *prm : per passar a flux()
		*/
		
		int i; int n = 2*m;
		double dr[n], c[n], g[n], dg[n*n];
		double nc, ng; // Norma de la correció i de G
		
		int iter = 0;
		do{
			iter++;
			cmani_gdg (m, x0, xf, dt, dv, g, dg, pas0, pasmin, pasmax, tolfl, npasmx, camp, prm);
			qrres(n,n,dg,dr,g,c);
			nc = 0; ng = 0;
			for(i=0;i<n;i++){
				dv[i] -= c[i];
				nc += c[i]*c[i];
				ng += g[i]*g[i];
			}
			nc = sqrt(nc); ng = sqrt(ng);
			fprintf(stderr,"cmani() :: it %d ng %10.5E nc %10.5E\n", iter, ng, nc);
		} while(iter<=maxit && nc>tol);
		
		if(iter > maxit){
			fprintf(stderr,"cmani() :: s'ha excedit el nombre d'iteracions maxim");
			return -1;
		}
		else{
			// Imprimimos la solucions final
			fprintf(stderr,"cmani() :: dv1 =");
			for(i=0;i<m;i++) fprintf(stderr," %lf",dv[i]);
			fprintf(stderr,"\n");
			fprintf(stderr,"cmani() :: dv2 =");
			for(i=0;i<m;i++) fprintf(stderr," %lf",dv[m+i]);
			fprintf(stderr,"\n");
			
			return 0;
		}
	}
#include <stdio.h>
#include "../hdr/rk78.h"

int flux (
	double *t, double x[], double *h,
	double T, double pasmin, double pasmax,
	double tol, int npasmx, int n,
	int (*camp)(int n, double t, double x[], double f[], void *prm),
	void *prm){
		/* Implementa el rk78 fins a arribar a la solucio a l'instant t0+T */
		/* 	Arguments:
				- *t : apuntador a temps incial (sortida temps final)
				- x[] : apuntador a condicions inicials (sortida condicions finals)
				- *h : apuntador a pas inicial (sortida pas següent proposat)
				- T : interval de temps a integrar
				- pasmin,pasmax,tol : per passar a rk78
				- npasmx : maxim de pasos del rk78
				- n : dimensio del camp
				- *camp : camp a integrar
				- *prm : parametres per passar al camp, en cas de necessari
		*/		
		
		int cont = 0; double TEMPS_FINAL = *t+T; int control;
		while(*t+*h<TEMPS_FINAL){
			cont++;
			
			control = rk78(t,x,h,pasmin,pasmax,tol,n,camp,prm);
			// Si falla rk78
			if (control != 0){
				fprintf(stderr,"flux() :: El rk78 dio error\n");
				return -1;
			}
			// Si nos pasamos de pasos
			if(cont == npasmx){
				fprintf(stderr,"flux() :: Se ha alcanzado el numero maximo de pasos\n");
				return -1;
			}
		}
		*h = TEMPS_FINAL-*t;
		control = rk78(t,x,h,pasmin,pasmax,tol,n,camp,prm);
		// Si falla rk78
		if (control != 0){
			fprintf(stderr,"flux() :: El rk78 dio error\n");
			return -1;
		}		
		return 0;		
	}
# Càlcul de maniobres d'una nau espacial
_Conjunt de rutines per al càlcul de maniobres d'una nau especial en el problema del tres cossos_

---------------

Aquest respositori consta de tot el conjunt de rutines elaborades per la pràctica de l'assignatura de 'Càlcul Numèric'. L'objectiu final d'aquesta pràctica és el càlcul de les dues maniobres necessàries per portar una nau sotmesa al problema de tres cossos des d'un punt A -de l'espai de sis dimensions 'espai + velocitat'- a un punt B -del mateix espai-. En aquest repositori, però, s'inclouen totes les subrutines que hem hagut de fer seguint el guió de pràctica (també disponible aquí). Per a una millor comprensió de la pràctica i explicació de cada rutina, recomano una lectura dels arxius **guio.pdf** i **memoria.pdf**.

Alguns dels mètodes més coneguts del Càlcul Numèric que es cobreixen en aquesta pràctica són el mètode de Runge-Kutta d'ordres 7 i 8 per la resolució de les ODE's, el mètode QR per la resolució de sistemes lineals sobredeterminats i el mètode de Newton per la resolució d'equacions de _n_ variables.

## Instruccions de compilació
> - Per compilar-ho tot: "make"
> - Per a esborrar object files: "make cleanobjects"
> - Per esborrar-ho tot (objectes i executables): "make cleanall"

## Estructura del codi
> - **img/**	- Conté totes les imatges que s'han fet (amb gnuplot) per a la memòria
> - **io/**	- Conté tots els arxius que han servit com a input i output dels programes
> - **lib/**	- Conté totes les llibreries creades
>    *	 **bin/**	- Conté els object files (si no s'esborren)
>    *	 **hdr/**	- Conté els headers
>    *   **src/**	- Conté els codis
> - **util/**	- Conté les utilitats creades
>    *   **bin/**	- Conté els executables (si no s'esborren)
>    *   **src/**	- Conté els codis

_Desenvolupat per Martín Campos per l'assignatura de 'Càlcul Numèric' del grau de Matemàtiques de la Universitat Autònoma de Barcelona_

/*
THIS PROGRAM EVALUATES INTEGRAL OF 1/(1+x) OVER THE INTERVAL (0,1) USING SIMPSON'S 1/3 RULE 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926
#define f(x) (sqrt(25*(sin(x)*sin(x))+100*(cos(x)*cos(x))))

double integral(double a, double b) {
	int n, j, i=0;
	double A, I, I_prev, h, sum;
	h=(b-a)/2; n=2;
	I=I_prev=0;
	printf ("  i    integral\n");
	printf ("--------------------\n");
	do{
		i++;
		I_prev=I; // update I_prev with I
		I=0;
		for (j=0; j<=n-2; j+=2) {
			A=f(a+j*h)+4*f(a+(j+1)*h)+f(a+(j+2)*h);
			I+=A*h/3; //calculate Ai for the current iteration
		}
		printf ("%3d   %9.6lf\n",i,I);
		n=n*2;
		h=h/2;
	}while (fabs(I-I_prev)>0.0000005);
	return I;
}
int main(void) {
	double a=0, b=2*PI;
	printf ("Value of integral is %lf\n",integral(a,b));
	return 0;
}
				
	


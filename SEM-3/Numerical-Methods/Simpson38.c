/*
THIS PROGRAM EVALUATES INTEGRAL OF 1/(1+x) OVER THE INTERVAL (0,1) USING SIMPSON'S 3/8 RULE 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926
#define f(x) (exp(-(x)))

double simpson3_8(double start, double end) {
	int count, i;
	double I, I_prev, h, n;
	I=I_prev=0;
	h=(end-start)/3; n=3;
	printf ("  i    integral\n");
	printf ("--------------------------\n");
	do {
		I_prev=I;
		I=0;
		for (i=0; i<=n-3; i+=3) {
			I+=f(start+i*h)+3*f(start+(i+1)*h)+3*f(start+(i+2)*h)+f(start+(i+3)*h);
		}
		I=I*h*3/8;
		printf ("%3d   %9.6lf\n",count,I);
		n=n*3;
		h=h/3;
		count++;
	}while ((I-I_prev)/I_prev > 0.00000001 || (I-I_prev)/I_prev < -0.00000001);
	return I;
}
int main(void) {
	simpson3_8(0,1);
	return 0;
}

/*
IMPLEMENT BISECTION METHOD OF FINDING ROOT OF A NON-LINEAR EQUATION
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float func(float);
float bisection(float,float);
int main(void) {
	float a,b,root;
	printf ("Enter lower bound and upper bound of the interval: ");
	do {
		scanf ("%f %f",&a,&b);
	}while (func(a)*func(b)>0); //condition for divergence
	root=bisection(a,b);
	printf ("Root: %9.6f\n\n",root);
	return 0;
}
float func(float val) {
	float f_val=val*sin(val)+cos(val);
	return f_val;
}
float bisection(float a, float b) {
	FILE *fp;
	if ((fp=fopen("bisect.txt","w+"))==NULL) {
		printf ("Cannot open file\n");
		exit(1);
	}
	int i=1;
	float mid_now, mid_prev=a, err_now, err_prev=0, order, abs_error;
	if (func(a)==0) return a;
	else if (func(b)==0) return b;
	printf ("  i      a           b           m          f(m)      abs error order of covergence\n"); 
	printf ("------------------------------------------------------------------------------\n");
	do{
		mid_now=(a+b)/2; // calculate current midpoint
		err_now=(a>b)?(a-b):(b-a);  //calculate absolute error
		order=log(err_now)/log(err_prev); //calculate order of convergence
		printf ("%3d   %9.6f   %9.6f   %9.6f   %9.6f   %9.6f   %9.6f\n",i,a,b,mid_now,func(mid_now),err_now,order);
		fprintf (fp,"%3d   %9.6f   %9.6f   %9.6f   %9.6f   %9.6f   %9.6f\n",i,a,b,mid_now,func(mid_now),err_now,order);
		if (func(mid_now)*func(a)>0) a=mid_now; // set the next values of a and b
		else b=mid_now;
		mid_prev=mid_now; // update previous midpoint
		err_prev=err_now; // update previous error
		i++;
	}while (func(mid_now)!=0 && err_now>0.000001); //condition for convergence
	fclose(fp);
	return mid_now;
}

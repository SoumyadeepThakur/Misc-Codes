/*
THIS PROGRAM SOLVES A SYSTEM OF LINEAR EQUATIONS BY GAUSS ELIMINATION METHOD
*/

#include <stdio.h>
#include <stdlib.h>
#define ABS(a) ((a>0)?a:-a)

void gauss_jordan(double **a, double *x, int size) {
	int i, j, k, max_row;
	double sum, max, mult, temp;
	for (i=0; i<size-1; i++) {
		max=ABS(a[i][i]);
		for (j=i; j<size; j++) {  // find the row having largest value of first non zero element
			max=(ABS(a[j][i])>max)?ABS(a[j][i]):max;
			max_row=j;
		}
		for (j=i; j<=size; j++) { // swap the first row with the row having maximum first non zero element
			temp=a[i][j];
			a[i][j]=a[max_row][j];
			a[max_row][j]=temp;
		}
		for (j=i+1; j<size; j++) {
			mult=a[j][i]/a[i][i]; // find multiplier for jth row
			for (k=i; k<=size; k++) {
				a[j][k]=a[j][k]-mult*a[i][k]; // row reduction
			}
		}
	}
	for (i=size-1; i>=0; i--) {
		sum=0;
		for (j=size-1; j>i; j--) {
			sum+=x[j]*a[i][j]; 
		}
		x[i]=(a[i][size]-sum)/a[i][i]; // calculate values of xi
	}
}
void input(double ***coeff, double **soln, int *size) {
	int i, j, row, col;
	printf ("Enter number of equations:\n");
	scanf ("%d",&row); col=row+1;
	*coeff=(double**)malloc(row*sizeof(double*));
	*soln=(double*)malloc(row*sizeof(double));
	for (i=0; i<row; i++) {
		(*coeff)[i]=(double*)malloc(col*sizeof(double));
	}
	printf ("Enter coeffecients\n");
	for (i=0; i<row; i++) { 
		for (j=0; j<=row; j++) {
			scanf ("%lf",&(*coeff)[i][j]); // take input
		}
	}
	*size=row;
}
void display(double *soln, int n) {
	int i;
	printf ("Solution of the system of equations:\n");
	for (i=0; i<n; i++) printf ("x%d = %lf\n",(i+1),soln[i]);
}
int main(void) {
	int n, i, j;
	double **coeff, *soln;
	coeff=(double**)malloc(sizeof(double*));
	soln=(double*)malloc(sizeof(double));
	input(&coeff,&soln,&n);
	gauss_jordan(coeff,soln,n);
	display(soln,n);
	return 0;
}

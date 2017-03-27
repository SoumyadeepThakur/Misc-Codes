/*
THIS PROGRAM EVALUATES THE INVERSE OF A MATRIX USING GAUSS-JORDAN METHOD
*/


#include <stdio.h>
#include <stdlib.h>
#define ABS(a) ((a>0)?a:-a)

void gauss_jordan(double **a, double **x, int size) {
	int i, j, k, max_row;
	double sum, max, mult, temp;
	for (i=0; i<size; i++) {
		max=ABS(a[i][i]); max_row=i;
		for (j=i; j<size; j++) { // fing the row having the largest value of the first non-zero element
			max=(ABS(a[j][i])>max)?ABS(a[j][i]):max;
			max_row=j;
		}
		for (j=0; j<size; j++) { // swap the ith row with the row having maximum first non zero element
			temp=a[i][j];
			a[i][j]=a[max_row][j];
			a[max_row][j]=temp;
			temp=x[i][j]; //swap the ith row of the identity matrix accordingly
			x[i][j]=x[max_row][j];
			x[max_row][j]=temp;
		}
		for (j=0; j<size; j++) {
			if (j==i) continue;
			mult=a[j][i]/a[i][i]; // find the multiplier for the jth row
			for (k=0; k<size; k++) {
				a[j][k]=a[j][k]-mult*a[i][k]; // row reduction
				x[j][k]=x[j][k]-mult*x[i][k];
			}
		}
	}
	for (i=0; i<size; i++) { // reduce the coeffecient matrix to identity
		for (j=0; j<size; j++) {
			x[i][j]/=a[i][i]; 
		}
		a[i][i]/=a[i][i];
	}	
}
void input(double ***coeff, double ***soln, int *n) {
	int i, j, size;
	printf ("Enter size of the square matrix: ");
	scanf ("%d",&size);
	*n=size;
	*coeff=(double**)malloc(size*sizeof(double*));
	*soln=(double**)malloc(size*sizeof(double*));
	for (i=0; i<size; i++) {
		(*coeff)[i]=(double*)malloc(size*sizeof(double));
		(*soln)[i]=(double*)malloc(size*sizeof(double));
	}
	printf ("Enter the matrix elements:\n");
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			scanf ("%lf",&(*coeff)[i][j]); // input coeffecient matrix
			if (i==j) (*soln)[i][j]=1; // initialize soln with identity matrix
			else (*soln)[i][j]=0;
		}
	}
}
void display(double **arr, int n) {
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf ("%lf ",arr[i][j]);
		}
		printf ("\n");
	}
}
void multiply(double **arr1, double **arr2, double **arr3, int n) {
	int i, j, k;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			arr3[i][j]=0;
			for (k=0; k<n; k++) {
				arr3[i][j]+=arr1[i][k]*arr2[k][j];
			}
		}
	}
}
void copy(double **arr, double ***temp, int n) {
	int i, j;
	*temp=(double**)malloc(n*sizeof(double*));
	for (i=0; i<n; i++) {
		(*temp)[i]=(double*)malloc(n*sizeof(double));
	}
	for (i=0; i<n; i++) { // copy elemnts of arr to temp
		for (j=0; j<n; j++) {
			(*temp)[i][j]=arr[i][j];
		}
	}
}		
void clear(double **arr, int n) {
	int i;
	for (i=0; i<n; i++) {
		free(arr[i]);
	}
	free(arr);
}
int main(void) {
	int n, i, j;
	double **arr; double **x;
	double **temp;
	arr=(double**)malloc(sizeof(double*));
	x=(double**)malloc(sizeof(double*));
	temp=(double**)malloc(sizeof(double*));
	input(&arr,&x,&n);
	copy(arr,&temp,n); // copy arr to a temporary matrix
	gauss_jordan(temp,x,n);
	multiply(arr,x,temp,n); // multiply arr with x to verify the result
	printf ("\nInverse: \n\n");
	display(x,n);
	printf ("\nMultiplying the original matrix with the inverse:\n\n");
	display(temp,n);
	clear(arr,n); clear(temp,n); clear(x,n);
	return 0;
}

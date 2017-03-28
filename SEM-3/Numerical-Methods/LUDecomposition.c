#include <stdio.h>
#include <stdlib.h>
#define ABS(x) ((x>0)?x:-x)

void lu_decompose(double **arr, double **lmatrix, double **umatrix, int size) {
	int i, j, k;
	double mult;
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			umatrix[i][j]=arr[i][j];
			if (i==j) lmatrix[i][j]=1;
			else lmatrix[i][j]=0;
		}	
	}
	for (i=0; i<size; i++) {
		for (j=i+1; j<size; j++) {
			mult=umatrix[j][i]/umatrix[i][i];
			for (k=i; k<size; k++) {
				umatrix[j][k]-=mult*umatrix[i][k];
			}
			lmatrix[j][i]=mult;
		}
	}
	for (i=0; i<size; i++) {
		for (j=i; j<size; j++) {
			lmatrix[j][i]*=umatrix[i][i];
		}
		for (j=size-1; j>=i; j--) {
			umatrix[i][j]/=umatrix[i][i];
		}
	}
	printf("matrices:\n"); 
	printf ("L: \n");
	display_matrix(umatrix,size);
	printf ("U: \n");
	display_matrix(lmatrix,size);
}
void lu_solve(double **lmatrix, double **umatrix, double *b, double *x, int size) {
	int i, j;
	double sum;
	double *z=(double*)malloc(size*sizeof(double));
	for (i=0; i<size; i++) {
		sum=0;
		for (j=0; j<i; j++) {
			sum=sum+lmatrix[i][j]*z[j];
		}
		z[i]=(b[i]-sum)/lmatrix[i][i];
	}
	for (i=size-1; i>=0; i--) {
		sum=0;
		for (j=size-1; j>i; j--) {
			sum=sum+umatrix[i][j]*x[j];
		}
		x[i]=(z[i]-sum)/umatrix[i][i];
	}
	
	//for (i=0; i<size; i++) printf ("%lf ",z[i]);
	printf ("\nSolution: \n");
	for (i=0; i<size; i++) printf ("%lf ",x[i]);
}
void display_matrix(double **arr, int size) {
	int i, j;
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			printf ("%lf ",arr[i][j]);
		}
		printf ("\n");
	}
}
int main(void) {
	int i, j, n;
	double **a, **l, **u, *b, *x;
	printf("Enter size of matrix: ");
	scanf ("%d",&n);
	a=(double**)malloc(n*sizeof(double*));
	l=(double**)malloc(n*sizeof(double*));
	u=(double**)malloc(n*sizeof(double*));
	b=(double*)malloc(n*sizeof(double));
	x=(double*)malloc(n*sizeof(double));
	for (i=0; i<n; i++) {
		a[i]=(double*)malloc(n*sizeof(double));
		l[i]=(double*)malloc(n*sizeof(double));
		u[i]=(double*)malloc(n*sizeof(double));
	}
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			scanf ("%lf",&a[i][j]);
		}
		scanf ("%lf",&b[i]);
	}
	lu_decompose(a,l,u,n);
	lu_solve(l,u,b,x,n);
	//display_matrix(x);
	return 0;
} 

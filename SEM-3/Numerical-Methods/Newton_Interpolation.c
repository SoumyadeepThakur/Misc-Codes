/*
THIS PROGRAM IMPLEMENTS NEWTON'S INTERPOLATION METHOD

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	double *x;
	double *y;
	int size;
} points;

points *init_table(void) { // initiallize the data table
	int num, i;
	points *table;
	if ((table=(points*)malloc(sizeof(points)))==NULL) {
		printf ("Memory Allocation Error\n");
		exit(1);
	};
	printf ("Enter number of known points:\n");
	scanf ("%d",&num);
	table->x=(double*)malloc(num*sizeof(double));
	table->y=(double*)malloc(num*sizeof(double));
	table->size=num;
	printf ("Enter data points:\n");
	for (i=0; i<table->size; i++) {
		scanf ("%lf %lf",&(table->x[i]),&(table->y[i])); // input data
	}
	fflush(stdin);
	return table;
}
double **forward_difference_table(points *table) {
	int i, j;
	double **diff_table=(double**)malloc(table->size*sizeof(double*));
	for (i=0; i<table->size; i++) {
		diff_table[i]=(double*)malloc((table->size-i)*sizeof(double));
		if (i==0) {
			for (j=0; j<table->size; j++) diff_table[i][j]=table->y[j]; // first column contains values of y
		}
		else {
			for (j=0; j<table->size-i; j++) {
				diff_table[i][j]=diff_table[i-1][j+1]-diff_table[i-1][j]; // jth column contains (j-1)th forward difference
			}
		}
	}
	return diff_table;
}
double interpolate(points *table, double x_value) {
	int deg=table->size-1, i, j;
	double y_value, interval, mid, **diff_table, mult, p;
	mid=(table->x[0]+table->x[deg])/2;
	interval=table->x[1]-table->x[0];
	diff_table=forward_difference_table(table);
	mult=1; y_value=0;
	if (x_value<mid) { // if x_value is towards beginning of table apply Forward Difference formula
		p=(x_value-table->x[0])/interval;
		for (i=0; i<=deg; i++) {
			//printf ("%lf ",diff_table[i][0]*mult);
			y_value+=diff_table[i][0]*mult; // calculate y value
			mult*=(p-i)/(double)(i+1);
		}
	}
	else { // if x_value is towards end of table apply Backward Difference formula
		p=(x_value-table->x[deg])/interval;
		for (i=0; i<=deg; i++) {
			y_value+=diff_table[i][deg-i]*mult; // calculate y_value
			mult*=(p+i)/(double)(i+1);
		}
	}
	for (i=0; i<table->size; i++) free(diff_table[i]);
	free(diff_table);
	return y_value;
}
int main(void) {
	int i, j;
	double y, x;
	points *table1;
	table1=init_table();
	printf ("Enter x for which y needs to be found:\n");
	scanf ("%lf",&x);
	y=interpolate(table1,x);
	printf ("For x=%lf y=%lf\n",x,y);
	free(table1);
	return 0;
}



/*
PROGRAM TO REPRESENT POLYNOMIALS AS DATA STRUCTURES USING ARRAYS
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100000

int avail; // cursor to unused space of poly_term
typedef struct {
	int exp;
	float coeff;
}term;
term poly_term[MAX_TERMS]; // pool of terms
typedef struct {
	int start;
	int end;
}polynomial;
polynomial *init(void) {
	polynomial *poly;
	if ((poly=(polynomial*)malloc(sizeof(polynomial)))==NULL) {
		printf ("Memory Allocation Error\n");
		exit(1);
	}
	return poly;
}
void create (polynomial *poly) {
	int no_terms;
	printf ("Enter number of non-zero terms in the polynomial:\n");
	scanf ("%d",&no_terms);
	poly->start=avail;
	printf ("Enter coeffecient of terms in decreasing order of exponents:\n");
	while (no_terms-- >0) {
		printf ("Exponent: ");
		scanf ("%d",&(poly_term[avail].exp));
		printf ("Coeffecient: ");
		scanf ("%f",&(poly_term[avail].coeff));
		if(poly_term[avail].coeff!=0) avail++; // increment avail pointer for each non zero coefficient
	}
	poly->end=avail-1;
}
void display(polynomial *poly) {
	int i;
	if (is_zero(poly)) {
		printf ("Zero Polynomial\n");
		return;
	}
	for (i=poly->start; i<=poly->end; i++) {
		if (poly_term[i].exp==0) printf ("%f",poly_term[i].coeff);
		else printf ("%fx^%d",poly_term[i].coeff,poly_term[i].exp);
		if (i!=poly->end) printf ("+ ");
	}
	printf ("\n");
}
polynomial *add_subtract (polynomial *poly1, polynomial *poly2, int sub) {
	int i, j;
	int sign;
	sign=(sub)?-1:1; // add or subtract control
	polynomial *poly_sum=(polynomial*)malloc(sizeof(polynomial));
	i=poly1->start, j=poly2->start;
	poly_sum->start=avail;
	while (i<=poly1->end && j<=poly2->end) { 
		if (poly_term[i].exp>poly_term[j].exp) { // store term of poly1
			poly_term[avail].coeff=poly_term[i].coeff;
			poly_term[avail].exp=poly_term[i].exp;
			avail++;
			i++;
		}
		else if (poly_term[j].exp>poly_term[i].exp) { // store term of poly2
			poly_term[avail].coeff=poly_term[j].coeff*sign;
			poly_term[avail].exp=poly_term[j].exp;
			avail++;
			j++;
		}
		else {
			if (poly_term[i].coeff+poly_term[j].coeff!=0) { // store sum/difference of terms of poly1 and poly2
				poly_term[avail].coeff=poly_term[i].coeff+poly_term[j].coeff*sign;
				poly_term[avail].exp=poly_term[i].exp;
				avail++;
			}
			i++;
			j++;
		}
	}
	while (i<=poly1->end) {
		poly_term[avail].coeff=poly_term[i].coeff;
		poly_term[avail].exp=poly_term[i].exp;
		avail++;
		i++;
	}
	while (j<=poly2->end) {
		poly_term[avail].coeff=poly_term[j].coeff*sign;
		poly_term[avail].exp=poly_term[j].exp;
		avail++;
		j++;
	}
	poly_sum->end=avail-1;
	return poly_sum;
}
polynomial *multiply_cons(polynomial *poly, float cons) {
	int i;
	polynomial *pdt=(polynomial*)malloc(sizeof(polynomial));
	if (cons==0 || is_zero(poly)) { // product will be zero polynomial
		pdt->start=avail;
		pdt->end=avail-1;
		return pdt;
	}
	pdt->start=avail;
	for (i=poly->start; i<=poly->end; i++) {
		poly_term[avail].coeff=poly_term[i].coeff*cons; // multiply each (non-zero) term by cons
		poly_term[avail].exp=poly_term[i].exp;
		avail++;
	}
	pdt->end=avail-1;
	return pdt;
}
polynomial *multiply(polynomial *poly1, polynomial *poly2) {
	int i, deg, lo, up, mid, reqd_exp;
	float coeff_sum;
	polynomial *pdt;
	if ((pdt=(polynomial*)malloc(sizeof(polynomial)))==NULL) {
		printf ("Memory Allocation Error\n");
		exit(1);
	}
	if (is_zero(poly1) || is_zero(poly2)) { // result will be zero plynomial
		pdt->start=avail;
		pdt->end=avail-1;
		return pdt;
	}
	deg=poly_term[poly1->start].exp+poly_term[poly2->start].exp;
	pdt->start=avail;
	while (deg>=0) {
		i=poly1->start;
		coeff_sum=0;
		while ((deg-poly_term[i].exp)<=poly_term[poly2->start].exp && i<=poly1->end) {
			reqd_exp=deg-poly_term[i].exp;
			lo=poly2->start; up=poly2->end; 
			if (reqd_exp<0) {
				i++; continue;
			}
			while (lo<=up) { // search for the exponent in the polynomial
				mid=(lo+up)/2;
				if (reqd_exp>poly_term[mid].exp) up=mid-1;
				else if (reqd_exp<poly_term[mid].exp) lo=mid+1;
				else {
					coeff_sum+=poly_term[mid].coeff*poly_term[i].coeff;
					break;
				}
			}
			i++;
		}
		if (coeff_sum) {
			poly_term[avail].coeff=coeff_sum;
			poly_term[avail].exp=deg;
			avail++;
		}
		deg--;
	}
	pdt->end=avail-1;
	return pdt;
}
int degree(polynomial *poly) {
	int deg;
	deg=poly_term[poly->start].exp; // since exponents are sorted in descending order
	return deg;
}
int is_zero(polynomial *poly) {
	if (poly->end<poly->start) return 1;
	return 0;
}
int main(void) {
	polynomial *poly[MAX_TERMS];
	int next_index=0, index1, index2, choice, deg, flag=1;
	float cons;
	while (flag) {
		printf ("MENU:\n");
		printf ("1. Create a polynomial\n2. Add 2 polynmials\n3. Subtract a polynomial from another polynomial\n4. Multiply a polynomial with a constant\n5. Multiply 2 polynomials\n6. Find degree of a polynomial\n7. Check whether a polynomial is zero polynomial\n8. Display a polynomial\n9. Exit\n\n");
		printf ("Enter your choice: \n");
		scanf ("%d",&choice);
		switch(choice) {
			case 1: poly[next_index]=init();
					create(poly[next_index++]);
					break;
			case 2: printf ("Enter the polynomial numbers to be added:\n");
					scanf ("%d %d",&index1,&index2);
					poly[next_index]=init();
					poly[next_index]=add_subtract(poly[index1],poly[index2],0);
					next_index++;
					break;
			case 3: printf ("Enter the polynomial number to be subtracted and the polynomial number from which it is to be subtracted:\n");
					scanf ("%d %d",&index1,&index2);
					poly[next_index]=init();
					poly[next_index]=add_subtract(poly[index1],poly[index2],1);
					next_index++;
					break;
			case 4: printf ("Enter the polynomial number to be multiplied with a constant:\n");
					scanf ("%d",&index1);
					printf ("Enter the constant:\n");
					scanf ("%f",&cons);
					poly[next_index]=init();
					poly[next_index]=multiply_cons(poly[index1],cons);
					next_index++;
					break;
			case 5: printf ("Enter the polynomial numbers to be multiplied:\n");
					scanf ("%d %d",&index1,&index2);
					poly[next_index]=init();
					poly[next_index]=multiply(poly[index1],poly[index2]);
					next_index++;
					break;
			case 6: printf ("Enter the polynomial number whose degree is to be found:\n");
					scanf ("%d",&index1);
					deg=degree(poly[index1]);
					printf ("Degree: %d\n",deg);
					break;
			case 7: printf ("Enter the polynomial number to be checked for:\n");
					scanf ("%d",&index1);
					if (is_zero(poly[index1])) printf ("Zero polynomial\n");
					else printf ("Not a zero polynomial\n");
					break;
			case 8: printf ("Enter the polynomial number to be displayed:\n");
					scanf ("%d",&index1);
					display(poly[index1]);
					break;
			case 9: exit(1);
			default: printf ("Invalid Choice\n");
		}
	}
	
	//poly[2]=add(poly[0],poly[1]);
	//printf ("%lf %d",poly_term[0].coeff,poly_term[0].exp);
	//printf ("%lf %d",poly_term[1].coeff,poly_term[1].exp);
	//printf ("%lf %d",poly_term[2].coeff,poly_term[2].exp);
	//display(poly[0]);
	//display(poly[1]);
	//display(poly[2]);
	return 0;
}

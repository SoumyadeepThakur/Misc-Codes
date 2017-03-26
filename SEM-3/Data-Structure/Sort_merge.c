/*
PROGRAM TO MERGE 2 SORTED ARRAYS INTO A SINGLE ARRAY IN THAT SORTED ORDER
*/

#include <stdio.h>
#include <stdlib.h>

unsigned char get_order(int* array, int length) { // function to evaluate the sort order
	unsigned char order='E';
	int i;
	for (i=1; i<length; i++) {
		if (order=='E' && array[i-1]==array[i]) order='E';
		else if (order=='E' && array[i-1]<array[i]) order='I';
		else if (order=='E' && array[i-1]>array[i]) order='D';
		else if (order=='I' && array[i-1]>array[i]) return 'U';
		else if (order=='D' && array[i-1]<array[i]) return 'U';
	}
	return order;
}
void merge (int* merged, int* arr1, int len1, int* arr2, int len2, int order) {
	int i=0, j=0, k=0;
	while (i<len1 && j<len2) {
		if (order=='E' || order=='I') { // merge in increasing order
			if (arr1[i]<arr2[j]) {
				merged[k]=arr1[i];
				k++; i++;
			}
			else {
				merged[k]=arr2[j];
				k++; j++;
			}
		}
		else if (order=='D') { // merge in decreasing order
			if (arr1[i]>arr2[j]) {
				merged[k]=arr1[i];
				k++; i++;
			}
			else {
				merged[k]=arr2[j];
				k++; j++;
			}
		}
	}
	while (i<len1) merged[k++]=arr1[i++]; 
	while (j<len2) merged[k++]=arr2[j++];
}
int main(void) {
	int len1, len2, i;
	int *array1, *array2, *merged;
	unsigned char order1, order2;
	printf ("Enter lengths of the 2 arrays: ");
	scanf ("%d %d",&len1, &len2);
	array1=(int*)malloc(len1*sizeof(int));
	array2=(int*)malloc(len2*sizeof(int));
	printf ("Enter 1st array: ");
	for (i=0; i<len1; i++) {
		scanf ("%d",&array1[i]);
	}
	printf ("Enter 2nd array: ");
	for (i=0; i<len2; i++) {
		scanf ("%d",&array2[i]);
	}
	order1=get_order(array1,len1);
	order2=get_order(array2,len2);
	if (order1 =='U' || order2 == 'U') {
		printf ("Error: One of the arrays is unsorted\n");
		exit(1);
	}
	else if (order1!=order2) {
		printf ("Error: Arrays are not sorted in the same order\n");
		exit(1);
	}
	merged=(int*)malloc((len1+len2)*sizeof(int));
	merge(merged,array1,len1,array2,len2,order1);
	printf ("Merged Array:\n");
	for (i=0; i<len1+len2; i++) printf ("%d ",merged[i]);
	return 0;
}

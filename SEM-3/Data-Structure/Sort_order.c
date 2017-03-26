/*
PROGRAM TO FIND WHETHER AN ARRAY IS SORTED OR NOT AND ITS SORTED ORDER
*/
#include <stdio.h>
#include <stdlib.h>

// E='equal' I='increasing' D='decreasing' U='unordered'
unsigned char get_order(float* array, int length) {
	unsigned char order='E'; // assuming order to be equal
	int i;
	for (i=1; i<length; i++) {
		if (order=='E' && array[i-1]==array[i]) order='E'; // order upto i-1 is E and a[i]=a[i-1] implies order remains E
		else if (order=='E' && array[i-1]<array[i]) order='I'; //order upto i-1 is E and a[i]>a[i-1] implies order is I
		else if (order=='E' && array[i-1]>array[i]) order='D'; //order upto i-1 is E and a[i]<a[i-1] implies order is D
		else if (order=='I' && array[i-1]>array[i]) return 'U'; //order upto i-1 is I and a[i]<a[i-1] implies unordered
		else if (order=='D' && array[i-1]<array[i]) return 'U'; //order upto i-1 is D and a[i]>a[i-1] implies unordered
	}
	return order;
}

int main(void) {
	int i, size;
	float *arr;
	unsigned char order;
	printf ("Enter size of the array: ");
	scanf ("%d",&size);
	arr=(float*)malloc(size*sizeof(float));
	printf ("Enter array elements:\n");
	for (i=0; i<size; i++) {
		scanf ("%f",&arr[i]);
	}
	fflush(stdin);
	order=get_order(arr,size);
	switch(order) {
		case 'I': printf ("Array is sorted in increasing order");
				  break;
		case 'D': printf ("Array is sorted in decreasing order");
				  break;
		case 'E': printf ("Array elements are all equal");
				  break;
		case 'U': printf ("Array is unsorted");
				  break;
		default: printf("ERROR");
	}
	free(arr);
	return 0;
}

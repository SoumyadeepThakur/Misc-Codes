/*
PROGRAM TO REPRESENT POLYNOMIALS AS DATA STRUCTURES USING ARRAYS
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 10000
#define SENTINEL -1

typedef struct listtype {
	int node_array[N];
	int length;
	int max_length; // maximum allowable length of the list
} list;
void init(list **ls) {
	*ls=(list*)malloc(sizeof(list));
	(*ls)->max_length=N;
	(*ls)->length=0;
}
int is_empty(list *ls) {
	return (ls->length==0);
}
int length(list *ls) {
	return ls->length;
}
int is_legal(list *ls, int pos) {
	if (pos<0 || pos>=ls->length) return 0; // pos out of list bounds
	return 1;
}
void display(list *ls) {
	int i;
	if (is_empty(ls)) {
		printf ("EMPTY LIST\n");
		return;
	}
	printf ("\nContents of the list:\n");
	for (i=0; i<ls->length; i++) printf ("%d ",ls->node_array[i]);
	printf ("\n");
}
void insert_list(list *ls, int data, int pos) {
	int i, j;
	if (ls->length==N-1) {
		printf ("LIST IS FULL\n");
		return;
	}
	if (pos==ls->length) { // insert at end
		ls->node_array[pos]=data;
		ls->length++;
		return;
	}
	if (is_legal(ls,pos)) {
		for (i=ls->length-1; i>=pos; i--) { // shift elements towards right
			ls->node_array[i+1]=ls->node_array[i];
		}
		ls->node_array[pos]=data;
		ls->length++;
	}
	printf ("INVALID POSITION\n");
}

int delete_list(list *ls, int pos) {
	int i, j, value;
	if (is_empty(ls)) {
		printf ("EMPTY LIST\n");
		return INT_MIN;
	}	
	if (!(is_legal(ls,pos))) {
		printf ("INVALID POSITION\n");
		return INT_MIN; // error flag
	}
	value=ls->node_array[pos];
	for (i=pos; i<ls->length-1; i++) { // shift elements towards left
		ls->node_array[i]=ls->node_array[i+1];
	}
	ls->length--;
	return value;
}

int read(list *ls, int pos) {
	int value=INT_MIN;
	if (is_empty(ls)) {
		printf ("EMPTY LIST\n");
		return INT_MIN; // error flag
	}
	if (is_legal(ls,pos)) {
		value=ls->node_array[pos];
	}
	else printf ("INVALID POSITION\n");
	return value;
}
void write(list *ls, int data, int pos) {
	if (is_empty(ls)) {
		printf ("EMPTY LIST\n");
	}
	if (is_legal(ls,pos)) {
		ls->node_array[pos]=data;
	}
	else printf ("INVALID POSITION\n");
	return;
}
int search_list(list *ls, int key) {
	int i=0;
	if (is_empty(ls)) {
		printf ("LIST IS EMPTY\n");
		return -1;		
	}
	for (i=0; i<ls->length; i++) {
		if (ls->node_array[i]==key) return i;
	}
	return -1;
} 
void sort(list *ls) {
	if (is_empty(ls)) {
		printf ("LIST IS EMPTY\n");
		return;
	}
	int t, k, i;
	//insertion sort
    for (i=1; i<ls->length; i++) {
    	t = ls->node_array[i];
		k = i-1;
       	while (k>=0 && t < ls->node_array[k]) {
        	ls->node_array[k+1] = ls->node_array[k];
			k--;	
    	}
    	ls->node_array[k+1] = t;
	}
}
int main(void) {
	list *ls1;
	int choice, data, n, flag=1;
	init(&ls1);
	while (flag) {
		printf ("MENU:\n");
		printf ("1. Read the nth element\n2. Write the nth element\n3. Insert an element at the nth position \n4. Delete the element from nth position\n5. Search for a key\n6. Sort the list in ascending order\n7. Check whether the list is empty\n8. Find length of the list\n9. Display the list\n0. Exit");
		printf ("\n\nEnter your choice: \n");
		scanf ("%d",&choice);
		switch(choice) {
			case 1: printf ("Enter n:\n");
			        scanf("%d",&n);
		 	        printf ("Element: %d\n",read(ls1,n));
		 	        break;
			case 2: printf ("Enter n:\n");
			        scanf("%d",&n);
					printf ("Enter data to write: \n");
					scanf("%d",&data);
		 	        write(ls1,data,n);
		 	        break;
			case 3: printf ("Enter n:\n");
			        scanf("%d",&n);
					printf ("Enter data to be inserted: \n");
					scanf("%d",&data);
		 	        insert_list(ls1,data,n);
		 	        break;
		 	case 4: printf ("Enter n:\n");
			        scanf("%d",&n);
					printf ("Deleted Element: %d\n",delete_list(ls1,n));
					break;
			case 5 :printf ("Enter the key to be searched for: ");
					scanf ("%d",&data);
					n=search_list(ls1,data);
					if (n==-1) printf ("Data not found\n");
					else printf ("Position: %d",n);
					break;
			case 6: sort(ls1);
					break;
			case 7: if (is_empty(ls1)) printf ("Empty List\n");
					else printf ("Non-empty List\n");
					break;
			case 8: printf ("Length: %d\n",length(ls1));
					break;
			case 9: display(ls1);
					break;
			case 0: exit(1);
			default: printf ("Wrong Choice\n");
		}
	}
	return 0;
}




/*
PROGRAM TO REPRESENT POLYNOMIALS AS DATA STRUCTURES USING ARRAYS
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 10001
#define SENTINEL -1

typedef struct listtype {
	int node_array[N];
	int max_length; // maximum allowable length of the list
} list;
void init(list **ls) {
	*ls=(list*)malloc(sizeof(list));
	(*ls)->node_array[0]=SENTINEL;
	(*ls)->max_length=N-1; // set maximum allowable length to N-1
}
int is_empty(list *ls) {
	return (ls->node_array[0]==SENTINEL);
}
int length(list *ls) {
	int i, length;
	i=0;
	while (ls->node_array[i]!=SENTINEL) {
		i++; // iterate over elements until sentinel is reached
	}
	length=i;
	return length;
}
int is_legal(list *ls, int pos) {
	int i=0;
	if (pos<0 || pos>=ls->max_length) return 0; // pos out of list bounds
	while (ls->node_array[i]!=SENTINEL) {
		if (i==pos) return 1;
		i++;
	}
	return 0;
}
void display(list *ls) {
	int i=0;
	printf ("\nContents of the list:\n");
	while (ls->node_array[i]!=SENTINEL){
		printf ("%d ",ls->node_array[i]);
		i++;
	}
	printf ("\n");
}
void insert_list(list *ls, int data, int pos) {
	int i, j;
	if (ls->node_array[N-1]==SENTINEL) {
		printf ("LIST IS FULL\n");
		return;
	}
	if (ls->node_array[pos]==SENTINEL) { // insert at end
		ls->node_array[pos]=data;
		ls->node_array[pos+1]=SENTINEL;
		return;
	}
	if (is_legal(ls,pos)) {
		i=0;
		j=pos;
		while (ls->node_array[j]!=SENTINEL) j++;
		while (j!=pos-1) {
			ls->node_array[j+1]=ls->node_array[j]; // shift elements towards right
			j--;
		}
		ls->node_array[pos]=data; 
		return;
	}
	printf ("INVALID POSITION\n");
}

int delete_list(list *ls, int pos) {
	int i, j, value;
	if (is_empty(ls)) {
		printf ("EMPTY LIST\n");
		return INT_MIN; // error flag
	}	
	if (!(is_legal(ls,pos))) {
		printf ("INVALID POSITION\n");
		return INT_MIN; // error flag
	}
	value=ls->node_array[pos];
	i=pos;
	while (ls->node_array[i]!=SENTINEL) {
		ls->node_array[i]=ls->node_array[i+1]; // shift elements towards left
		i++;
	}
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
	while (ls->node_array[i]!=SENTINEL) {
		if (ls->node_array[i]==key) return i;
		i++;
	}
	return -1;
} 
void sort(list *ls) {
	if (is_empty(ls)) {
		printf ("LIST IS EMPTY\n");
		return;
	}
	int t, k, i=1;
		// insertion sort
    	while (ls->node_array[i]!=SENTINEL) {
        	t = ls->node_array[i];
		k = i-1;
        	while (k>=0 && t < ls->node_array[k]) {
       	    		ls->node_array[k+1] = ls->node_array[k];
	    		k--;
        	}
        	ls->node_array[k+1] = t;
		i++;
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
					else printf ("Position: %d\n",n);
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
			case 0: exit(0);
			default: printf ("Wrong Choice\n");
		}
	}
	return 0;
}




/*
PROGRAM TO REPRESENT SPARSE MATRIX AS A DATA STRUCTURE USING ARRAY
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TERMS 1001

typedef struct {
	int row;
	int col;
	float val;
}sparse;
sparse *init_sparse(int row, int col) {
	int i, limit=2+(row*col)/4;
	sparse *spm;
	spm=(sparse*)malloc(limit*sizeof(sparse));
	spm[0].row=row;
	spm[0].col=col;
	spm[0].val=0;
	return spm;
}
void clear (sparse **spm) {
	sparse *temp=*spm;
	free(temp);
	free(spm);
}
sparse *create_sparse(void) {
	int row, col, limit, i, j, k=0;
	float num;
	sparse *sp_matrix;
	printf ("Enter no of rows and columns: ");
	scanf ("%d %d",&row,&col);
	sp_matrix=init_sparse(row,col);
	printf("%d %d\n",sp_matrix[0].row,sp_matrix[0].col);
	printf ("Enter matrix elements:\n");
	for (i=0; i<row; i++) {
		for (j=0; j<col; j++) {
			scanf ("%f",&num);
			printf ("%f ",num);
			if (fabs(num)>=0.000001) {
				k++;
				//printf ("%d ",(*sp_matrix)[0][2]);
				sp_matrix[k].row=i;
				sp_matrix[k].col=j;
				sp_matrix[k].val=num;
			} 
		}
	}
	sp_matrix[0].val=k;
	for (i=0; i<=sp_matrix[0].val; i++) {
		printf ("%d %d %f\n",sp_matrix[i].row,sp_matrix[i].col,sp_matrix[i].val);
	}
	//free(spm);
	return sp_matrix;
}
void display_sparse(sparse *spm) {
	if (spm==NULL) {
		printf ("NULL");
		return;
	}
	printf ("Sparse Matrix:\n");
	int i, j, k, len, row, col;
	k=1;
	row=spm[0].row; col=spm[0].col;
	printf ("%d %d\n",row, col);
	for (i=0; i<row; i++) {
		for (j=0; j<col; j++) {
			if (k<=spm[0].val && i==spm[k].row && j==spm[k].col){
				printf ("%7.4f ",spm[k].val);
				k++;
			}
			else printf ("%7.4f ",0);
		}
		printf ("\n");
	}
}
sparse *add_sparse(sparse *spm1, sparse *spm2) {
	int i, j, k, row, col, limit;
	sparse *spm_sum;
	if(spm1[0].row != spm2[0].row || spm1[0].col != spm2[0].col) {
		printf("Invalid matrix size");
		return NULL;
	}
	row=spm1[0].row; col=spm1[0].col;
	spm_sum=init_sparse(row,col);
	i=1; j=1; k=1;
	while (i<=spm1[0].val && j<=spm2[0].val) {
		printf ("%d %d \n",i,j);
		if ((col*spm1[i].row+spm1[i].col)<(col*spm2[j].row+spm2[j].col)) {
			spm_sum[k].row=spm1[i].row;
			spm_sum[k].col=spm1[i].col;
			spm_sum[k].val=spm1[i].val;
			k++; i++;
		}
		else if ((col*spm1[i].row+spm1[i].col)>(col*spm2[j].row+spm2[j].col)) {
			spm_sum[k].row=spm2[j].row;
			spm_sum[k].col=spm2[j].col;
			spm_sum[k].val=spm2[j].val;
			k++; j++;
		}
		else {
			spm_sum[k].row=spm1[i].row;
			spm_sum[k].col=spm1[i].col;
			spm_sum[k].val=spm1[i].val+spm2[j].val;
			k++; i++; j++;
		}
	}
	while (i<=spm1[0].val) {
		spm_sum[k].row=spm1[i].row;
		spm_sum[k].col=spm1[i].col;
		spm_sum[k].val=spm1[i].val;
		k++;i++;
	} //while
	while (j<=spm2[0].val) {
		spm_sum[k].row=spm2[j].row;
		spm_sum[k].col=spm2[j].col;
		spm_sum[k].val=spm2[j].val;
		k++;j++;
	} // while
	spm_sum[0].val=k-1;
	return spm_sum;
}
sparse *transpose_sparse(sparse *spm1) {
	int i, pos, row, col;
	int *row_elem=(int*)malloc(spm1[0].col*sizeof(int));
	int *start_pos=(int*)malloc(spm1[0].col*sizeof(int));
	sparse *spm2;
	row=spm1[0].row; col=spm1[0].col;
	if (spm1[0].val==0) {
		spm2=spm1;
		return spm2;
	}
	spm2=init_sparse(col,row);
	spm2[0].val=spm1[0].val;
	for (i=0; i<spm1[0].col; i++) row_elem[i]=0;
	for (i=1; i<=spm1[0].val; i++) row_elem[spm1[i].col]++;
	start_pos[0]=1;
	for (i=1; i<spm1[0].col; i++) {
		start_pos[i]=start_pos[i-1]+row_elem[i-1];
	}
	for (i=1; i<=spm1[0].val; i++) {
		pos=start_pos[spm1[i].col]++;
		spm2[pos].col=spm1[i].row;
		spm2[pos].row=spm1[i].col;
		spm2[pos].val=spm1[i].val;
	}
	return spm2;
}
sparse *multiply_const(sparse *spm, int constant) {
	int i;
	int row=spm[0].row, col=spm[0].col;
	int limit=1+(row*col)/4;
	sparse *spm_new=init_sparse(row,col);
	if (constant==0 || spm[0].val==0) { // result will be null matrix
		return spm_new;
	}
	//printf ("%d %d %d\n",row,col,spm1[0][2]);
	
	spm_new[0].val=spm[0].val;
	for (i=1; i<=spm[0].val; i++) {
		spm_new[i].row=spm[i].row;
		spm_new[i].col=spm[i].col;
		spm_new[i].val=constant*spm[i].val;
		printf ("%f %f\n",spm[i].val,spm_new[i].val);
	}
	return spm_new;
}

sparse *multiply(sparse *spm1,sparse *spm2){ // CHECK
    sparse *spm22, *spm3; 
    int i,j,k,row1,col2,i1,sum,t1,t2,limit; 
    t1=spm1[0].val;t2=spm2[0].val; 
    if(spm1[0].col!=spm2[0].row){ 
        printf("Incompatible for multiplication\n"); 
        return; 
    }
    //init_sparse(spm3,spm1[0][0],spm2[0][1]);
    printf ("%d %d\n",spm1[0].row,spm2[0].col);
    spm3=init_sparse(spm1[0].row,spm2[0].col);
    printf ("this %d %d\n",spm3[0].row,spm3[0].col);
    limit=1+(spm1[0].row*spm2[0].col/4);
	spm22=transpose_sparse(spm2);
    //transpose_sparse(spm2,&spm22);   
    k=1;       //index for b3 
    i=1; 
    while(i<=t1){ 
        i1=i; 
        j=1; 
        while(j<=t2){ 
            row1=spm1[i].row; 
            col2=spm22[j].row; 
            sum=0; 
			while(i<=t1 && j<=t2 && row1==spm1[i].row && col2==spm22[j].row){ 
    	        if(spm1[i].col==spm22[j].col) { 
        	        sum=sum+spm1[i].val*spm22[j].val; 
            	    i++;j++; 
            	} 
            	else if(spm1[i].col<spm22[j].col) 
                	i++; 
            	else 
                	j++; 
        	}	 
        	if(fabs(sum)>=0.000001){
				if (k>=limit) {
        			printf ("Overflow");
        			return;
				};
            	spm3[k].row=row1; 
            	spm3[k].col=col2; 
            	spm3[k].val=sum; 
            	k++;
        	}	 
        	if(j<=t2) 
            	i=i1; 
       		while(col2==spm22[j].row && j<=t2) 
            j++; 
    	}	 
    	while(row1==spm1[i].row && i<=t1) 
       	i++; 
	} 
    spm3[0].val=k-1; 
    printf ("returning");
    return spm3;
}

int main(void) {
	//sparse *sp, *sp1, *sp2, *sum, *t;
	//sp=create_sparse();
	sparse *pool[MAX_TERMS];
	int next_index=0, index1, index2, choice, cons, flag=1;
	//display_sparse(sp);
	//sp1=create_sparse();
	//display_sparse(sp1);
	//t=multiply(sp,sp1);
	//display_sparse(t);
	//sum=add_sparse(sp,sp1);
	//display_sparse(sum);
	//t=transpose_sparse(sp);
	//t=multiply_const(sp,3);
	//display_sparse(t);
	//sp2=create_sparse();
	//t=multiply(sp1,sp2);
	//display_sparse(t);
	//return 0;
	/*
	int **sp1, **sp2, **sp3;
	int m_no, cons, choice;
	printf ("SPARSE MATRIX OPEARTIONS\n");
	sp1=(int**)malloc(sizeof(int*));
	sp2=(int**)malloc(sizeof(int*));
	sp3=(int**)malloc(sizeof(int*));
	printf ("Enter Matrix 1:\n");
	create_sparse(&sp1);
	printf ("Enter Matrix 2:\n");
	create_sparse(&sp2);
	*/
	while (flag) {
		printf ("MENU:\n");
		printf ("1. Add Matrices\n2. Multiply a Matrix with a constant\n3. Multiply 2 Matrices\n4. Transpose a Matrix\n5. Create a new Matrix\n6. Display a Matrix\n0. Exit\n");
		printf ("Enter your choice: \n");
		scanf ("%d",&choice);
		switch(choice) {
			case 1: printf ("Enter Matrix numbers to be added:\n");
					scanf ("%d %d",&index1,&index2);
					pool[next_index]=add_sparse(pool[index1],pool[index2]);
					next_index++;
					break;
			case 2: printf ("Enter the matrix number to be multiplied with a constant, and the constant to be multiplied with:\n");
					scanf ("%d %d",&index1,&cons);
					pool[next_index]=multiply_const(pool[index1],cons);
					next_index++;
					break;
			case 3: printf ("Enter Matrix numbers to be multiplied:\n");
					scanf ("%d %d",&index1,&index2);
					pool[next_index]=multiply(pool[index1],pool[index2]);
					next_index++;
					break;
			case 4: printf ("Enter the matrix number to be transposed:\n");
					scanf ("%d",&index1);
					pool[next_index]=transpose_sparse(pool[index1]);
					printf ("Transpose of Matrix %d stored in Matrix %d\n",index1,next_index);
					next_index++;
					break;
			case 5: printf ("Enter Matrix %d\n",next_index);
					pool[next_index]=create_sparse();
					next_index++;
					break;
			case 6: printf ("Enter Matrix number to be displayed:\n");
					scanf ("%d",&index1);
					display_sparse(pool[index1]);
					break;
			case 0: exit(1);
			default: printf ("Invalid Choice\n");
		}
	}
	

}




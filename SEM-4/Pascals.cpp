/*
PASCAL'S TRIANGLE
*/
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

class pascal {
	int size;
	void fill_pascal(int*&,int);
	public:
	double combination(int,int);
	explicit pascal(int insize=0) {
		size=insize;
	}
	void display_iter();
	void display_comb();
};
void pascal::fill_pascal(int*& arr, int len) {
	arr[0]=1;
	for (int i=len-1; i>0; i--) {
		arr[i]=arr[i]+arr[i-1]; // next value of sequence calculated from previous step
	}
}
double  pascal::combination(int n, int k) {
	double c_value=1.0;
	for (int i=n; i>n-k; i--) {
		c_value*=(double)i/(double)(k+i-n);
	} 
	return c_value;
}
void pascal::display_iter() {
	int *line=(int*)calloc(size,sizeof(int));
	int i;
	for (i=0; i<size; i++) {
		
		line[0]=1;
		for (int j=0; j<size-i+1; j++) cout << "  "; // pre-sequence space
		for (int j=0; j<size; j++) {
			if (line[j]!=0)
			cout << setw(3) << line[j] << " "; // generate terms using terms of previous level
		}
		fill_pascal(line,size);
		cout << endl;
	}
}
void pascal::display_comb() {
	for (int i=0; i<size; i++) {
		for (int j=0; j<size-i+1; j++) cout << "  "; // pre-sequence space
		for (int j=0; j<=i; j++) {
			cout << setw(3) << combination(i,j) << " "; // generate terms using combination function
		}
		cout << endl;
	}
}
int main() {
	pascal p;
	int choice, flag=1, size;
	while (flag) {
		cout << "1. Display Pascals's triangle using iterative method\n2. Display Pascals's triangle using combination method\n0. Exit" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "Enter size: " << endl;
					cin >> size;
					p=pascal(size);
					p.display_iter();
					cout << endl;
					break;
			case 2: cout << "Enter size: " << endl;
					cin >> size;
					p=pascal(size);
					p.display_comb();
					cout << endl;
					break;
			case 0: flag=0;
					break;
			default: cout << "Invalid choice" << endl;
		}
	}
	return 0;

}	

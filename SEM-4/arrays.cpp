#include <iostream>
#include <cstdlib>
#define MIN(a,b) ((a)<(b))?(a):(b)
#define MAX(a,b) ((a)>(b))?(a):(b)
using namespace std;

class Array {
	double *arr=NULL;
	int len;
	public:
	Array(int,double);
	Array(const Array&);
	Array(const double*, int);
	~Array();
	int length() const {return len;}
	double &operator[](int);
	void operator=(Array);
	Array operator+(Array&);
	Array operator*(double);
	friend Array operator*(double,Array&);
};
Array::Array(int size=0, double def=0.0) {
	if (arr) {// already space allocated
		delete arr;
		len=0;
	}
	len=0;
	if(size<0) {
		cout << "Array memory allocation error" << endl;
	}
	else if(size>0) {
		len=size;
		arr=new double[len];
		for (int i=0; i<len; i++)
		arr[i]=def;
	}
	//cout << "Array created with size: " << len << endl;
}
Array::Array(const Array& array) {
	//cout << "copy" << endl;
	//if (len) {// already space allocated
		//cout << "length is: " << len << " :" << (arr==NULL) << endl;
	if (arr) {
		cout << "must delete" << endl;
		delete arr; // the reason why arr was initialized earlier, else segfaault (uninitialized pointer)
		
		//cout << "deleted" << endl;
		len=0;
		//cout << "space cleared" << endl;
	}
	//}
	if((len=array.length())) { // allocate space equal to array
		//cout << "copying" << endl;
		arr=new double[len];
		for (int i=0; i<len; i++)
		arr[i]=array.arr[i];
	}
	//cout << "copy end" << endl;
}
Array::Array(const double *array, int size) {
	if (arr) {// already space allocated
		delete arr;
		len=0;
	}
	len=0;
	if (size<0) {
		cout << "Array memory allocation error" << endl;
	}
	else if(size>0) {
		len=size;
		arr=new double[len];
		for (int i=0; i<len; i++)
		arr[i]=array[i];
	}
}
Array::~Array() {
	if (arr) {
		len=0;
		delete arr;
	}
}
double& Array::operator[](int index) {
	if (index>=len) {
		cout << "Array index out of bounds: " << index << " "<< endl;
	}
	return arr[index];
}
void Array::operator=(Array array) {
	if (arr) {// already space allocated
		delete arr;
		len=0;
	}
	if((len=array.length())) { // allocate space equal to array
		arr=new double[len];
		for (int i=0; i<len; i++)
		arr[i]=array[i];
	}
}
//CHECK ERROR
Array Array::operator+(Array& array) { // in case of size mismatch, sum will be size of larger array
	int len2, min, max, i;
	len2=array.length();
	min=MIN(len,len2);
	max=MAX(len,len2);
	Array sum(max);
	for (i=0; i<len && i<len2; i++) {
		sum[i]=array[i]+arr[i];
		//sum[i]=sum[i]+arr[i];
	}
	for (; i<len; i++) sum[i]=arr[i];
	for (; i<len2; i++) sum[i]=array[i];
	return sum;
}
Array Array::operator*(double mul) {
	Array pdt=*this;
	//cout << pdt.length();
	if (pdt.length()) {
		for (int i=0; i<pdt.length(); i++) {
			pdt[i]=pdt[i]*mul;
		}
	
	}
	return pdt;	
}
Array operator*(double mul, Array& array) {
	//cout << "xxx" << array.length();
	Array pdt(0);
	pdt=array;
	//Array pdt=array;
	if (pdt.length()) {
		//cout << "pdt length is: " << pdt.length();
		for (int i=0; i<pdt.length(); i++) {
			//cout << "yyy";
			pdt[i]=pdt[i]*mul;
		}
	}
	return pdt;	
}
int main() {
	Array a(5,0), b(3,1);
	Array c=a+b;
	/*
	Array a,b,c;
	int n,m,flag=1, i;
	char ch;
	double mul,def;
	cout << "Enter size of first array: " << endl;
	cin >> n;
	cout << "Initialize with default value? (Y/N) " << endl;
	cin >> ch;
	if (ch=='Y') {
		cout << "Enter default value: " << endl;
		cin >> def;
		a=Array(n,def);
	}
	else if (ch=='N') {
		a=Array(n);
		cout << "Enter array elements: " << endl;
		for (i=0; i<n; i++) cin >> a[i];
	}
	cout << "Enter size of second array: " << endl;
	cin >> m;
	cout << "Initialize with default value? (Y/N) " << endl;
	cin >> ch;
	if (ch=='Y') {
		cout << "Enter default value: " << endl;
		cin >> def;
		b=Array(m,def);
	}
	else if (ch=='N') {
		b=Array(m);
		cout << "Enter array elements: " << endl;
		for (i=0; i<m; i++) cin >> b[i];
	}
	int choice, index;
	while (flag) {
		cout << "MENU:" << endl;
		cout << "1. Add 1st and 2nd array\n2. Assign a new array with an existing array\n3. Pre multiply an array with a constant\n4. Post multiply an array with a constant\n5. Initialize an array\n0. Exit\n" << endl;
		cout << "Enter Your Choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: c=a+b;
					cout << "Sum: " << endl;
					for (i=0; i<c.length(); i++) {
						cout << c[i] << " ";
					}
					cout << endl;
					break;
			case 2: cout << "Enter array number (1 or 2) " << endl;
					cin >> index;
					if (index==1) c=a;
					else if (index==2) c=b;
					else cout << "Wrong input" << endl;
					for (i=0; i<c.length(); i++) {
						cout << c[i] << " ";
					}
					cout << endl;
					break;
			case 3: cout << "Enter array number (1 or 2) " << endl;
					cin >> index;
					cout << "Enter multiplier" << endl;
					cin >> mul;
					if (index==1) c=mul*a;
					else if (index==2) c=mul*b;
					else cout << "Wrong input" << endl;
					for (i=0; i<c.length(); i++) {
						cout << c[i] << " ";
					}
					cout << endl;
					break;
			case 4: cout << "Enter array number (1 or 2) " << endl;
					cin >> index;
					cout << "Enter multiplier" << endl;
					cin >> mul;
					if (index==1) c=a*mul;
					else if (index==2) c=b*mul;
					else cout << "Wrong input" << endl;
					for (i=0; i<c.length(); i++) {
						cout << c[i] << " ";
					}
					cout << endl;
					break;
			case 5: cout << "Enter array number (1 or 2) " << endl;
					cin >> index;
					if (index==1) {
						cout << "Enter size of array 1: " << endl;
						cin >> n;
						a=Array(n);
						cout << "Enter array elements: " << endl;
						for (i=0; i<n; i++) {
							cin >> a[i];
						}
					}
					else if (index==2) {
						cout << "Enter size of array 2: " << endl;
						cin >> m;
						b=Array(m);
						cout << "Enter array elements: " << endl;
						for (i=0; i<m; i++) {
							cin >> b[i];
						}
					}
					else cout << "Wrong input" << endl;
					break;
			case 0: flag=0;
					break;
			default: cout << "Invalud input" << endl;
			

		}
	}
	/*
	cout << "Enter sizes of 2 arrays:" << endl;
	int n, m;
	cin >> n >> m;
	Array a(n), b(m);
	for (int i=0; i<n; i++) cin >> a[i];
	for (int i=0; i<m; i++) cin >> b[i];
	Array c;
	//cout << "hhh";
	c=a+b;
	//cout << "hhh";
	cout << "a+b: " << endl;
	for (int i=0; i<c.length(); i++) {
		cout << c[i] << " ";
	}
	cout << endl;
	c=a*5;
	cout << "a*5: " << endl;
	for (int i=0; i<c.length(); i++) {
		cout << c[i] << " ";
	}
	cout << endl;
	c=6*a;
	cout << "6*a: " << endl;
	for (int i=0; i<c.length(); i++) {
		cout << c[i] << " ";
	}
	double *ar=new double[4];
	for (int i=0; i<4; i++) ar[i]=i+0.2;
	
	Array d(ar,4);
	for (int i=0; i<4; i++) cout << d[i];
	//cout << a.length() << " " << b.length() << " " << c.length() << " " << d.length() << " " << e.length() << endl;
	*/
	return 0;
	
}

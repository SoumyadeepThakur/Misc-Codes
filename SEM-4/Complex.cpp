#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <sstream>
#define MAX_TERMS 10001
using namespace std;

class complex{
	int re, im;
	public:
	complex(int,int);
	double abs_value();
	friend ostream& operator<<(ostream&, const complex); // must be friend because first argument is ostream not complecx
	friend istream& operator>>(istream&, complex&);
	complex operator+(complex); 
	complex operator-(complex); 
	friend complex operator+(int,complex);
};
complex::complex(int r=0, int i=0) {
	re=r;
	im=i;
}
double complex::abs_value() {
	double abs;
	//cout << re << " " << im << endl;
	abs=sqrt((double)(re*re+im*im));
	//cout << abs;
	return abs;
}
istream& operator>>(istream& in, complex& cplx) {
	string instr, re, im;
	int pos;
	bool sign=false;
	cin.ignore(256,'\n');
	getline(in,instr);
	pos=instr.find('i');
	if (pos==-1) { // input is purely real
		cplx=atoi(instr.c_str());
	}
	else if (pos==0) { // purely imaginary with +ve im part
		cplx=complex(0,atoi(instr.substr(1).c_str()));
	}
	else if (pos==1) { // purely imaginary with -ve im part
		im=instr.substr(pos+1);
		if (instr.at(pos-1)=='-') sign=true;
		im=(sign)?("-"+im):im;
		cplx=complex(0,atoi(im.c_str()));
	}
	else {
		re=instr.substr(0,pos-1);
		im=instr.substr(pos+1);
		if (instr.at(pos-1)=='-') sign=true;
		im=(sign)?("-"+im):im;
		cplx=complex(atoi(re.c_str()),atoi(im.c_str()));
	}
	return in;
}
ostream& operator<<(ostream& out, const complex cplx) {
	char sign='+';
	if (cplx.im<0) sign='-';
	if (cplx.im==0) out << cplx.re;
	else if (cplx.re==0) {
		if (sign=='+') sign=' ';
		out << sign << "i" << fabs(cplx.im);
	}
	else out << cplx.re << sign << "i" << fabs(cplx.im);
	return out;
}
complex complex::operator+(complex cplx) {
	complex sum(re+cplx.re,im+cplx.im);
	return sum;
}
complex complex::operator-(complex cplx) {
	complex sum(re-cplx.re,im-cplx.im);
	return sum;
}
complex operator+(int r, complex cplx) {
	complex sum(cplx.re+r,cplx.im);
	return sum;
}

int main(void) {
	complex term[MAX_TERMS];
	int next=0, index1, index2, choice;
	double abs;
	while (true) {
		cout << "1. Create a complex number\n2. Add 2 complex numbers\n3. Subtract a complex number from another\n4. Find absolute value of the complex number\n5. Display a complex number\n0. Exit\n" << endl;
		cout << "Enter Your Choice:" << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "Enter complex number " << next+1 << endl;
					//term[next]=complex(0,0);
					cin >> term[next];
					next++;
					break;
			case 2: cout << "Enter the complex numbers to be added:" << endl;
					cin >> index1;
					cin >> index2;
					cout << "Sum is stored as complex number " << next+1 << endl;
					term[next]=term[index1-1]+term[index2-1];
					next++;
					break;
			case 3: cout << "Enter the complex number to be subtracted and the complex number from which it is to be subtracted:" << endl;
					cin >> index1;
					cin >> index2;
					cout << "Sum is stored as complex number " << next+1 << endl;
					term[next]=term[index2-1]-term[index1-1];
					next++;
					break;
			case 4: cout << "Enter the complex number: " << endl;
					cin >> index1;
					abs=term[index1-1].abs_value();
					cout <<  abs << endl;
					break;
			case 5: cout << "Enter the complex number to be displyaed:" << endl;
					cin >> index1;
					cout << term[index1-1] << endl;
					break;
			case 0: exit(1);
			default: cout << "Invalid Choice";
		}
		
	}
}

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class mystring {
	char *str=NULL;
	int size;
	public:
	mystring(int);
	mystring(const mystring&);
	mystring(const char*);
	~mystring();
	int length() const {return size;}
	char &operator[](int);
	void operator=(mystring);
	mystring operator+(mystring&);
	bool operator==(mystring&);
	bool operator!=(mystring&);
	bool operator<=(mystring&);
	bool operator>=(mystring&);
	bool operator<(mystring&);
	bool operator>(mystring&);
	friend ostream& operator<<(ostream&,mystring&);
};
mystring::mystring(int len=0) {
	cout << "1" << endl;
	size=0;
	if (str) {
		delete str;
		size=0;
	}
	if (len==0) {
		str=NULL;
		size=0;
	}
	else if(len<0) {
		cout << "Array memory allocation error" << endl;
	}
	else if(len>0) {
		size=len;
		str=new char[size+1];
		for (int i=0; i<len; i++)
		str[i]='\0';
		str[size]='\0';
	}	
	//cout << "Array created with size: " << len << endl;
}
mystring::mystring(const mystring& instr) {
	cout << "2" << endl;
	if (str) {
		delete str;
		size=0;
	}
	if((size=instr.length())) { // allocate space equal to array
		cout << "copying" << endl;
		str=new char[size+1];
		for (int i=0; i<size; i++)
		str[i]=instr.str[i];
		str[size]='\0';
	}
}
mystring::mystring(const char *instr) {
	cout << "3" << endl;
	int len=strlen(instr);
	
	if (str) {// already space allocated
		delete str;
		size=0;
	}
	size=0;
	if (len==0) {
		str=NULL;
		size=0;
	}
	else if (len<0) {
		cout << "Array memory allocation error" << endl;
	}
	else if(len>0) {
		size=len;
		str=new char[len+1];
		for (int i=0; i<len; i++)
		str[i]=instr[i];
		str[len]='\0';
	}
}
mystring::~mystring() {
	if (str) {
		size=0;
		delete str;
	}
}
void mystring::operator=(mystring mstr) {
	if (str) {// already space allocated
		delete str;
		size=0;
	}
	if((size=mstr.length())) { // allocate space equal to array
		str=new char[size+1];
		for (int i=0; i<size; i++)
		str[i]=mstr[i];
		str[size]='\0';
	}
	
}
char& mystring::operator[](int index) {
	if (index>=size) {
		cout << "String index out of bounds: " << index << " "<< endl;
	}
	return str[index];
}
ostream& operator<<(ostream& out, mystring& mstr) {
	//out << "halu" << endl;
	out << mstr.str;
	return out;
}
mystring mystring::operator+(mystring& mstr) {
	int con_len=length()+mstr.length(), j=0;
	mystring concat(con_len);
	for (int i=0; i<length(); i++) concat[j++]=str[i];
	for (int i=0; i<mstr.length(); i++) concat[j++]=mstr[i];
	return concat;
}
bool mystring::operator==(mystring& mstr) {
	if (strcmp(str,mstr.str)==0) return true;
	return false; 
}
bool mystring::operator!=(mystring& mstr) {
	if (strcmp(str,mstr.str)==0) return false;
	return true; 
}
bool mystring::operator<=(mystring& mstr) {
	if (strcmp(str,mstr.str)<=0) return true;
	return false; 
}
bool mystring::operator>=(mystring& mstr) {
	if (strcmp(str,mstr.str)>=0) return true;
	return false; 
}
bool mystring::operator<(mystring& mstr) {
	if (strcmp(str,mstr.str)<0) return true;
	return false; 
}
bool mystring::operator>(mystring& mstr) {
	if (strcmp(str,mstr.str)>0) return true;
	return false; 
}
int main() {
	mystring a,b,c;
	int n,m,flag=1, i;
	char ch, text[101];
	double mul,def;
	//cout << "Enter size of first string: " << endl;
	//cin >> n;
	cout << "Enter 1st string(as character array): " << endl;
	cin.getline(text,100);
	a=mystring(text);
	cout << "Enter 2nd string(as character array): " << endl;
	cin.getline(text,100);
	b=mystring(text);
	int choice, index;
	while (flag) {
		cout << "MENU:" << endl;
		cout << "1. Concat 1st and 2nd array\n2. Assign a new string with an existing string\n3. Compare 1st and 2nd strings\n4. Initialize a string\n0. Exit\n" << endl;
		cout << "Enter Your Choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: c=a+b;
					cout << "Concat: " << endl;
					cout << c << endl;
					break;
			case 2: cout << "Enter string number (1 or 2) " << endl;
					cin >> index;
					if (index==1) c=a;
					else if (index==2) c=b;
					else cout << "Wrong input" << endl;
					for (i=0; i<c.length(); i++) {
						cout << c[i] << " ";
					}
					cout << endl;
					break;
			case 3: cout << "1 indicates true, 0 indicates false" << endl;
					cout << "'a' is the 1st string, 'b' is the 2nd string" << endl; 
					cout << "a==b: " << (a==b) << endl;
					cout << "a!=b: " << (a!=b) << endl;
					cout << "a<=b: " << (a<=b) << endl;
					cout << "a>=b: " << (a>=b) << endl;
					cout << "a<b: " << (a<b) << endl;
					cout << "a>b: " << (a>b) << endl;
					break;
			case 4: cout << "Enter array number (1 or 2) " << endl;
					cin >> index;
					if (index==1) {
						cout << "Enter string 1: " << endl;
						cin.ignore(4,'\n');
						cin.getline(text,100);
						a=text;
					}
					else if (index==2) {
						cout << "Enter string 2: " << endl;
						cin.ignore(4,'\n');
						cin.getline(text,100);
						b=text;
					}
					else cout << "Wrong input" << endl;
					break;
			case 0: flag=0;
					break;
			default: cout << "Invalud input" << endl;
			

		}
	}
	return 0;
}


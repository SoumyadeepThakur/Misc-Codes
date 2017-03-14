#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

class strings {
	int size;
	int *cp; // count of objects pointing to that string
	char *str;
	public:
	strings(int s=0) {
		size=s;
		if (s==0) {
			cp=NULL;
			str=NULL;
		}
		else {
			str=new char[size+1];
			cp=new int(1);
			str[0]='\0';
		}
	}
	strings(char *t) {
		size=0;
		if (t!=NULL) {
			size=strlen(t);
			str=new char[size+1];
			cp=new int(1);
		}
		else {
			str=NULL;
			cp=NULL;
		}
	}
	strings(const strings& s) {
		size=s.size;
		cp=s.cp;
		str=s.str;
		if(cp!=NULL) *cp=*cp+1;
	}
	~strings() {
		if (str!=NULL) {
			*cp=*cp-1;
			if (*cp==0) {
				delete cp;
				delete str;
			}
		}
	}
	void operator=(strings s);
	void display();
};
void strings::operator=(strings s) {
	if(str!=NULL) { // clear the pointer to the string it originally points to
		*cp=*cp-1;
		if (*cp==0) {
			delete str;
			delete cp;
		}
			
	}
	size=s.size;
	cp=s.cp;
	str=s.str;
	if (cp!=NULL) *cp=*cp+1;
}
void strings::display() {
	cout << str << "\t"<< size << "\t" << *cp << "\n"; 
}
int main(void) {
	strings a("abc");
	a.display();
	strings b=a;
	b.display();
	return 0;
}


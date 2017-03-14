#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>
#define CAPACITY 100
#define MAX_ISSUES 100
#define STUDENT_MAX 2
using namespace std;

class library;
class date {
	int day, month, year;
	public:
	date() {
		day=1;
		month=1;
		year=1970;
	}
	date(int dd, int mm, int yy) {
		day=dd;
		month=mm;
		year=yy;
	}
	friend ostream& operator<<(ostream&,date);
	static bool is_valid_date(date); 
	static date get_system_date();
	static int days_elapsed(date,date);
};
ostream& operator<<(ostream& out, date dat) {
	out << setfill('0') << setw(2) << dat.day << "/" << setfill('0') << setw(2) << dat.month << "/" << setfill('0') << setw(4) << dat.year;
	return out;
}
date date::get_system_date() {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[12];
	int dd, mm, yy;
	date sysdate;
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,12,"%d/%m/%Y",timeinfo); // estract system time
	string cur_date(buffer);
	dd=atoi(cur_date.substr(0,2).c_str()); // extract day
	mm=atoi(cur_date.substr(3,2).c_str()); // extract month
	yy=atoi(cur_date.substr(6).c_str()); // extract year
	sysdate=date(dd,mm,yy);
	return sysdate;
}
bool date::is_valid_date(date dat) {
	date sysdate=date::get_system_date();
	if (dat.year<1970 || dat.year>2079) return false; // invalid year
	else if (dat.month<1 || dat.month>12) return false; // invalid month
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap=false;
	if (dat.year%400==0 || (dat.year%100!=0 && dat.year%4==0)) leap=true; // check leap year
	if (leap) days[2]++;
	if (dat.day<1 || dat.day>days[dat.month]) return false;
	if (dat.year>sysdate.year || (dat.year==sysdate.year && dat.month>sysdate.month) || (dat.year==sysdate.year && dat.month==sysdate.month && dat.day>sysdate.day)) // future date
	return false;
	return true;
}
int date::days_elapsed(date beg, date end) {
	int sd=beg.day, sm=beg.month, sy=beg.year;
	int fd=end.day, fm=end.month, fy=end.year;
	int days=0;
	int mnth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (sy%400==0 || (sy%100!=0 && sy%4==0)) mnth[2]=29;
	else mnth[2]=28;
	while (!(sd==fd && sm==fm && sy==fy)) {
		sd++;
		if (sd>mnth[sm]) {
			sm++;
			sd=1;
			if (sm>12) {
				sm==1;
				sy++;
				if (sy%400==0 || (sy%100!=0 && sy%4==0)) mnth[2]=29;
				else mnth[2]=28;
			}
		}
		days++;
	}
	return days;
}		
class book {
	string name, code;
	void set_details();
	public:
	void show_details() const;
	friend class library;
};
class journal {
	string name,journ_issue_no;
	date date_of_publish;
	int volume_no;
	void set_details();
	public:
	void show_details() const;
	friend class library;
};
/*
class journal {
	string name, code;
	int issue_no, vol_no;
	void set_details();
	void show_details() const;
};
*/
class issue {
	int issue_no, no_days, returned;
	date issue_date;
	double fine;
	char issue_type, issued_by;
	string b_code, j_code;
	public:
	issue(){no_days=30; returned=0; fine=0.0;}
	void submit_slip();
	void set_fine();
	friend class library;
};
class library {
	int no_books, no_journals, no_issues;
	issue issues[MAX_ISSUES];
	book books[CAPACITY];
	int book_quantity[CAPACITY];
	journal journals[CAPACITY];
	public:
	library() {
		no_books=0; no_journals=0; no_issues=0;
	}
	void init_library();
	int search_book(string) const;
	int search_issue(int) const;
	int search_journal(string) const;
	void issue_book(char);
	void return_book();
	void issue_journal();
};

void book::set_details() {
	cout << "Enter name of the book:" << endl;
	cin.ignore(256,'\n');
	getline(cin,name);
	cout << "Enter code of the book:" << endl;
	cin >> code;
}
void book::show_details() const {
	cout << "Book Name: " << name << endl;
	cout << "Book Code: " << code << endl;
}
void journal::set_details() {
	string publ;
	int dd, mm, yy;
	cout << "Enter name of the journal:" << endl;
	cin.ignore(256,'\n');
	getline(cin,name);
	cout << "Enter issue number of the journal:" << endl;
	cin >> journ_issue_no;
	cout << "Enter volume number: " << endl;
	cin >> volume_no;
	cout << "Enter date of publication: " << endl;
	cin.ignore(256,'\n');
	getline(cin,publ);
	dd=atoi(publ.substr(0,2).c_str());
	mm=atoi(publ.substr(3,2).c_str());
	yy=atoi(publ.substr(6).c_str());
	date_of_publish=date(dd,mm,yy);
}
void journal::show_details() const {
	cout << "Journal Name: " << name << endl;
	cout << "Journal Issue Number: " << journ_issue_no << endl;
	cout << "Journal Volume Number: " << volume_no << endl;
	cout << "Journal Publication Date: " << date_of_publish << endl;
}
void issue::set_fine() {
	fine=0.0;
	date cur=date::get_system_date();
	int days=date::days_elapsed(issue_date,cur);
	cout << days << endl;
	if (issued_by=='S') {
		fine=1.0*(days-30);
		if (fine<0) fine=0.0;
	}
}	
void library::init_library() {
	int ch, quant, flag=1;
	book bk; journal jn;
	while (flag) {
		cout << "Press 1 to add books.\nPress 2 to add journals\nPress any other key to stop" << endl;
		cin >> ch;
		switch (ch) {
			case 1: bk.set_details();
					books[no_books]=bk;
					cout << "Enter quantity: " << endl;
					cin >> quant;
					book_quantity[no_books]=quant;
					no_books++;
					break;
			case 2: jn.set_details();
					journals[no_journals]=jn;
					no_journals++;
					break;
			default: flag=0;
					 break;
		}
	}
}
int library::search_book(string bcode) const{
	int pos=-1;
	for (int i=0; i<no_books; i++) {
		if (bcode.compare(books[i].code)==0) {
			pos=i;
			break;
		}
	}
	return pos;
}
int library::search_journal(string jcode) const{
	int pos=-1;
	for (int i=0; i<no_journals; i++) {
		if (jcode.compare(journals[i].journ_issue_no)==0) {
			pos=i;
			break;
		}
	}
	return pos;
}
int library::search_issue(int ino) const{
	int pos=-1;
	for (int i=0; i<no_issues; i++) {
		if (ino==issues[i].issue_no) {
			pos=i;
			break;
		}
	}
	return pos;
}
void library::issue_book(char iss_by) {
	string bcode;
	cout << "Enter code of book to be issued: " << endl;
	cin >> bcode;
	int pos=search_book(bcode);
	if (pos==-1) {
		cout << "Book not in stock" << endl;
		cout << "Try again later!" << endl;
	}
	else {
		book issued=books[pos];
		if (book_quantity[pos]==0) {
			cout << "Not enough books in stock! " << endl;
			return;
		}
		issued.show_details(); // correct
		//cout << "found" << endl;
		issues[no_issues]=issue();		
		issue &temp=issues[no_issues];
		temp.issue_no=no_issues+1;
		temp.issue_type='B';
		temp.issued_by=iss_by;
		temp.issue_date=date::get_system_date();
		temp.b_code=bcode;
		book_quantity[pos]--;
		cout << "Book Issued" << endl;
		cout << "Issue Number: " << temp.issue_no << endl;
		if (iss_by=='S')
		cout << "Return within 30 days" << endl;
		no_issues++;
	}
}
void library::return_book() {
	int icode;
	cout << "Enter issue number of book to be returned: " << endl;
	cin >> icode;
	int pos=search_issue(icode);
	if (pos==-1) {
		cout << "Invalid Issue" << endl;
	}
	else {
		issue& temp=issues[pos];
		temp.returned=1;
		temp.set_fine();
		int pos_bk=search_book(temp.b_code);
		book_quantity[pos_bk]++;
		cout << "Book Returned" << endl;
		if (temp.issued_by=='S')
		cout << "Fine: Rs. " << temp.fine << endl;
	}
}
void library::issue_journal() {
	string jcode;
	cout << "Enter issue number of journal to be issued: " << endl;
	cin >> jcode;
	int pos=search_journal(jcode);
	if (pos==-1) {
		cout << "Journal not in stock" << endl;
		cout << "Try again later!" << endl;
	}
	else {
		journal issued=journals[pos];
		issued.show_details(); // correct
		//cout << "found" << endl;
		issues[no_issues]=issue();		
		issue &temp=issues[no_issues];
		temp.issue_no=no_issues+1;
		temp.issue_type='J';
		temp.issued_by='F';
		temp.issue_date=date::get_system_date();
		temp.j_code=jcode;
		cout << "Journal Issued" << endl;
		cout << "Issue Number: " << temp.issue_no << endl;
		no_issues++;
	}
}

int main(void) {
	library lib;
	cout << "Store books and journals in the library" << endl;
	lib.init_library();
	int next=0, stop, choice, flag=1, i;
	char type;
	string rno;
	while (flag) {
		cout << "1. Issue Book\n2. Issue Journal\n3. Return Book\n0. Exit\n" << endl;
		cout << "Enter Your Choice:" << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "Enter user type: Student/Faculty (S/F) " << endl;
					cin >> type;
					if (type=='S') {
						cout << "Maximum 2 books can be issued at a time" << endl;
						for (i=1; i<=2; i++) {
							cout << "Pess 1 to issue more. Press 0 to stop" << endl;
							cin >> stop;
							if (stop==0) break;
							lib.issue_book('S');
						}
						
					}
					else if (type=='F') {
						cout << "Maximum 10 books can be issued at a time" << endl;
						for (i==1; i<=10; i++) {
							cout << "Press 1 to issue more. Press 0 to stop" << endl;
							cin >> stop;
							if (stop==0) break;
							lib.issue_book('F');
						}
					}
					break;
			case 2: lib.issue_journal();
					break;
			case 3: lib.return_book();
					break;
			case 0: flag=0;
					break;
			default: cout << "Invalid Choice" << endl;
		}
	}
	return 0;
}



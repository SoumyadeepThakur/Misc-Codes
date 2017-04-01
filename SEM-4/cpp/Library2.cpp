#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
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
	friend istream& operator>>(istream&, date&);
	static bool is_valid_date(date); 
	static date get_system_date();
	static int days_elapsed(date,date);
};
ostream& operator<<(ostream& out, date dat) {
	out << setfill('0') << setw(2) << dat.day << "/" << setfill('0') << setw(2) << dat.month << "/" << setfill('0') << setw(4) << dat.year;
	return out;
}
istream& operator>>(istream& in, date& dat) {
	string str_date;
	in >> str_date;
	if (str_date.length()<10) {
		return in;
	}
	int dd, mm, yy;
	dd=atoi(str_date.substr(0,2).c_str()); // extract day
	mm=atoi(str_date.substr(3,2).c_str()); // extract month
	yy=atoi(str_date.substr(6).c_str()); // extract year
	//cout << dd << mm << yy << endl;
	dat=date(dd,mm,yy);
	return in;
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
	void add_to_library();
	void load_library();
	void update_library() const;
	void show_register() const;
	int search_book(string) const;
	int search_issue(int) const;
	int search_journal(string) const;
	void issue_book(char);
	void return_book();
	void issue_journal();
	void return_journal();
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
	if (!date::is_valid_date(date_of_publish)) {
		cout << "Invalid date" << endl;
		cout << "Date set to epoch" << endl;
		date_of_publish=date();
	}
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
	if (issued_by=='S') {
		fine=1.0*(days-30);
		if (fine<0) fine=0.0;
	}
}	
void library::add_to_library() {
	int ch, quant, flag=1;
	book bk; journal jn;
	fstream f_bk("books.txt",ios::app);
	fstream f_jn("journals.txt",ios::app);
	while (flag) {
		cout << "Press 1 to add books.\nPress 2 to add journals\nPress any other key to stop" << endl;
		cin >> ch;
		switch (ch) {
			case 1: bk.set_details();
					cout << "Enter quantity: " << endl;
					cin >> quant;
					f_bk << bk.code << endl << bk.name << endl << quant << endl; // add book to file
					no_books++;
					break;
			case 2: jn.set_details();
					f_jn << jn.journ_issue_no << endl << jn.name << endl << jn.date_of_publish << endl << jn.volume_no << endl; // add journal to file
					no_journals++;
					break;
			default: flag=0;
					 break;
		}
	}
	f_bk.close();
	f_jn.close();
}
void library::load_library() {
	int count=0;
	fstream f_bk("books.txt",ios::in);
	while (!f_bk.eof()) { // load books from file to program
		book bk;
		f_bk >> bk.code;
		f_bk.ignore(256,'\n');
		getline(f_bk,bk.name);
		f_bk >> book_quantity[count];
		books[count++]=bk;
	}
	no_books=count-1;
	f_bk.close();
	fstream f_jn("journals.txt",ios::in);
	count=0;
	cout << "Reading Journals" << endl;
	while (!f_jn.eof()) { // load journals from file to program
		journal jn;
		f_jn >> jn.journ_issue_no;
		f_jn.ignore(256,'\n');
		getline(f_jn,jn.name);
		cout << "here" << endl;
		f_jn >> jn.date_of_publish;
		f_jn >> jn.volume_no;
		journals[count++]=jn;
	}
	no_journals=count-1;
	f_jn.close();
	fstream f_is("issues.txt",ios::in);
	count=0;
	cout << "Reading issues" << endl;
	issue is;
	while (f_is!=NULL && !f_is.eof()) { // load issues from file to program
		f_is >> is.issue_no;
		f_is >> is.returned;
		f_is >> is.issue_date;
		f_is >> is.issue_type;
		f_is >> is.issued_by;
		if (is.issue_type=='B') {
			f_is >> is.b_code;
		}
		else if (is.issue_type=='J') {
			f_is >> is.j_code;
		}
		issues[count++]=is;
	}
	no_issues=count-1;
	f_is.close();
	//for (int i=0; i<no_issues; i++) {
	//	cout << is.issue_no << is.no_days << is.returned << is.issue_date << is.fine <<is.issue_type << is.issued_by << is.b_code << is.j_code << endl;
	//}
}
void library::show_register() const {
	cout << "REGISTER: " << endl;
	cout << "Books: " << endl;
	for (int i=0; i<no_books; i++) {
		books[i].show_details();
		cout << endl;
	}
	cout << "Journals: " << endl;
	for (int i=0; i<no_journals; i++) {
		journals[i].show_details();
		cout << endl;
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
		//fstream f_is("issues.txt",ios::app);
		/* Set details of the issue */
		issued.show_details();
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
		// write to file
		//f_is << temp.issue_no << endl << temp.returned << endl << temp.issue_date << endl << temp.issue_type << endl << temp.issued_by << endl << temp.b_code << endl;
		no_issues++;
		//f_is.close();
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
		if (temp.returned==1) {
			cout << "Invaid issue" << endl;
			return;
		}
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
		issued.show_details();
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
void library::return_journal() {
	int icode;
	cout << "Enter issue number: " << endl;
	cin >> icode;
	int pos=search_issue(icode);
	if (pos==-1) {
		cout << "Invalid Issue" << endl;
	}
	else {
		issue& temp=issues[pos];
		if (temp.returned==1) {
			cout << "Invaid issue" << endl;
			return;
		}
		temp.returned=1;
		cout << "Journal Returned" << endl;
	}	
}
void library::update_library() const {
	fstream f_updt("books.txt",ios::out);
	for (int i=0; i<no_books; i++) {
		f_updt << books[i].code << endl << books[i].name << endl << book_quantity[i] << endl; // update details of all books
	}
	f_updt.close();
	f_updt.open("journals.txt",ios::out);
	for (int i=0; i<no_journals; i++) {
		f_updt << journals[i].journ_issue_no << endl << journals[i].name << endl << journals[i].date_of_publish << endl << journals[i].volume_no << endl; // update details of all books
	}
	f_updt.close();
	f_updt.open("issues.txt",ios::out);
	for (int i=0; i<no_issues; i++) {
		f_updt << issues[i].issue_no << endl << issues[i].returned << endl << issues[i].issue_date << endl << issues[i].issue_type << endl << issues[i].issued_by << endl;
		if (issues[i].issue_type=='B') f_updt << issues[i].b_code << endl;
		else if (issues[i].issue_type=='J') f_updt << issues[i].j_code << endl;
	}
	f_updt.close();

}
int main(void) {
	library lib;
	cout << "Store books and journals in the library" << endl;
	lib.add_to_library();
	lib.load_library();
	int next=0, stop, choice, flag=1, i;
	char type;
	string rno;
	while (flag) {
		cout << "1. Issue Book\n2. Issue Journal\n3. Return Book\n4. Return journal\n5. Display Register\n0. Exit\n" << endl;
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
			case 4: lib.return_journal();
					break;
			case 5: lib.show_register();
					break;
			case 0: lib.update_library();
					flag=0;
					break;
			default: cout << "Invalid Choice" << endl;
		}
	}
	return 0;
}



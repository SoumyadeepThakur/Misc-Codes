#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#define NO_OF_SUBJECTS 5
#define MAX_STUDENTS 1001
#define MIN(a,b) ((a)<(b))?(a):(b)
using namespace std;

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
	//friend istream& operator>>(istream&,date&);
	static bool is_valid_date(date); 
};
class student {
	static int no_of_students;
	string name, roll, course;
	int marks_updated=0;
	date admission_date;
	int marks[NO_OF_SUBJECTS];
	public:
	void admission();
	void view_details() const;
	void set_marks();
	void get_marksheet() const;
	friend int search(student*,string,int);
	static int get_total_students() {
		return no_of_students;
	}
};
int student::no_of_students=0;
ostream& operator<<(ostream& out, date dat) {
	out << setfill('0') << setw(2) << dat.day << "/" << setfill('0') << setw(2) << dat.month << "/" << setfill('0') << setw(4) << dat.year;
	return out;
}
bool date::is_valid_date(date dat) {
	if (dat.year<1970 || dat.year>2079) return false;
	else if (dat.month<1 || dat.month>12) return false;
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap=false;
	if (dat.year%400==0 || (dat.year%100!=0 && dat.year%4==0)) leap=true;
	if (leap) days[2]++;
	if (dat.day<1 || dat.day>days[dat.month]) return false;
	return true;
}
void student::admission() {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[12];
	int dd, mm, yy;
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,12,"%d/%m/%Y",timeinfo);
	string cur_date(buffer);
	cout << "Enter student name: " << endl;
	cin.ignore(256,'\n');
	getline(cin,name);
	cout << "Enter roll number: (e.g XY0000)" << endl; // roll number is in  XY0000 format
	cin >> roll;
	cout << "Enter course name: " << endl;
	cin.ignore(256,'\n');
	getline(cin,course);
	dd=atoi(cur_date.substr(0,2).c_str());
	mm=atoi(cur_date.substr(3,2).c_str());
	yy=atoi(cur_date.substr(6).c_str());
	admission_date=date(dd,mm,yy);
	student::no_of_students++; // no of students taken admission
}
void student::set_marks() {
	cout << "Enter marks of 5 subjects of Roll " << roll << ":" << endl;
	for (int i=0; i<NO_OF_SUBJECTS; i++) {
		cin >> marks[i];
	}
	marks_updated=1;
}
void student::view_details() const {
	cout << "Name: " << name << "\nRoll: " << roll << "\nCourse: " << course << "\nDate of Admission: " << admission_date << endl;
}
void student::get_marksheet() const {
	if (marks_updated) {
		cout << "MARKSHEET: " << endl;
		view_details();
		cout << "Subject	Marks" << endl;
		int tot=0, sum=0, grade, fail=0;
		double sgpa;
		for (int i=0; i<NO_OF_SUBJECTS; i++) {
			cout << i+1 << "\t" << marks[i] << endl;
			if (marks[i]<40) fail=1;
			grade=MIN(10,marks[i]/10+1);
			sum+=grade;
			tot+=marks[i];
		}
		sgpa=(double)sum/NO_OF_SUBJECTS;
		cout << "Total Marks Obtained: " << tot << endl;
		cout << "SGPA Obtained: " << sgpa << endl;
	}
	else {
		cout << "Marks not yet received" << endl;
	}
}
int search(student *stdnt, string rno, int length) {
	int found=-1;
	for (int i=0; i<length; i++) {
		if (rno.compare(stdnt[i].roll)==0) {
			found=i;
			break;
		}
	}
	return found;
}
int main () {
	student stu[MAX_STUDENTS];
	int next=0, index, choice;
	string rno;
	while (true) {
		cout << "1. Take Admission\n2. Receive marks\n3. Prepare marksheet\n4. Display details of a student\n5. View total no of students admitted\n0. Exit\n" << endl;
		cout << "Enter Your Choice:" << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "Admission for student " << next+1 << endl;
					stu[next].admission();
					next++;
					break;
			case 2: cout << "Enter roll no of student: ";
					cin >> rno;
					index=search(stu,rno,next);
					if (index>=0)
					stu[index].set_marks();
					break;
			case 3: cout << "Enter roll no of student: ";
					cin >> rno;
					index=search(stu,rno,next);
					if (index>=0)
					stu[index].get_marksheet();
					break;
			case 4: cout << "Enter roll no of student: ";
					cin >> rno;
					index=search(stu,rno,next);
					if (index>=0)
					stu[index].view_details();
					break;
			case 5: cout << "Number of students admitted: " << student::get_total_students() << endl;
					break;
			case 0: exit(1);
			default: cout << "Invalid Choice" << endl;
		}
	}
	return 0;
}

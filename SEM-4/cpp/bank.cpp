#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>
#define MAX_CUSTOMER 1001
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
	static bool is_valid_date(date); 
	static date get_system_date();
};
class balance;
class transaction {
	long long accno;
	float amount;
	char type;
	date dotrans;
	public:
	transaction(long long);
	void set_transaction_details();
	void execute_transaction(balance&);
};
class balance {
	long long accno;
	float accbalance;
	date last_update;
	public:
	balance();
	balance(long long,float,date);
	void view_details();
	friend int search_accno(balance*,int,long long);
	friend void transaction::execute_transaction(balance&);
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
	strftime(buffer,12,"%d/%m/%Y",timeinfo);
	string cur_date(buffer);
	dd=atoi(cur_date.substr(0,2).c_str());
	mm=atoi(cur_date.substr(3,2).c_str());
	yy=atoi(cur_date.substr(6).c_str());
	sysdate=date(dd,mm,yy);
	return sysdate;
}
bool date::is_valid_date(date dat) {
	date sysdate=date::get_system_date();
	if (dat.year<1970 || dat.year>2079) return false;
	else if (dat.month<1 || dat.month>12) return false;
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	bool leap=false;
	if (dat.year%400==0 || (dat.year%100!=0 && dat.year%4==0)) leap=true;
	if (leap) days[2]++;
	if (dat.day<1 || dat.day>days[dat.month]) return false;
	if (dat.year>sysdate.year || (dat.year==sysdate.year && dat.month>sysdate.month) || (dat.year==sysdate.year && dat.month==sysdate.month && dat.day>sysdate.day))
	return false;
	return true;
}
balance::balance() {
	accno=0;
	accbalance=0.0;	
}
balance::balance(long long acc_no, float bal, date dat) {
	accno=acc_no;
	accbalance=bal;
	last_update=dat;
}
void balance::view_details() {
	cout << "Account Number: " << accno << endl;
	cout << "Account Balance: " << accbalance << endl;
	cout << "Last updated on: " << last_update;
}
transaction::transaction(long long ano=0) {
	accno=ano;
	amount=0.0;
	type='D'; // set type to deposit by default
	dotrans=date::get_system_date();
}
void transaction::set_transaction_details() {
	cout << "Enter type of transaction: \n1. Deposit(D)\n2. Withdrawl(W)\nEnter D/W" << endl;
	cin >> type;
	cout << "Enter amount: (Can deposit/withdraw maximum Rs. 100000 at a time)" << endl;
	cin >> amount;
	if (amount<0 || amount>=100000) {
		cout << "Invalid amount" << endl;
	}
}
void transaction::execute_transaction(balance& bal) {
	if (type=='W') {
		if (amount>bal.accbalance) {
			cout << "Sorry! Insufficient balance" << endl;
		}
		else {
			bal.accbalance=bal.accbalance-amount;
			cout << "Rs. " << amount << "withdrawn successfully" << endl;
			cout << "Available balance: Rs. " << bal.accbalance << endl;
		}
	}
	else if (type=='D') {
		bal.accbalance=bal.accbalance+amount;
		cout << "Rs. " << amount << "deposited successfully" << endl;
		cout << "Available balance: Rs. " << bal.accbalance << endl;
		bal.last_update=dotrans;
	}
}
int search_accno(balance* cust, int len, long long ano) {
	int pos=-1;
	for(int i=0; i<len; i++) {
		if(ano==cust[i].accno) {
			pos=i;
			break;
		}
	}
	return pos;
}
int main() {
	/*
	date d(1,3,2017);
	cout << date::get_system_date() << endl;
	cout << d << endl;
	cout << date::is_valid_date(d);
	*/
	balance customers[MAX_CUSTOMER];
	long long ano;
	int next=0, index, choice, flag=1, pos;
	float blnc;
	string dat;
	date tempdate;
	while (flag) {
		cout << endl << "MENU: " << endl;
		cout << "1. Add an account\n2. Make a Transaction\n3. View balance\n0. Exit" << endl;
		cout << "Enter you choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "Enter account number" << endl;
					cin >> ano;
					cout << "Enter available balance" << endl;
					cin >> blnc;
					cout << "Enter last date of updation" << endl;
					cin >> dat;
					tempdate=date(atoi(dat.substr(0,2).c_str()),atoi(dat.substr(3,2).c_str()),atoi(dat.substr(6).c_str()));
					if(!(date::is_valid_date(tempdate))) {
						cout << "Invalid date" << endl;
					}
					else {
						customers[next++]=balance(ano,blnc,tempdate);
					}
					break;
			case 2: cout << "Enter account number: " << endl;
					cin >> ano;
					pos=search_accno(customers,next,ano);
					if (pos==-1) {
						cout << "Sorry! You don't have an account here" << endl;
					}
					else {
						transaction trans(ano);
						trans.set_transaction_details();
						trans.execute_transaction(customers[pos]);
					}
					break;
			case 3: cout << "Enter account number: " << endl;
					cin >> ano;
					pos=search_accno(customers,next,ano);
					if (pos==-1) {
						cout << "Sorry! You don't have an account here" << endl;
					}
					else {
						customers[pos].view_details();
					}
					break;
			case 0: cout << "Thank You!" << endl;
					flag=0;
					break;
			default: cout << "Invalid Choice" << endl;
		}
	}
	/*
	balance bl(1000,1000)
	transaction tr;
	tr.set_transaction_details();
	tr.execute_transaction(bl);
	*/
	return 0;
}



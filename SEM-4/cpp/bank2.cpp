/*
SAVINGS AND CURRENT ACCOUNT
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>
#define MAX_CUSTOMER 501
#define MAX_TRANS 51
using namespace std;

class savings;
class current;
class account {
	protected:
	long long accno;
	float amount;
	public:
	account(long long ano=0, float amt=0.0) {accno=ano; amount=amt;} 
	virtual void withdraw(float)=0;
	virtual void deposit(float)=0;
	friend int search_savings_accno(savings*,int,long long);
	friend int search_current_accno(current*,int,long long);
};
class transaction {
	int trans_id;
	char type;
	float amount;
	public:
	transaction() {trans_id=0; amount=0.0;}
	transaction(int id, char typ, float amt) {
		trans_id=id;
		type=typ;
		amount=amt;
	}
	friend class savings;
	friend class current;
};
class savings:public account {
	int no_trans;
	transaction trans[MAX_TRANS];
	public:
	savings():account(0,0) {}
	savings(long long ano, float amt):account(ano,amt) {no_trans=0;}
	void deposit(float);
	void withdraw(float);
	void show_transaction_last10() const;
	//friend int search_savings_accno(savings*,int,long long);
};
class current : public account{
	transaction trans[MAX_TRANS];
	int no_trans;
	float over_amt;
	public:
	current():account(0,0) {}
	current(long long ano, float amt):account(ano, amt) {
		no_trans=0;
		over_amt=0.0;
	}
	void deposit(float);
	void withdraw(float);
	void show_transaction_last10() const;
	//friend int search_current_accno(current*,int,long long);
};
void savings::deposit(float amt) {
	amount+=amt;
	trans[no_trans++]=transaction(no_trans,'D',amt);
	cout << "Rs. " << amt << " deposited successfully" << endl;
	cout << "Available balance: Rs. " << amount << endl;
	//no_trans++;
}
void savings::withdraw(float amt) {
	if ((amount-amt)<500) {
		cout << "Account must have minimum of Rs. 500" << endl;
	}
	else {
		amount-=amt;
		trans[no_trans++]=transaction(no_trans,'W',amt);
		cout << "Rs. " << amt << " withdrawn successfully" << endl;
		cout << "Available balance: Rs. " << amount << endl;
		//no_trans++;
	}
}
void savings::show_transaction_last10() const {
	cout << "Account Number: " << accno << endl;
	cout << "Available Balance: Rs. " << amount << endl;
	cout << "S.NO	Type	Amount" << endl;
	for (int i=0; i<no_trans  && i<10; i++) {
		cout << i+1 << "\t" << trans[no_trans-1-i].type << "\t" << trans[no_trans-1-i].amount << endl; 
	}
}
void current::deposit(float amt) {
	amount+=amt;
	over_amt=(amount<0.0)?-amount:0.0;
	trans[no_trans++]=transaction(no_trans,'D',amt);
	cout << "Rs. " << amt << " deposited successfully" << endl;
	if (amount<0) {
		cout << "Available Overdraft Limit: Rs. " << (20000-over_amt) << endl;
	}
	else {
		cout << "Available balance: Rs. " << amount << endl;
	}
}
void current::withdraw(float amt) {
	if ((amount-amt)<-20000) {
		cout << "Maximum overdraft is Rs. 20000" << endl;
	}
	else {
		amount-=amt;
		over_amt=(amount<0.0)?-amount:0.0;
		trans[no_trans++]=transaction(no_trans,'W',amt);
		cout << "Rs. " << amt << " withdrawn successfully" << endl;
		if (amount<0) {
		cout << "Available Overdraft Limit: Rs. " << (20000-over_amt) << endl;
		}
		else {
			cout << "Available balance: Rs. " << amount << endl;
		}
	}
}
void current::show_transaction_last10() const {
	cout << "Account Number: " << accno << endl;
	if (amount<0) {
		cout << "Available Overdraft Limit: Rs. " << (20000-over_amt) << endl;
	}
	else {
		cout << "Available balance: Rs. " << amount << endl;
	}
	cout << "S.NO	Type	Amount" << endl;
	for (int i=0; i<no_trans  && i<10; i++) {
		cout << i+1 << "\t" << trans[no_trans-1-i].type << "\t" << trans[no_trans-1-i].amount << endl; 
	}
}
int search_savings_accno(savings* cust, int len, long long ano) {
	int pos=-1; // pos=-1 if not found
	for(int i=0; i<len; i++) {
		if(ano==cust[i].accno) { // search for account number
			pos=i; 
			break;
		}
	}
	return pos;
}
int search_current_accno(current* cust, int len, long long ano) {
	int pos=-1; // pos=-1 if not found
	for(int i=0; i<len; i++) {
		if(ano==cust[i].accno) { // search for account number
			pos=i; 
			break;
		}
	}
	return pos;
}

int main() {
	/*
	savings s(1000,500);
	s.deposit(200);
	s.withdraw(400);
	s.show_transaction_last10();
	cout << endl;
	current c(1001,600);
	c.deposit(1000);
	c.withdraw(500);
	c.deposit(1000);
	c.withdraw(5000);
	c.deposit(500);
	c.deposit(500);
	c.deposit(500);
	c.deposit(500);
	c.deposit(500);
	c.deposit(500);
	c.withdraw(500);
	c.deposit(100000);
	c.show_transaction_last10();
	
	*/
	savings s_acc[MAX_CUSTOMER];
	current c_acc[MAX_CUSTOMER];
	long long ano;
	int nexts=0, nextc=0 ,choice, flag=1, poss, posc, sav_cur;
	float blnc;
	string dat;
	while (flag) {
		cout << endl << "MENU: " << endl;
		cout << "1. Create account\n2. Deposit\n3. Withdraw\n4. View last 10 transactions" << endl;
		cout << "Enter you choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: cout << "1. Savings Account\n2. Current Account\nEnter your choice: " << endl;
					cin >> sav_cur;
					cout << "Enter account number" << endl;
					cin >> ano;
					cout << "Enter initial balance:" << endl;
					cin >> blnc;
					if (sav_cur==1 && blnc<500) {
						cout << "Minumum Rs. 500 must be deposited" << endl;
					}
					else {
						if (sav_cur==1) s_acc[nexts++]=savings(ano,blnc);
						else if (sav_cur==2) c_acc[nextc++]=current(ano,blnc);
					}
					break;
			case 2: cout << "Enter account number: " << endl;
					cin >> ano;
					poss=search_savings_accno(s_acc,nexts,ano);
					posc=search_current_accno(c_acc,nextc,ano);
					if (poss==-1 && posc==-1) {
						cout << "Sorry! You don't have an account here" << endl;
						break;
					}
					cout << "Enter amount to be deposited" << endl;
					cin >> blnc;
					if (poss>=0) {
						s_acc[poss].deposit(blnc);
					}
					else if (posc>=0) {
						c_acc[posc].deposit(blnc);
					}
					break;
			case 3: cout << "Enter account number: " << endl;
					cin >> ano;
					poss=search_savings_accno(s_acc,nexts,ano);
					posc=search_current_accno(c_acc,nextc,ano);
					if (poss==-1 && posc==-1) {
						cout << "Sorry! You don't have an account here" << endl;
						break;
					}
					cout << "Enter amount to be withdrawn" << endl;
					cin >> blnc;
					if (poss>=0) {
						s_acc[poss].withdraw(blnc);
					}
					else if (posc>=0) {
						c_acc[posc].withdraw(blnc);
					}
					break;
			case 4: cout << "Enter account number: " << endl;
					cin >> ano;
					poss=search_savings_accno(s_acc,nexts,ano);
					posc=search_current_accno(c_acc,nextc,ano);
					if (poss==-1 && posc==-1) {
						cout << "Sorry! You don't have an account here" << endl;
						break;
					}
					if (poss>=0) {
						s_acc[poss].show_transaction_last10();
					}
					else if (posc>=0) {
						c_acc[posc].show_transaction_last10();
					}
					break;
			case 0: cout << "Thank You!" << endl;
					flag=0;
					break;
			default: cout << "Invalid Choice" << endl;
		}
	}
	
	
	return 0;
}

/*
Design a class time which stores hours, minuites and seconds. The class should have functions to support ibput and display of time in 12hr/24hr format
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

class time1 {
	int hour, min, sec;
	public:
	time1() {hour=min=sec=0;}
	void set_time(); 
	void disp_time(bool);
	void add_minuites(int);
};
void time1::set_time() {
	string tim, format;
	int h_temp, m_temp, s_temp;
	cout << "Enter time:" << endl;
	cout << "HH:MM:SS HR (24 hour format)" << endl << "HH:MM:SS AM/PM (12 hour format)" << endl;
	getline(cin,tim);
	format=tim.substr(9,2); // extract the 12/24 hr format
	h_temp=(int)(tim.at(0)-'0')*10+(int)(tim.at(1)-'0'); // extract hours part
	m_temp=(int)(tim.at(3)-'0')*10+(int)(tim.at(4)-'0'); // extract minuites part
	s_temp=(int)(tim.at(6)-'0')*10+(int)(tim.at(7)-'0'); // extract seconds part
	if (m_temp<0 || m_temp>=60 || s_temp<0 || s_temp>=60 || h_temp<0 || h_temp>=24) {
		cout << "INVALID INPUT\n";
		return;
	}
	/*
		STORE TIME IN 24 HOUR FORMAT ALWAYS
	*/
	if (!(format.compare("AM") && format.compare("Am") && format.compare("aM") && format.compare("am"))) { // AM case
		if (h_temp>12 || h_temp==0) {
			cout << "INVALID INPUT" << endl;
			return;
		}
		hour=h_temp%12; // 12 will become 0
		min=m_temp;
		sec=s_temp;
	}
	else if (!(format.compare("PM") && format.compare("Pm") && format.compare("pM") && format.compare("pm"))){ // PM case
		if (h_temp>12 || h_temp==0) {
			cout << "INVALID INPUT" << endl;
			return;
		}
		hour=h_temp%12+12; // 12 will remain 12
		min=m_temp;
		sec=s_temp;
	}
	else if (!(format.compare("HR") && format.compare("Hr") && format.compare("hR") && format.compare("hr"))) { // 24 hour case
		hour=h_temp;
		min=m_temp;
		sec=s_temp;
	}
	else {
		cout << "INVALID INPUT" << endl;	
		return;
	}
}
void time1::disp_time(bool format=false) {
	int h_temp=hour;
	string form;
	if (format) {// 12 hour format
		if (h_temp<12) {
			h_temp=(h_temp==0)?12:h_temp; // 0 becomes 12
			form="AM";
		}
		else {
			h_temp=(h_temp==12)?h_temp:h_temp-12; // 12 remains 12
			form="PM";
		}
	}
	else { // 24 hour format
		form="HR";
	}
	cout << "Current time is:" << endl;
	cout << setfill('0') << setw(2) << h_temp << ":" << setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << sec << " " << form << endl;
}
void time1::add_minuites(int minuites) {
	int hrs, mins;
	mins=minuites%60;
	hrs=minuites/60;
	min+=mins;
	hour+=hrs; 
	hour=hour%24; 
	if (min>=60) { // handle excess minuites by adding an hour
		hour++;
		min-=60;	
	}
}
int main(void) {
	time1 t;
	int choice, min;
	while (true) {
		cout << "1. Set the time\n2. Display time in 24 hour format\n3. Display time in 12 hour format\n4. Add minuites to time\n0. Exit\n" << endl;
		cout << "Enter your choice:" << endl;
		cin >> choice;
		cin.ignore (256, '\n'); // skip over \n
		switch(choice) {
			case 1: t.set_time();
					break;
			case 2: t.disp_time();
					break;
			case 3: t.disp_time(1);
					break;
			case 4: cout << "Enter minuites to be added:" << endl;
					cin >> min;
					t.add_minuites(min);
					break;
			case 0: exit(1);
			default: cout << "Invalid Choice\n";
		}
	}
	return 1;
}

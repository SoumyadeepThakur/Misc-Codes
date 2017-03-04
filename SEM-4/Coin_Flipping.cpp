/*
Coin Tossing
*/
#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
using namespace std;

class coin_toss{
	int no_tosses;
	int head, tail;
	public:
	coin_toss(){
		no_tosses=0;
		head=tail=0;
	}
	void toss();
};
void coin_toss::toss() {
	int count, flip;
	head=tail=0;
	no_tosses=0;
	count=0;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // time dependent seed
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,2);
	while (count<3) {
		int flip = distribution(generator);  // generates number in the range 1 to 2 
		if(flip%2) {
			cout << "Heads" << endl;
			count++; // increment count for heads
			head++;
		}
		else {	
			cout << "Tails" << endl;
			count=0;	//reset count for tails
			tail++;
		}
		no_tosses++;	//count total no of tosses to get three consecutive heads
	}
	cout << "It took " << no_tosses << " flips to get three consecutive heads." << endl;
}
int main() {
	coin_toss ct1;
	int choice, flag=1;
	while (flag) {
		cout << "MENU: " << endl;
		cout << "1. Flip Coin\n0. Exit" << endl;
		cout << "Enter Your Choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: ct1=coin_toss();
					ct1.toss();
					break;
			case 0: flag=0;
					break;
			default: cout << "Invalid Choice" << endl;
		}
	}
	return 0;
}

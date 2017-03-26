#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#define MAX_SIZE 1001
using namespace std;

class item {
	int itemcode, qty;
	float rate;
	char *name;
	public:
	item(int,const char*); 
	void display();
	int get_icode() {return itemcode;}
	void set_quantity(int iqty) {qty=iqty;}
	int get_quantity() const{return qty;}
	void set_rate(float irate) {rate=irate;}
	float get_rate() const {return rate;}
	char *get_name() const {return name;}
	void update_quantity(int uqty) {qty+=uqty;}
};
class item_list {
	item stock[MAX_SIZE];
	int count;
	public:
	int search_item(int);
	void add_item();
	void issue_item(int,int);
	void change_rate(int);
	void display_details(int);
};
item::item(int icode=-1, const char *iname="") {
	itemcode=icode;
	name=new char[strlen(iname)+1];
	strcpy(name,iname);
	qty=0;
	rate=0.0;
}
void item::display() {
	cout << "Item code: " << itemcode << "\nName: " << name << "\nQuantity: " << qty << "\nRate: " << rate << endl;
}
void item_list::display_details(int icode) {
	stock[search_item(icode)].display();
}
int item_list::search_item(int icode) {
	int pos=-1; // if not found pos will be -1
	for (int i=0; i<count; i++) {
		if (stock[i].get_icode()==icode) { // search for code
			pos=i;
			break;
		}
	}
	return pos;
}
void item_list::add_item() {
	int ic, q;
	float r;
	char n[50];
	cout << "Enter itemcode, name, rate and quantity" << endl;
	cin >> ic >> n >> r >> q;
	item temp(ic,n);
	temp.set_rate(r);
	temp.set_quantity(q);
	int pos=search_item(ic);
	if (pos==-1) { // add item to list if it is not already present
		stock[count++]=temp;
	}
	else { // update item details if item exists in list
		stock[pos].set_rate(r);
		stock[pos].update_quantity(q);
	}
}
void item_list::issue_item(int icode, int quant) {
	int exist=search_item(icode);
	int pos;
	float cost;
	if (exist==-1) {
		cout << "Item not present in stock!" << endl;
		return;
	}
	pos=search_item(icode);
	if (quant>stock[pos].get_quantity()) {
		cout << "Not enough items in stock! " << endl;
		return;
	}
	stock[pos].update_quantity(-quant);
	cost=stock[pos].get_rate()*quant;
	cout << "Your Bill:" << endl;
	cout << "Item  code: " << icode << endl;
	cout << "Item  name: " << stock[pos].get_name() << endl;
	cout << "Amount issued: " << quant << endl;
	cout << "Issue cost: Rs. " << cost << endl << endl;
	cout << "Amount of items left in stock: " << stock[pos].get_quantity() << endl;
}
void item_list::change_rate(int icode) {
	int rate;
	cout << "Current Status of item: " << icode << endl;
	cout << "Enter changed rate: " << endl;
	cin >> rate;
	stock[search_item(icode)].set_rate(rate);
}
int main(void) {
	item_list il;
	int choice, icode, qty;
	while (true) {
		cout << endl << "MENU: " << endl;
		cout << "1. Add new item\n2. Change rate of item\n3. Issue an item\n4. Display details of an item\n0. Exit" << endl;
		cout << "Enter you choice: " << endl;
		cin >> choice;
		switch(choice) {
			case 1: il.add_item();
					break;
			case 2: cout << "Enter code of item whose rate is to be changed: " << endl;
					cin >> icode;
					il.change_rate(icode);
					break;
			case 3: cout << "Enter item code and quantity to be issued: " << endl;
					cin >> icode;
					cin >> qty;
					il.issue_item(icode,qty);
					break;
			case 4: cout << "Enter code of item: " << endl; 
					cin >> icode;
					il.display_details(icode);
					break;
			case 0: exit(1);
			default: cout << "Invalid Choice" << endl;
		}
	}
	return 0;
}
	
	

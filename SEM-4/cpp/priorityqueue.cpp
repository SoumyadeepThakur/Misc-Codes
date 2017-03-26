#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

template <class Type, class Container=std::vector<Type> >
class priority_queue {
	public:
	static int min, max;
	private:
	bool priority;
	int size;
	Container queue; 
	bool compare(Type val1, Type val2) {
		bool flag=false;
		if (priority==0) flag=(val1>val2);
		else if (priority==1) flag=(val1<val2);
		return flag;
	}
	public:
	explicit priority_queue(int);
	Type dequeue();
	void enqueue(Type);
	Type top();
	bool is_empty();
	int get_size();
	void increase_key(int,Type);

};
template <class T, class C>
int priority_queue<T,C>::max=0;
template <class T, class C>
int priority_queue<T,C>::min=1;
template <class T, class C>
priority_queue<T,C>::priority_queue(int prior) {
	priority=prior;
	size=0;
	cout << "Hello template " << priority << endl;
	cout << sizeof(T);
}
template <class T, class C>
bool priority_queue<T,C>::is_empty() {
	return (size==0);
}
template <class T, class C>
int priority_queue<T,C>::get_size() {
	return size;
}
template <class T, class C>
void priority_queue<T,C>::enqueue(T data) { // need to do for both priorities
	if (is_empty()) {
		queue.push_back(T()); // dummy first element
	}
	queue.push_back(data);
	size++;
	int index=queue.size()-1;
	T temp=queue[index];
	while (index>1 && compare(temp,queue[index/2])) {
		queue[index]=queue[index/2];
		index=index/2;
	}
	queue[index]=temp;
	//cout << index;
	//cout << endl;
	for (int i=1; i<=size; i++) cout << queue[i] << " ";
	cout << endl;
	
}
template <class T, class C>
T priority_queue<T,C>::dequeue() { // need to do for both priorities
	if (is_empty()) {
		cout << "Priority Queue Underflow Error" << endl;
		T garbage;
		return garbage;
	}
	T deq=queue[1];
	T temp=queue[1]=queue[size];
	queue.pop_back();
	size--;
	int index=2;
	T child;
	//index=index*2;
	while (index<=size) {
		child=queue[index];
		//cout << "temp" << temp << endl;
		if (index<size && compare(queue[index+1],child)) {
			child=queue[index+1];
			index++;
		}
		//cout << "child" << child << endl;
		if (compare(temp,child)) break;
		queue[index/2]=queue[index];
		index=index*2;
		//cout << "Current Queue:" << endl;
		//for (int i=1; i<=size; i++) cout << queue[i] <<" ";
		//cout << endl;
	}
	queue[index/2]=temp;
	for (int i=1; i<=size; i++) cout << queue[i] << " ";
	cout << endl;
	return deq;
}
template <class T, class C>
void priority_queue<T,C>::increase_key(int index, T amount) {
	if (amount<0) {
		cout << "Invalid change amount" << endl;
		return;
	}
	if (priority==0) queue[index]=queue[index]+amount;
	else if (priority==1) queue[index]=queue[index]-amount;
	else return;
	T temp=queue[index];
	while (index>1 && compare(temp,queue[index/2])) {
		queue[index]=queue[index/2];
		index=index/2;
	}
	queue[index]=temp;
}
template <class T, class C>
T priority_queue<T,C>::top() {
	if (is_empty()) {
		cout << "Priority Queue is empty" << endl;
		T garbage;
		return garbage;
	}
	return queue[1];
}
int main() {
	/*
	
	priority_queue<double> pq(priority_queue<double>::min);
	cout << pq.is_empty();
	pq.enqueue(2.2);
	pq.enqueue(3.3);
	pq.enqueue(4.4);
	pq.enqueue(1.1);
	pq.enqueue(2.8);
	pq.increase_key(3,0.5);
	cout << pq.dequeue() << endl;
	cout << pq.top() << endl;
	cout << pq.dequeue() << endl;
	*/
	priority_queue<int> pq_int(priority_queue<double>::max);
	int choice, flag=1;
	
	cout << 
	cin >> type;
	while (flag) {
		cout << "MENU:" << endl;
		cout << "1. Create the priority queue with a data type\n2. Insert an element to the queue\n3. Delete element from the queue\n4. Get the top element\n5. Display the queue\n0. Exit" << endl;
		case 1: break;
	}
	



	return 0;
}


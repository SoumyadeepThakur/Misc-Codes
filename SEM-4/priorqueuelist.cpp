#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

template <class Type, class Container=std::list<Type> >
class priority_queue 
{
	public:
	static int min, max;
	private:
	bool priority;
	int size;
	Container queue; 
	bool compare(Type val1, Type val2) 
	{
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
	void increase_key(Type,Type);
	void display();

};
template <class T, class C>
int priority_queue<T,C>::max=0;
template <class T, class C>
int priority_queue<T,C>::min=1;
template <class T, class C>
priority_queue<T,C>::priority_queue(int prior) 
{
	priority=prior;
	size=0;
}
template <class T, class C>
bool priority_queue<T,C>::is_empty() 
{
	return (size==0);
}
template <class T, class C>
int priority_queue<T,C>::get_size() 
{
	return size;
}
template <class T, class C>
void priority_queue<T,C>::enqueue(T data) 
{   
	size++;
	if (is_empty()) 
	{
		queue.push_back(data);
		return;
	}
	typename list<T>::iterator i=queue.begin();
	bool inserted=false; 
	while (i!=queue.end()) 
	{
		if (compare(data,*i))
		{
			inserted=true;
			queue.insert(i,data);
			break;
		}
		++i;
	}
	if (!inserted) queue.push_back(data);
	cout << endl;
	
}

template <class T, class C>
T priority_queue<T,C>::dequeue() 
{ 
	if (is_empty()) 
	{
		cout << "Priority Queue Underflow Error" << endl;
		T garbage;
		return garbage;
	}
	T deq=queue.front();
	queue.pop_front();
	return deq;
}

template <class T, class C>
void priority_queue<T,C>::increase_key(T data, T amount) 
{	
	bool found=false;
	if (amount<0) 
	{
		cout << "Invalid change amount" << endl;
		return;
	}
	queue.remove(data);
	if (priority==0) data=data+amount;
	else if (priority==1) data=data-amount;
	size--;
	enqueue(data);
	
}
template <class T, class C>
T priority_queue<T,C>::top() 
{
	if (is_empty()) 
	{
		cout << "Priority Queue is empty" << endl;
		T garbage;
		return garbage;
	}
	return queue.front();
}
template <class T, class C>
void priority_queue<T,C>::display()
{
	for (typename list<T>::iterator i=queue.begin(); i!=queue.end(); i++) cout << *i << " "; 
	cout << endl;
}
int main() {
	priority_queue<double> pqueue(priority_queue<double>::max);
	double ele, amt;
	int choice, flag=1;
	while (flag) {
		cout << "MENU:" << endl;
		cout << "1. Insert an element to the queue\n2. Delete element from the queue\n3. Change priority of an element\n4. Get the top element\n5. Display the queue\n0. Exit" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;
		switch(choice)
		{
			case 1: cout << "Input element: " << endl;
					cin >> ele;
					pqueue.enqueue(ele);
					break;
			case 2: cout << "Deleted element: " << pqueue.dequeue() << endl;
					break;
			case 3: cout << "Enter element and amount by which priority is to be increased: " << endl;
					cin >> ele >> amt;
					pqueue.increase_key(ele,amt);
					break;
			case 4: cout << "Top element: " << pqueue.top() << endl;
					break;
			case 5: cout << "Priority Queue: " << endl;
					pqueue.display();
					break;
			case 0: flag=0;
					break;
			default: cout << "Wrong Input" << endl;
		}
	}
	return 0;
}


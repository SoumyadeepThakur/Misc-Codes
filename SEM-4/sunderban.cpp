/*
MINIMUM SPANNING TREE FOR VILLAGES
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

class weight
{
	int node, key;
	public:
	weight(int nd, int wght) {node=nd; key=wght;}
	bool operator<(weight wght) {return  (key<wght.key);}
	bool operator>(weight wght) {return  (key>wght.key);}
	int get_node() const{return node;}
	int get_weight() const{return key;}
	void update_weight(int new_wt) {key=new_wt;}
};
class Compare
{
	public:
	bool operator() (weight& a,weight& b) // comparison function for the priority queue
	{
		return (a>b);
	}
};
class network
{
	int no_village, no_road;
	vector <vector<weight> > adj_list;
	public:
	network(int,int);
	void init();
	void minimum_spanning_tree();
};
network::network(int villages, int roads)
{
	no_village=villages;
	no_road=roads;
	adj_list=vector <vector<weight> >(no_village);
}
void network::init()
{
	int src, dest, wt;
	cout << "Enter village numbers which are connected and its corresponding cost: " << endl;
	for (int i=0; i<no_road; i++) {
		cin >> src >> dest >> wt;
		weight source(dest-1,wt);
		weight destination(src-1,wt);
		adj_list[src-1].push_back(source); // add entry to adjacency list
		adj_list[dest-1].push_back(destination);
	}
}
void network::minimum_spanning_tree()
{
	int *parent=new int[no_village];
	vector<int> key;
	vector<weight> heap; // priority queue
	int scr=0; // assume that village with index 0 is the starting vertex
	weight temp(0,0);
	key.push_back(0);
	heap.push_back(temp); // starting element kept with min priority
	for (int i=1; i<no_village; i++)
	{
		key.push_back(numeric_limits<int>::max());
		temp=weight(i,numeric_limits<int>::max());
		heap.push_back(temp);
	}
	make_heap(heap.begin(),heap.end(),Compare()); // build min priority queue
	weight min_wt(0,0);
	int vertex;
	while (!heap.empty())
	{
		min_wt=heap[0]; // lowest weight element
		vertex=min_wt.get_node(); // get the node with min key
		pop_heap(heap.begin(),heap.end());
		heap.pop_back();
		for (vector<weight>::iterator i=adj_list[vertex].begin(); i!=adj_list[vertex].end(); ++i)
		{
			int adj=i->get_node(), wght=i->get_weight(); 
			int pos=-1;
			for (int j=0; j<heap.size(); j++)
			{
				if (heap[j].get_node()==adj) // for all adjacent nodes of vertex, search if present in queue
				{
					pos=j; 
					break;
				}
			}
			if (pos>=0 && i->get_weight()<key[adj])
			{
				key[adj]=wght;
				heap[pos].update_weight(wght); // update key
				parent[adj]=vertex; // set parent
			}
		}
		make_heap(heap.begin(),heap.end(),Compare()); // rearrange after changing keys
	}
	cout << "Roads along which wires should be laid: " << endl;
	for (int i = 1; i < no_village; ++i)
    cout << (parent[i]+1) << "-" << (i+1) << endl;
	cout << endl;
}
int main()
{
	int vill, road;
	cout << "Enter number of villages and roads: " << endl;
	cin >> vill >> road;
	network opt_fibre(vill,road);
	opt_fibre.init();
	opt_fibre.minimum_spanning_tree();
	return  0;
}

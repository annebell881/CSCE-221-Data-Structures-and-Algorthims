#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex (T l) : label(l) {top_num = 0;}; //Part 1
  // You may include default constructor optionally.
  Vertex(){};
};

template < class T >
class VertexCompare {
	public :
	// will be called as a < operator
	bool operator ()( Vertex <T > v1 , Vertex <T > v2 ){
		// TODO - implement
		if(v1.top_num > v2.top_num){
			return true;
		}
		return false ;
	}
};

template <class T>
class Graph{
	private:
		unordered_map <T , Vertex <T > > node_set ;
		
	public:
		Graph() {}; // default constructor
		
		
		
		// build a graph
		void buildGraph(istream& input){
			
			//put these into an unordered_map so just use T
			T data1;
			T label1;
			string line;
			//std::cout << line << std::endl;
			//read in the data and lable to start building up the graph
			while(getline(input, line)){
				stringstream ss (line);
				ss >> label1;
				//std::cout << line << std::endl;
				//std::cout << label1 << std::endl;
				Vertex<T> v =Vertex<T>(label1);
				node_set .insert ( std::make_pair ( label1 , v));
				while (!ss.eof()){
					ss >> data1;
					//std::cout << data1 << std::endl;
					//push back the data into the list once all the data is shifted through we should be able to add it to the unordered map
					node_set[label1].adj_list.push_back(data1);
				}
				//std::cout << "end data" << endl;
				
			}
		}
		
		Vertex<T> at(T label){
			return node_set.at(label);
		}
		
		void displayGraph(ostream &o){
			for(auto& element: node_set) {
				//do stuff, note that element will be a pair <T, Vertex v>, so if you  want to access properties of the vertex itself
				//you will need to do element.second.adj_list etc.
				o << element.first << ": ";
				for (auto i = 0; i < element.second.adj_list.size(); i++){
					o << element.second.adj_list[i] << " ";
				}
				o << std::endl;
			}
		}
		
		int size(){
			return node_set.size();
		}
		
		void compute_indegree(){
			//assigns the indegree, the number of inbound edges, for each node.
			
			queue<T> q;
			for(auto& element: node_set) {
				//each indegree is equal to zero for each vertex
				element.second.indegree = 0;
				for(auto i = 0; i < element.second.adj_list.size(); i++){
					q.push(element.second.adj_list[i]);
				}
			}	
			
			while (!q.size() == 0){
				T data2 = q.front();
				
				for(auto& element: node_set) {
					if(element.second.label == data2){
						element.second.indegree ++;
					}
				}
				q.pop();
			}
		}
		
		bool topological_sort(){
			//performs the topological sort which returns true
			//if a topological ordering is found, otherwise returns false.
			priority_queue <  T  , vector <T >  , VertexCompare <T > > pq ;
			int counter = 0;
			
			//all vertices with indegrees equal zero into a queue
			for(auto& element: node_set) {
				if (element.second.indegree == 0){
					pq.push(element.first);
				}
			}
			
			while(pq.size() != 0){
				Vertex<T> v = node_set.at(pq.top());
				v.top_num = ++counter;
				node_set.at(pq.top()) = v;
				pq.pop();
				//store adj_list
				queue<T> q;	
				for(auto& element: node_set) {
					if(element.second.label == v.label){
						for(auto i = 0; i < element.second.adj_list.size(); i++){
							q.push(element.second.adj_list[i]);
						}
					}
				}
				while(q.size() != 0){
				
						T data2 = q.front();
						for(auto& element: node_set) {
							if(element.second.label == data2){
								if (--element.second.indegree == 0){
									pq.push(element.first);
								}
							}
						}
				
					q.pop();
				}
			}	
			
			if (counter != size()){
				return false;
			}
			else{
				return true;
			}
		}
		
		void print_top_sort(ostream& o, bool addNewline=true){
			priority_queue <  T  , vector <T >  , VertexCompare <T > > pq ;
			for(auto& element: node_set) {
				pq.push(element.first);
			}
			while(pq.size() != 0){
				Vertex<T> v = pq.top();
				pq.pop();
				o << v.label << " ";
			}
			if (addNewline){
				o << std::endl;
			}
			
		}

	
};


	

// optional, but probably helpful
// template <class T>
// ostream& operator<<(ostream &o, Vertex<T> v){};

#endif
#include <iostream>
#include <list>
#include <stack>
using std::cout;
using std::endl;
using std::list;

class Graph {

	int num_vertices;
	list<int> *adjacency_list;

 public:
	Graph(int num_v) {
		num_vertices = num_v;
		adjacency_list = new list<int>[num_vertices];
	}	
	
	void addEdge(int vertex1, int vertex2) {
		adjacency_list[vertex1].push_back(vertex2);
		adjacency_list[vertex2].push_back(vertex1);
	}

	void breathFirstSearch(int start_vertex) {
		bool *visited = new bool[num_vertices];
		for (int i = 0; i < num_vertices; i++) {
			visited[i] = false;
		}
		list<int> queue;
		visited[start_vertex] = true;
		queue.push_back(start_vertex);

		cout << "Breath First Search: " << endl;		
		while(!queue.empty()) {
			int v = queue.front();
			cout << v << " ";
			queue.pop_front();

			for(list<int>::iterator i = adjacency_list[v].begin();
			    i != adjacency_list[v].end(); i++) {
				if (!visited[*i]) {
					visited[*i] = true;
					queue.push_back(*i);
				}
			}
		}
		cout << endl;
	}
	void depthFirstSearch(int start_vertex) {
		bool *visited = new bool[num_vertices];
		for(int i = 0; i < num_vertices; i++) {
			visited[i] = false;
		}
		std::stack<int> stack;
		visited[start_vertex] = true;
		stack.push(start_vertex);
		cout << "Depth First Search: " << endl;
		while(!stack.empty()) {
			int v = stack.top();
			stack.pop();
			cout << v << " ";
			for (list<int>::iterator i = adjacency_list[v].begin();
		     		i != adjacency_list[v].end(); i++) {
				if (!visited[*i]) {
					visited[*i] = true;
					stack.push(*i);
				}
			}
		}				
		cout << endl;
	}
};

int main() 
{
	Graph mygraph(6); // graph with 6 vertices
	mygraph.addEdge(0,1);
	mygraph.addEdge(0,2);
	mygraph.addEdge(1,2);
	mygraph.addEdge(2,3);
	mygraph.addEdge(1,4);
	mygraph.addEdge(3,5);
	mygraph.breathFirstSearch(2);
	mygraph.depthFirstSearch(2);
}



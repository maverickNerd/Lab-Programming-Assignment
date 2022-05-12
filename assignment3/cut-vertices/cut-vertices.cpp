#include<iostream> 
#include <list> 

#define NIL -1 
using namespace std; 
  
class Graph 
{ 
    int V;              // No. of vertices 
    list<int> *adj;    // A dynamic array of adjacency lists 
    void findCutVertices(int v, int disc[], int low[],  
                int parent[], bool ap[], bool visited[]); 
public: 
    Graph(int V);                   // Constructor 
    void addEdge(int v, int w);
    void DFS(); 
}; 
//Create Graph
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); 
    adj[w].push_back(v);
} 
  
// find cut-vertices points using DFS traversal
void Graph::findCutVertices(int u, int discovery[],  
                                      int low[], int parent[], bool ap[], bool visited[]) 
{ 
    static int time = 0;  
    int children = 0; 
    visited[u] = true; 
  
    // Initialize
    discovery[u] = low[u] = ++time; 
    
    list<int>::iterator i; 
    //Iterate through adjacent vertices
    for (i = adj[u].begin(); i != adj[u].end(); ++i) 
    { 
        int v = *i; 
  
        // Check if the vertex is visited, if it is then make it a child of u
        if (!visited[v]) 
        { 
            children++; 
            parent[v] = u; 
            findCutVertices(v, discovery, low, parent, ap, visited); // Recurse to keep finding new childs
  
            //check if any vertex in subtree rooted with v has a back edge to one of the ancestors 
            low[u]  = min(low[u], low[v]); 
  
            // u is an cut-vertices point in following cases 
  
            // Check if u is root and has two or more chilren. 
            if (parent[u] == NIL && children > 1) 
               ap[u] = true; 
  
            if (parent[u] != NIL && low[v] >= discovery[u]) 
               ap[u] = true; 
        } 
  
        else if (v != parent[u]) 
            low[u]  = min(low[u], discovery[v]); 
    } 
} 
  
// DFS Traversal function
void Graph::DFS() 
{ 
    int *discovery = new int[V]; 
    int *low = new int[V]; 
    int *parent = new int[V]; 
    bool *ap = new bool[V]; 
    bool *visited = new bool[V]; 
  
    for (int i = 0; i < V; i++) 
    { 
        // Mark all the vertices as not visited 
        parent[i] = NIL; 
        visited[i] = false; 
        ap[i] = false; 
    } 
    //Find  cut-vertices point 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            findCutVertices(i, discovery, low, parent, ap, visited); 
  
    // Print cut-vertices points
    for (int i = 0; i < V; i++) 
        if (ap[i] == true) 
            cout << i << " "; 
} 
  
// Below graph example is taken from GeeksForGeeks, code is not taken, just the example 
int main() 
{ 
    cout << "\ncut-vertices points in first graph \n"; 
    //Create Graph
    Graph g1(5); 
    g1.addEdge(1, 0); 
    g1.addEdge(0, 2); 
    g1.addEdge(2, 1); 
    g1.addEdge(0, 3); 
    g1.addEdge(3, 4); 
    g1.DFS(); 
  
    cout << "\ncut-vertices points in second graph \n"; 
    //Create Graph
    Graph g2(4); 
    g2.addEdge(0, 1); 
    g2.addEdge(1, 2); 
    g2.addEdge(2, 3); 
    g2.DFS(); 
  
    cout << "\n" << endl;
    return 0; 
}

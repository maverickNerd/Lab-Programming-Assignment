#include <iostream>
#include <climits>
#define V 5

using namespace std;

int root[V];

int find_root(int node) {
    while(root[node] >= 0)
        node = root[node];
    return node;
}

//Performing Kruskal's Algo
void kruskal(int adj_matrix[V][V]) {
    int u, v = 0;
    int k = 0, count = 0;
    int a[V];
    int b[V];
    int weight[V];
    int minimum;
    int firstNode, secondNode;
    int min_weight = 0;

    fill_n(root, V, -1); // calling fill to initialize all V values to -1
    
    for (int i = 0; i <= V-1; i++)
        for (int j = 0; j <= V-1; j++)
            if (adj_matrix[i][j] == 0)
                adj_matrix[i][j] = INT_MAX; //Initialize all non adjacent i and j nodes to infinite

    while(count < V-1) {
        minimum = INT_MAX; // Initialize to infinite
        for (int i = 0; i <= V-1; i++) {
            for (int j = 0; j <= V-1; j++) {
                if (adj_matrix[i][j] < minimum) {
                    minimum = adj_matrix[i][j];
                    firstNode = i;
                    secondNode = j;
                }
            }
        }

        u = find_root(firstNode);
        v = find_root(secondNode);

        // Check for loop
        if (u != v) {
            root[v] = u;
            a[k] = firstNode;
            b[k] = secondNode;
            weight[k] = adj_matrix[firstNode][secondNode];
            count++;
            k++;
        }

        adj_matrix[firstNode][secondNode] = adj_matrix[secondNode][firstNode] = INT_MAX; // For edges which are included in MST, mark the weight as INFINITE
    }

    for (int i=0; i<V-1; i++) {
        cout << a[i] << "---" << b[i] << " " << "weight: " << weight[i] << endl;
        min_weight += weight[i];
    }
    cout << "Minimum Weight of Spanning Tree is " << min_weight << endl;
}

int main() {

     int adj_matrix[V][V] = {
     {0,1,0,3,0},
     {2,1,5,8,5},
     {3,2,0,0,7},
     {6,8,0,0,9},
     {1,5,7,9,0}
    };

    kruskal(adj_matrix);
    return 0;
}

#include <iostream>
#include <climits>

#define V 5   // No. of Vertex

using namespace std;

// Performing Prims Algorithm
void prims(int adj_matrix[V][V])
{
    int u, v = 0;
    int i, j, k = 0, count = 0;
    int a[V];
    int b[V];
    int weight[V];
    int minimum;
    int min_weight = 0;
    int visited[V] = { 0 }; // Initialize the visited set to 0.

    for (int i = 0; i <= V-1; i++)
        for (int j = 0; j <= V-1 ; j++)
            if (adj_matrix[i][j] == 0)
                adj_matrix[i][j] = INT_MAX; // Initialize all non adjacent i and j nodes to infinite

    visited[0] = 1; // Initialize the visited set

    while(count<V-1)
    {
        minimum = INT_MAX; // Initialize to infinite
        for (i=0; i<=V-1; i++)
        {
            for (j=0; j<=V-1; j++)
            {
                if (visited[i] != 0 && adj_matrix[i][j] < minimum) // If the first node is not in MST yet, traverse through all the edges connected through it
                {
                    minimum = adj_matrix[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        // Check if vertex is included in MST, if not include it in MST
        if (visited[u]==0 || visited[v]==0)
        {
            a[k] = u;
            b[k] = v;
            weight[k] = adj_matrix[u][v];
            count++;
            k++;
            visited[v] = 1; // Mark the vertex as visited
        }

        adj_matrix[u][v] = adj_matrix[v][u] = INT_MAX; // For edges which are included in MST, mark the weight as INFINITE
    }
    for (int i=0; i<V-1; i++)
    {
        cout << a[i] << "---" << b[i] << " "
             << "Weight: " << weight[i] << endl;
        min_weight += weight[i];
    }
    cout << "Minimum Weight of Spanning Tree is " << min_weight << endl;

}

int main()
{

    int adj_matrix[V][V] = {
     {0,1,0,3,0},
     {2,1,5,8,5},
     {3,2,0,0,7},
     {6,8,0,0,9},
     {1,5,7,9,0}
    };

    prims(adj_matrix);
    return 0;
}


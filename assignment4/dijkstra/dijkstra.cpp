#include <iostream>
#include <climits>

using namespace std;

#define V 5

int minDistance(int distance[], bool ShortestPathTree[])
{
    int min = INT_MAX, min_index;

    for(int i = 0; i <= V-1; i++)
    {
        if(ShortestPathTree[i] == false && distance[i] <= min)
        {
            min = distance[i];
            min_index = i ;
        }
    }

    return min_index;
}

void dijkstra(int adj_matrix[V][V], int source)
{
    int distance[V];
    bool ShortestPathTree[V];

    for(int i = 0; i <= V-1; i++)
    {
        distance[i] = INT_MAX;
        ShortestPathTree[i] = false;
    }

    distance[source] = 0;

    for(int count = 0; count < V - 1; count++)
    {
        int u = minDistance(distance, ShortestPathTree);

        ShortestPathTree[u] = true;

        for(int v = 0; v <= V-1; v++)
            if(ShortestPathTree[v] == 0 && adj_matrix[u][v] != 0 &&
                distance[u] != INT_MAX && distance[u] + adj_matrix[u][v] < distance[v])
                distance[v] = distance[u] + adj_matrix[u][v];
    }

    cout << "Distance from Source " << source << ":" << endl;

    cout << "Vertex\tDistance" << endl;
    for(int i = 0; i <= V-1; i++)
        cout << i << "\t" << distance[i] << endl;
}

int main()
{
    int adj_matrix[V][V] = {{0, 0, 6, 3, 0},
                        {3, 0, 0, 0, 0},
                        {0, 0, 0, 2, 0},
                        {0, 1, 1, 0, 0},
                        {0, 4, 0, 2, 0}};

    dijkstra(adj_matrix, 4);

    return 0;
}

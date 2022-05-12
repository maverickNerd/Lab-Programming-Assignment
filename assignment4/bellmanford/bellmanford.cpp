#include <iostream>
#include <climits>

using namespace std;

#define V 5

void bellmanFord(int adjmatrix[V][V], int source)
{
    unsigned int distance[V];
    for (int i = 0; i <= V-1; i++)
    {
        distance[i] = UINT_MAX;
    }

    distance[source] = 0;

    for (int i = 0; i <= V-1; i++)
    {
        for (int j = 0; j <= V-1; j++)
        {
            for (int k = 0; k <= V-1; k++)
            {
                if (adjmatrix[j][k] != 0 && distance[j] + adjmatrix[j][k] < distance[k])
                {
                    distance[k] = distance[j] + adjmatrix[j][k];
                }
            }
        }
    }

    for (int i = 0; i <= V-1; i++)
    {
        for (int j = 1; j <= V-1; j++)
        {
            if (adjmatrix[i][j] != 0 && distance[i] + adjmatrix[i][j] < distance[j])
            {
                cout << "Given Graph is invalid as it contains negative weights";
                return;
            }
        }
    }

    cout << "Distance of all the V from source " << source << endl;
    cout << "Vertex\tDistance\n";

    for (int i = 0; i <= V-1; i++)
        cout << i << "\t" << distance[i] << endl;
}

int main()
{
    // No of vertex are 5
    int adjmatrix[V][V] = {
                                                {0, 0, 6, 3, 0},
                                                {3, 0, 0, 0, 0},
                                                {0, 0, 0, 2, 0},
                                                {0, 1, 1, 0, 0},
                                                {0, 4, 0, 2, 0}
                                            };
    // Assume Source Vertex is 4
    bellmanFord(adjmatrix, 4);
    return 0;
}


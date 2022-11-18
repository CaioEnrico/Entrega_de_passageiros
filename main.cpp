#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>

using namespace std;

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[])
{

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance
// array
int printSolution(int dist[], int destino)
{
	int i = destino;
	cout << "Vertex \t Distance from Source" << endl;
	cout << i << " \t\t\t\t" << dist[i] << endl;
	cout << endl;
	return dist[i];
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[V][V], int src, int destino, int &res)
{
	int dist[V]; // The output array.  dist[i] will hold the
	// shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is
	// included in shortest
	// path tree or shortest distance from src to i is
	// finalized


	// Initialize all distances as INFINITE and stpSet[] as
	// false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.5
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet,
			// there is an edge from u to v, and total
			// weight of path from src to  v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v]
					&& dist[u] != INT_MAX
					&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	res = printSolution(dist, destino);
}

int main()
{
	int capacidade;
	int Local;
	int res = 0;
	int aux[50];
	int origem = 0;
	int primeiro[50];

	int graph[V][V] =
            {
                        { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
};

	cout << "Entre com a capacidade de lugares do veiculo: " << endl;
	cin >> capacidade;
    int p = 0;

	do
	{
		for (int i = 0; i < capacidade; i++)
		{
			cout << "Entre com o endereco de onde esta o proximo passageiro: " << endl;
			cin >> Local;
			dijkstra(graph, origem, Local, res);
			aux[i] = res;
			if(aux[i] != -1)
				primeiro[i] = aux[i];
            p++;
		}
	} while (p  < capacidade && Local != -1);

    for (int j = 0; j < capacidade; j++)
        for (int i = 0; i < capacidade; i++)
        {
            if (aux[i] > aux[i+1])
            {
                int temp = aux[i];
                aux[i] = aux[i+1];
                aux[i+1] = temp;
            }
        }

    int indicador[capacidade];
    for (int j = 0; j < capacidade; j++)
        for (int i = 0; i < capacidade; i++)
        {
            if (primeiro[i] > primeiro[i+1])
            {
                int temp = primeiro[i];
                primeiro[i] = primeiro[i+1];
                primeiro[i+1] = temp;
            }
        }

    for (int i = 0; i < capacidade; i++)
        if(primeiro[i] == aux[i])
        {
            cout << "Entrega passageiro " << i+1 <<endl;
            cout << primeiro[i] << endl;
        }

	return 0;

}
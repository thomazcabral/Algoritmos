//still very poorly implemented, but it should pass in at least one test case

#include <iostream>

#define INT_MAX 2147483647

using namespace std;

int minCost(int key[], bool mstSet[], int vertices) { //function to find the vertex with the minimum key value, from those that are notin the mstSet
    int min_value = INT_MAX, min_index;

    for(int i = 0; i < vertices; i++) {
        if(!mstSet[i] && key[i] < min_value) {
            min_value = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMst(int parent[], int vertices, int** graph) {
    int total_cost = 0;
    for(int i = 1; i < vertices; i++) {
        total_cost += graph[i][parent[i]];
    }
    cout << total_cost;
}

void primMst(int vertices, int** graph) {
    int parent[vertices]; // store the MST at the moment
    int key[vertices]; // store the key value of the vertices
    bool mstSet[vertices]; // true if the vertex is in the mst

    for(int i = 0; i < vertices; i++) { // initializing the arrays
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0; //defining where to start
    parent[0] = -1;

    for(int i = 0; i < vertices - 1; i++) {
        int pick = minCost(key, mstSet, vertices); //select the vertex with the minimum key value that is not in the mst
        mstSet[pick] = true; // vertex in the mst

        for(int j = 0; j < vertices; j++) {
            if(graph[pick][j] && !mstSet[j] && graph[pick][j] < key[j]) { //update the key value of the vertices that are not in the mst
                parent[j] = pick;
                key[j] = graph[pick][j];
            }
        }
    }
    printMst(parent, vertices, graph);
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    int** graph = new int*[vertices];
    for(int i = 0; i < vertices; i++) { // initializing the graph
        graph[i] = new int[vertices];
        for(int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    for(int i = 0; i < edges; i++) {
        int vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        graph[vertex1][vertex2] = weight; // addEdge function
        graph[vertex2][vertex1] = weight;
    }

    primMst(vertices, graph);
    cout << "\n";
    return 0;
}

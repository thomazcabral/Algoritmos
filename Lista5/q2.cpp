#include <iostream>

#define INT_MAX 2147483647

using namespace std;

struct Edge {
    int vertex, weight;
};

int minCost(int* key, bool* mstSet, int vertices) { //function to find the vertex with the minimum key value, from those that are notin the mstSet
    int min_value = INT_MAX, min_index;

    for(int i = 0; i < vertices; i++) {
        if(!mstSet[i] && key[i] < min_value) {
            min_value = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMst(int* parent, Edge** adjList, int vertices) {
    int total_cost = 0;
    for(int i = 1; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            if(adjList[i][j].vertex == parent[i]) {
                total_cost += adjList[i][j].weight;
                break;
            }
        }
    }
    cout << total_cost;
}

void primMst(int vertices, Edge** adjList) {
    int* parent = new int[vertices]; // store the MST at the moment
    int* key = new int[vertices]; // store the key value of the vertices
    bool* mstSet = new bool[vertices]; // true if the vertex is in the mst

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
            if(adjList[pick][j].vertex != -1 && !mstSet[adjList[pick][j].vertex] && adjList[pick][j].weight < key[adjList[pick][j].vertex]) { //update the key value of the vertices that are not in the mst
                parent[adjList[pick][j].vertex] = pick;
                key[adjList[pick][j].vertex] = adjList[pick][j].weight;
            }
        }
    }
    printMst(parent, adjList, vertices);

    delete[] parent;
    delete[] key;
    delete[] mstSet;
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    Edge** adjList = new Edge*[vertices];
    for(int i = 0; i < vertices; i++) { 
        adjList[i] = new Edge[vertices];
        for(int j = 0; j < vertices; j++) {
            adjList[i][j].vertex = -1;
            adjList[i][j].weight = INT_MAX;
        }
    }

    for(int i = 0; i < edges; i++) {
        int vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;
        if(adjList[vertex1][vertex2].weight > weight) {
            adjList[vertex1][vertex2].vertex = vertex2;
            adjList[vertex1][vertex2].weight = weight;
            adjList[vertex2][vertex1].vertex = vertex1;
            adjList[vertex2][vertex1].weight = weight;
        }
    }

    primMst(vertices, adjList);

    for(int i = 0; i < vertices; i++) {
        delete[] adjList[i];
    }
    delete[] adjList;

    cout << "\n";
    return 0;
}

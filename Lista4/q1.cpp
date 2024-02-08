#include <iostream>

using namespace std;

struct Graph {
    int numVertices;
    int numEdges;
    int **adjMatrix; // adjacency matrix of the graph
    bool *visited; // important to use when doing bfs and dfs search
};

Graph* createGraph(int numVertices) {
    Graph* graph = new Graph; // initializing the pointers
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->adjMatrix = new int*[numVertices];
    graph->visited = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) { // allocating memory for the adjacency matrix
        graph->adjMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numVertices; i++) { // allocating memory for the visited variable
        graph->visited[i] = false;
    }

    return graph;

}

void addEdge(Graph* graph, int vertex1, int vertex2) { // maybe I'll have to add a & for graph
    graph->adjMatrix[vertex1][vertex2] = 1;
    graph->adjMatrix[vertex2][vertex1] = 1;
    graph->numEdges++;
}

void printAdjMatrix(Graph* graph) { // function not necessary to the question, but useful to debug
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            cout << graph->adjMatrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void printRows(Graph* graph) { //useful function for the code
    for (int i = 0; i < graph->numVertices; i++) {
        cout << i << ": ";
        bool isEmpty = true;
        for (int j = graph->numVertices - 1; j >= 0; j--) {
            if (graph->adjMatrix[i][j] == 1) {
                cout << j << " ";
                isEmpty = false;
            }
        }
        if (isEmpty) {
            cout << "Lista Vazia";
        }
        cout << "\n";
    }
}

void DFS(Graph* graph, int vertex) {
    cout << vertex << " ";
    graph->visited[vertex] = true;

    for (int i = graph->numVertices; i >= 0; i--) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFS(graph, i);
        }
    }
}

void deleteGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) { // deallocating memory for the adjacency matrix
        delete[] graph->adjMatrix[i];
    }
    delete[] graph->adjMatrix; // delete the adjacency matrix itself

    delete[] graph->visited; // delete the visited variable itself

    delete graph; // delete the graph itself
}

int main() {
    int numVertices;
    cin >> numVertices;

    Graph* graph = createGraph(numVertices); // creating the graph

    int vertex1, vertex2, condition;

    do {
        cin >> vertex1 >> vertex2 >> condition;

        addEdge(graph, vertex1, vertex2);
    } while(condition != 0);

    printRows(graph);
    cout << "\n";
    DFS(graph, 0); // DFS from the vertex 0

    deleteGraph(graph);

    return 0;
}

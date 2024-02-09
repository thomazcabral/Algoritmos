#include <iostream>

#define INFINITE 1000000000

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

void dijkstra(Graph* graph, int source, int desired_vertex) {
    int* distance = new int[graph->numVertices];
    bool* visited = new bool[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INFINITE;
        visited[i] = false;
    }

    distance[source] = 0;

    for (int count = 0; count < graph->numVertices; count++) {
        int min_distance = INFINITE, min_index;
        for (int v = 0; v < graph->numVertices; v++) {
            if (!visited[v] && distance[v] <= min_distance) {
                min_distance = distance[v], min_index = v;
            }
        }
        visited[min_index] = true;

        if (!visited[desired_vertex] && graph->adjMatrix[min_index][desired_vertex] && distance[min_index] != INFINITE && distance[min_index] + graph->adjMatrix[min_index][desired_vertex] < distance[desired_vertex]) {
            distance[desired_vertex] = distance[min_index] + graph->adjMatrix[min_index][desired_vertex];
        }
    }
    if (distance[desired_vertex] == INFINITE) {
        cout << "Labirinto Impossivel";
    } else {
        cout << distance[desired_vertex];
    }
}

int main() {

    int rows, columns;
    cin >> rows >> columns;
    Graph* graph = createGraph(rows*columns); // creating the graph

    int maze[rows][columns];
    bool upLocked, downLocked, leftLocked, rightLocked;

    int source, desired_vertex;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> maze[i][j];
            maze[i][j] = int(maze[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0) {
                upLocked = true;
            } else {
                upLocked = false;
            }

            if (i == rows - 1) {
                downLocked = true;
            } else {
                downLocked = false;
            }

            if (j == 0) {
                leftLocked = true;
            } else {
                leftLocked = false;
            }

            if (j == columns - 1) {
                rightLocked = true;
            } else {
                rightLocked = false;
            }

            if (maze[i][j] != 1) {
                if(!upLocked) {
                    if (maze[i - 1][j] != 1) {
                        addEdge(graph, maze[i][j], maze[i - 1][j]);
                    }
                }
                if (!downLocked) {
                    if (maze[i + 1][j] != 1) {
                        addEdge(graph, maze[i][j], maze[i + 1][j]);
                    }
                }
                if (!leftLocked) {
                    if (maze[i][j - 1] != 1) {
                        addEdge(graph, maze[i][j], maze[i][j - 1]);
                    }
                }
                if (!rightLocked) {
                    if (maze[i][j + 1] != 1) {
                        addEdge(graph, maze[i][j], maze[i][j + 1]);
                    }
                }
            }
            if (maze[i][j] == '2') {
                source = maze[i][j];
            }
            if (maze[i][j] == '3') {
                desired_vertex = maze[i][j];
            }
        }
    }
    dijkstra(graph, source, desired_vertex);
}

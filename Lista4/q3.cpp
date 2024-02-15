#include <iostream>

using namespace std;

struct Graph {
    int numVertices;
    int numEdges;
    int** adjMatrix; // in a weighed graph, the difference is that an element will not necessarily be 1 or 0, but the weight of the edge
    bool* visited;
    int* distance; // this will be useful for the dijkstra's algorithm
};

Graph* createGraph(int numVertices) {
    Graph* graph = new Graph;
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->adjMatrix = new int*[numVertices];
    graph->visited = new bool[numVertices];
    graph->distance = new int[numVertices];

    for (int i = 0; i < numVertices; i++) { 
        graph->adjMatrix[i] = new int[numVertices]; // allocating memory for the adjacency matrix
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0; // the default here will be 0. If it is not 0, it is the weight of the edge between the vertices
        }
    }

    for (int i = 0; i < numVertices; i++) { 
        graph->visited[i] = false; // initially, no vertex has been visited. This will be useful for the dijkstra's algorithm
    }

    for (int i = 0; i < numVertices; i++) { 
        graph->distance[i] = -1; // initially, the distance from the source to any vertex is infinity
    }

    return graph;

}

void addEdge(Graph* graph, int vertex1, int vertex2, int weight) {
    graph->adjMatrix[vertex1][vertex2] = weight;
    graph->numEdges++;
}

void removeEdge(Graph* graph, int vertex1, int vertex2) {
    graph->adjMatrix[vertex1][vertex2] = 0;
    graph->numEdges--;
}

void dijkstra(Graph* graph, int sourceVertex) {
    graph->distance[sourceVertex] = 0; // the distance to itself is 0

    for (int i = 0; i < graph->numVertices; i++) {
        int minDistanceVertex = -1;

        for (int j = 0; j < graph->numVertices; j++) { // finding the vertex with the minimum distance
            if (!graph->visited[j] && (minDistanceVertex == -1 || graph->distance[j] < graph->distance[minDistanceVertex])) {
                minDistanceVertex = j;
            }
        }

        if (graph->distance[minDistanceVertex] == -1) {
            break; // the vertex is not reachable from the source
        }

        graph->visited[minDistanceVertex] = true;

        for (int j = 0; j < graph->numVertices; j++) {
            int edgeDistance = graph->adjMatrix[minDistanceVertex][j];
            if (edgeDistance > 0 && graph->distance[minDistanceVertex] + edgeDistance < graph->distance[j]) {
                graph->distance[j] = graph->distance[minDistanceVertex] + edgeDistance;
            }
        }
    }
}

int main() {
    int blocks, streets, events;

    cin >> blocks >> streets >> events;
    // blocks = vertices, streets = edges, events = 1 or 2

    Graph* graph = createGraph(blocks);

    for (int i = 0; i < streets; i++) {
        int vertex1, vertex2, time;
        cin >> vertex1 >> vertex2 >> time;
        addEdge(graph, vertex1, vertex2, time);
    }

    for (int j = 0; j < events; j++) {
        int number;
        cin >> number;

        if (number == 1) {
            int vertex1, vertex2, time;
            cin >> vertex1 >> vertex2 >> time;
            if (graph->adjMatrix[vertex1][vertex2] == 0 || graph->adjMatrix[vertex1][vertex2] > time) {
                addEdge(graph, vertex1, vertex2, time);
            }
            else {
                removeEdge(graph, vertex1, vertex2);
                addEdge(graph, vertex1, vertex2, time);
            }
        }
        else {
            int vertex1, vertex2;
            cin >> vertex1 >> vertex2;
            dijkstra(graph, vertex1);
            cout << graph->distance[vertex2] << "\n";
        }
    }
    return 0;
}

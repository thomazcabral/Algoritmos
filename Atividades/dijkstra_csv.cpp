#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define INT_MAX 2147483647 // this is the maximum value for a 32-bit signed integer

using namespace std;


struct Graph {
    int numVertices;
    int numEdges;
    int** adjMatrix; // vector<vector<int>>
    bool* visited; // vector<bool>
    int* distance; // vector<int>
    vector<string> vertices;
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
        graph->distance[i] = INT_MAX; // initially, the distance from the source to any vertex is infinity
    }

    return graph;

}

void addEdge(Graph* graph, string vertex1, string vertex2, int weight) {
    int index1 = find(graph->vertices.begin(), graph->vertices.end(), vertex1) - graph->vertices.begin();
    int index2 = find(graph->vertices.begin(), graph->vertices.end(), vertex2) - graph->vertices.begin();
    graph->adjMatrix[index1][index2] = weight;
    graph->numEdges++;
}

void removeEdge(Graph* graph, string vertex1, string vertex2) {
    int index1 = find(graph->vertices.begin(), graph->vertices.end(), vertex1) - graph->vertices.begin();
    int index2 = find(graph->vertices.begin(), graph->vertices.end(), vertex2) - graph->vertices.begin();
    graph->adjMatrix[index1][index2] = 0;
    graph->numEdges--;
}

void dijkstra(Graph* graph, string sourceVertex) { 
    int sourceIndex = find(graph->vertices.begin(), graph->vertices.end(), sourceVertex) - graph->vertices.begin();
    graph->distance[sourceIndex] = 0; // the distance to itself is 0

    for (int i = 0; i < graph->numVertices; i++) {
        int minDistanceVertex = -1;

        for (int j = 0; j < graph->numVertices; j++) { // finding the vertex with the minimum distance
            if (!graph->visited[j] && (minDistanceVertex == -1 || graph->distance[j] < graph->distance[minDistanceVertex])) {
                minDistanceVertex = j;
            }
        }

        if (graph->distance[minDistanceVertex] == INT_MAX) {
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

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == delimiter) {
            tokens.push_back(token);
            token = "";
        }
        else {
            token += s[i];
        }
    }
    tokens.push_back(token);
    return tokens;
}

int main() {
    int arbitraryNumber = 5;
    Graph* graph = createGraph(arbitraryNumber);

    ifstream file("Airports2.csv");
    string line;

    while(getline(file, line)) {
        vector<string> fields = split(line, ',');
        if (find(graph->vertices.begin(), graph->vertices.end(), fields[0]) == graph->vertices.end()) {
            graph->vertices.push_back(fields[0]);
            graph->numVertices++;
        }
        if (find(graph->vertices.begin(), graph->vertices.end(), fields[1]) == graph->vertices.end()) {
            graph->vertices.push_back(fields[1]);
            graph->numVertices++;
        }

        if (graph->adjMatrix[find(graph->vertices.begin(), graph->vertices.end(), fields[0]) - graph->vertices.begin()][find(graph->vertices.begin(), graph->vertices.end(), fields[1]) - graph->vertices.begin()] == 0) {
            addEdge(graph, fields[0], fields[1], stoi(fields[7]));
        }
        else if (graph->adjMatrix[find(graph->vertices.begin(), graph->vertices.end(), fields[0]) - graph->vertices.begin()][find(graph->vertices.begin(), graph->vertices.end(), fields[0]) - graph->vertices.begin()] > stoi(fields[7])) {
            removeEdge(graph, fields[0], fields[1]);
            addEdge(graph, fields[0], fields[1], stoi(fields[7]));
        }
    }

    string originAirport, destinationAirport;
    cin >> originAirport >> destinationAirport;

    dijkstra(graph, originAirport);

    if(graph->distance[find(graph->vertices.begin(), graph->vertices.end(), destinationAirport) - graph->vertices.begin()] == INT_MAX) {
        cout << "There is no path between the airports\n";
    }
    else {
        cout << "The shortest path between the airports is " << graph->distance[find(graph->vertices.begin(), graph->vertices.end(), destinationAirport) - graph->vertices.begin()] << " minutes\n";
    }
}

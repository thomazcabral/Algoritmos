#include <iostream>

#define INT_MIN -2147483648;

using namespace std;

struct Queue {
    int top, end, size;
    int capacity;
    int* array;
};

Queue* createQueue(int capacity) {
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->top = queue->size = 0;
    queue->end = capacity - 1;
    queue->array = new int[queue->capacity];
    return queue;
}

bool isFull(Queue* queue) {
    if(queue->size == queue->capacity) {
        return true;
    }
    return false;
}

bool isEmpty(Queue* queue) {
    if(queue->size == 0) {
        return true;
    }
    return false;
}

void enqueue(Queue* queue, int vertex) {
    if (! isFull(queue)) {
        queue->end = (queue->end + 1) % queue->capacity;
        queue->array[queue->end] = vertex;
        queue->size++;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return INT_MIN;
    int vertex = queue->array[queue->top];
    queue->top = (queue->top + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return vertex;
}

struct Graph {
    int numVertices;
    int numEdges;
    int **adjMatrix;
    bool *visited;
};

Graph* createGraph(int numVertices) {
    Graph* graph = new Graph;
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->adjMatrix = new int*[numVertices];
    graph->visited = new bool[numVertices];

    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numVertices; i++) {
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int vertex1, int vertex2) {
    graph->adjMatrix[vertex1][vertex2] = 1;
    graph->adjMatrix[vertex2][vertex1] = 1;
    graph->numEdges++;
}

void BFS(Graph* graph, int vertex, int& num) {
    Queue* queue = createQueue(graph->numVertices);
    enqueue(queue, vertex);
    graph->visited[vertex] = true;

    while (!isEmpty(queue)) {
        num++;
        int currentVertex = dequeue(queue);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                enqueue(queue, i);
                graph->visited[i] = true;
            }
        }
    }

    delete queue;
}

void deleteGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        delete[] graph->adjMatrix[i];
    }
    delete[] graph->adjMatrix;
    delete[] graph->visited;
    delete graph;
}

int main() {
    int numVertices, edges;
    cin >> numVertices >> edges;

    Graph* graph = createGraph(numVertices);

    for(int i = 0; i < edges; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;

        addEdge(graph, vertex1 - 1, vertex2 - 1);
    }

    for(int j = 0; j < numVertices; j++) {
        for(int i = 0; i < numVertices; i++) {
            graph->visited[i] = false;
        }
        int num = 0;
        BFS(graph, j, num);
        cout << num;
        if(j != numVertices - 1) {
            cout << " ";
        }
    }
    cout << "\n";

    deleteGraph(graph);

    return 0;
}

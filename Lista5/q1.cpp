#include <iostream>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

struct Queue {
    Node *front, *rear;
};

Node* newNode(int v) {
    Node* node = new Node;
    node->vertex = v;
    node->next = NULL;

    return node;
}

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = q->rear = NULL;

    return q;
}

void enqueue(Queue* q, int v) {
    Node* temp = newNode(v);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(Queue* q) {
    if (q->front == NULL)
        return -1;

    Node* temp = q->front;

    int value = temp->vertex;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    delete temp;

    return value;
}

struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
};

Graph* createGraph(int vertices) {
    Graph* graph = new Graph;
    graph->numVertices = vertices;
    graph->adjLists = new Node*[vertices];
    graph->visited = new bool[vertices];

    for(int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(Graph* graph, int sourceVertex, int dest) {
    Node* newNode = new Node;
    newNode->vertex = dest;
    newNode->next = graph->adjLists[sourceVertex];
    graph->adjLists[sourceVertex] = newNode;

    newNode = new Node;

    newNode->vertex = sourceVertex;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(Graph* graph, int startVertex, int& num) {
    Queue* q = createQueue();

    graph->visited[startVertex] = true;
    enqueue(q, startVertex);

    while(q->front != NULL) {
        int currentVertex = dequeue(q);
        num++;
        Node* temp = graph->adjLists[currentVertex];
        while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == false){
                graph->visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    delete q;
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
    delete graph;
    return 0;
}

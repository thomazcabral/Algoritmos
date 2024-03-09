#include <iostream>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

struct Graph {
    int numVertices;
    Node** adjLists;
};

struct StackNode {
    int data;
    StackNode* next;
};

void push(StackNode** root, int data) {
    StackNode* stackNode = new StackNode;
    stackNode->data = data;
    stackNode->next = *root;
    *root = stackNode; //root is the top of the stack
}

int pop(StackNode** root) {
    if (*root == nullptr) { //if the stack is empty
        return -1;
    }

    StackNode* temp = *root;
    *root = (*root)->next; //root is now the next element in the stack
    int popped = temp->data;
    delete temp;
    return popped;
}

bool DFS(Graph* graph, int startVertex, int endVertex) {
    bool* visited = new bool[graph->numVertices];
    for(int i = 0; i < graph->numVertices; i++) { //initially all vertices as unvisited
        visited[i] = false;
    }

    StackNode* stack = nullptr;
    push(&stack, startVertex); //push the start vertex to the stack

    while(stack != nullptr) {
        int currentVertex = pop(&stack); //pop the top vertex from the stack
        Node* temp = graph->adjLists[currentVertex];

        if(currentVertex == endVertex) { //if we have reached the end vertex the function stops and returns true
            delete[] visited;
            return true;
        }

        if(!visited[currentVertex]) { //if the vertex is unvisited
            visited[currentVertex] = true;
            while(temp) {
                int adjVertex = temp->vertex; 
                if(adjVertex == endVertex) { //if the adjacent vertex is the end vertex the function stops and returns true
                    delete[] visited;
                    return true;
                }
                if(!visited[adjVertex]) {
                    push(&stack, adjVertex); //push the adjacent vertex to the stack
                }
                temp = temp->next;
            }
        }
    }
    delete[] visited;
    return false; //if it didnt returned true before, its because the end vertex was not reached
}

Node* createNode(int vertex) {
    Node* newNode = new Node;
    newNode->vertex = vertex;
    newNode->next = nullptr;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = new Graph;
    graph->numVertices = vertices;
    graph->adjLists = new Node*[vertices];
    for (int i = 0; i < vertices; i++) { //initialize all vertices as nullptr
        graph->adjLists[i] = nullptr;
    }
    return graph;
}

void addEdge(Graph* graph, int sourceVertex, int destinationVertex) {
    Node* newNode = createNode(destinationVertex);
    newNode->next = graph->adjLists[sourceVertex];
    graph->adjLists[sourceVertex] = newNode; //add an edge from source to destination

    newNode = createNode(sourceVertex);
    newNode->next = graph->adjLists[destinationVertex];
    graph->adjLists[destinationVertex] = newNode; //add an edge from destination to source
}

void get_horizontal_wall_separation(int wall, int N, int &square1, int &square2) {
    int row = wall / (N - 1);
    int col = wall % (N - 1);
    square1 = row * N + col;
    square2 = row * N + col + 1;
}

void get_vertical_wall_separation(int wall, int N, int &square1, int &square2) {
    int row = wall / N;
    int col = wall % N;
    square1 = row * N + col;
    square2 = (row + 1) * N + col;
}

bool is_horizontal_wall(int wall, int N, int &num) {
    if(wall <= (N - 2)) {
        return true;
    } else if((N - 1) <= wall && wall <= (2 * N - 2)) {
        return false;
    } else {
        num += 1;
        return is_horizontal_wall(wall - (2 * N - 1), N, num);
    }
}

int main() {
    int mazes;
    cin >> mazes;
    for(int i = 0; i < mazes; i++) {
        int N, wallsRemoved, tests;
        cin >> N >> wallsRemoved >> tests;
        Graph* graph = createGraph(N * N);
        for(int j = 0; j < wallsRemoved; j++) {
            int wall;
            cin >> wall;

            int square1, square2 = 0;
            int num = 0;

            if(is_horizontal_wall(wall, N, num)) {
                get_horizontal_wall_separation(wall - (N * num), N, square1, square2);
            } else {
                get_vertical_wall_separation(wall - ((N - 1) * (num + 1)), N, square1, square2);
            }
            addEdge(graph, square1, square2);
        }
        
        for(int j = 0; j < tests; j++) {
            int startVertex, endVertex;
            cin >> startVertex >> endVertex;
            if(DFS(graph, startVertex, endVertex)) {
                cout << i << "." << j << " 1" << "\n";
            } else {
                cout << i << "." << j << " 0" << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}

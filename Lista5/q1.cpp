#include <iostream>

using namespace std;

struct Stack {
    int* array;
    int top;
    int capacity;

    Stack(int size) {
        capacity = size;
        array = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] array;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(int value) {
        if (!isFull()) {
            top++;
            array[top] = value;
        }
    }

    int pop() {
        if (!isEmpty()) {
            int value = array[top];
            top--;
            return value;
        }
    }

    int checkTop() {
        if (!isEmpty()) {
            return array[top];
        }
    }
};

Stack createStack(int size) {
    return Stack(size);
}

struct Graph {
    int numVertices;
    int numEdges;
    int **adjMatrix; // adjacency matrix of the graph
    bool *visited; // important to use when doing bfs and dfs search
    Stack **stacks; // array of stacks
};

Graph* createGraph(int numVertices) {
    Graph* graph = new Graph; // initializing the pointers
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->adjMatrix = new int*[numVertices];
    graph->visited = new bool[numVertices];
    graph->stacks = new Stack*[numVertices];

    for (int i = 0; i < numVertices; i++) { // allocating memory for the adjacency matrix
        graph->adjMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numVertices; i++) { // allocating memory for the visited variable
        graph->visited[i] = false;
    }

    for (int i = 0; i < numVertices; i++) {
        graph->stacks[i] = new Stack(numVertices);
    }

    return graph;

}

void addEdge(Graph* graph, int vertex1, int vertex2) { // maybe I'll have to add a & for graph
    graph->adjMatrix[vertex1][vertex2] = 1;
    graph->adjMatrix[vertex2][vertex1] = 1;
    graph->numEdges++;

    graph->stacks[vertex1]->push(vertex2);
    graph->stacks[vertex2]->push(vertex1);
}

/*void displayStacks(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        cout << i << ": ";
        if (graph->stacks[i]->isEmpty()) {
            cout << "Lista Vazia";
        }
        else {
            while(!graph->stacks[i]->isEmpty()) {
                cout << graph->stacks[i]->pop() << " ";
            }
        }
        cout << "\n";
    }
}
*/

int DFS(Graph* graph, int vertex, int& num) {
    cout << vertex << " ";
    graph->visited[vertex] = true;

    for (int i = graph->numVertices - 1; i >= 0; i--) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            num++;
            DFS(graph, i, num);
        }
    }
}

void deleteGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) { // deallocating memory for the adjacency matrix
        delete[] graph->adjMatrix[i];
    }
    delete[] graph->adjMatrix; // delete the adjacency matrix itself

    delete[] graph->visited; // delete the visited variable itself

    for (int i = 0; i < graph->numVertices; i++) {
        delete graph->stacks[i];
    }
    delete[] graph->stacks;

    delete graph; // delete the graph itself
}

int main() {
    int numVertices, edges;
    cin >> numVertices >> edges;

    Graph* graph = createGraph(numVertices); // creating the graph

    for(int i = 0; i < edges; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;

        addEdge(graph, vertex1 - 1, vertex2 - 1);
    }

    for(int j = 0; j <= edges; j++) {
        int num = 0;
        DFS(graph, j, num);
        cout << num << " ";
    }
    cout << "\n";

    //displayStacks(graph);
    //cout << "\n";
    //num = DFS(graph, 0); // DFS from the vertex 0

    deleteGraph(graph);

    return 0;
}

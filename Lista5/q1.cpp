#include <iostream>

using namespace std;

struct DSU {
    int* parent;
    int* rank;
    int* size;

    DSU(int vertices) { //constructor
        parent = new int[vertices];
        rank = new int[vertices]();
        size = new int[vertices]();

        for (int i = 0; i < vertices; ++i) { //initializing the parent and size of each set
            parent[i] = i;
            size[i] = 1;
        }
    }

    ~DSU() { //deallocating memory for the arrays 
        delete[] parent;
        delete[] rank;
        delete[] size;
    }

    int find(int set) { //finding the parent of the set
        if (set != parent[set])
            parent[set] = find(parent[set]);
        return parent[set];
    }

    void union_sets(int setA, int setB) { //union of two sets
        setA = find(setA);
        setB = find(setB);
        
        if (setA != setB) {
            if (rank[setA] < rank[setB])
                swap(setA, setB);

            parent[setB] = setA;

            size[setA] += size[setB];
            if (rank[setA] == rank[setB])
                rank[setA]++;
        }
    }
};

struct Node { //node for the adjacency list
    int vertex;
    Node* next;
};

struct AdjList {
    Node* head;
};

Node* createNode(int v) { //creating a new node for the adjacency list
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->next = nullptr;
    return newNode;
}

int main() {
    int numVertices, edges;
    cin >> numVertices >> edges;

    DSU dsu(numVertices);
    AdjList* adjLists = new AdjList[numVertices];

    for(int i = 0; i < numVertices; i++) { //initializing the adjacency list
        adjLists[i].head = nullptr;
    }

    for(int i = 0; i < edges; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;

        vertex1--;
        vertex2--;

        Node* newNode = createNode(vertex2); //adding the edge to the adjacency list
        newNode->next = adjLists[vertex1].head; 
        adjLists[vertex1].head = newNode;

        newNode = createNode(vertex1); //the same but to the other vertex
        newNode->next = adjLists[vertex2].head;
        adjLists[vertex2].head = newNode;

        dsu.union_sets(vertex1, vertex2);
    }

    int* reachable = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) { //finding the size of the set of each vertex
        int root = dsu.find(i);
        reachable[i] = dsu.size[root];
    }

    for(int j = 0; j < numVertices; j++) { //printing the size of the set of each vertex
        cout << reachable[j];
        if(j != numVertices - 1) {
            cout << " ";
        }
    }
    cout << "\n";

    delete[] reachable; //deallocating memory for the arrays 
    for(int i = 0; i < numVertices; i++) { //deallocating memory for the adjacency list
        Node* node = adjLists[i].head;
        while (node) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete[] adjLists;

    return 0;
}

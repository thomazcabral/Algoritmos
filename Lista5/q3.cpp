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

        for (int i = 0; i < vertices; i++) { //initializing the parent and size of each set
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
        DSU dsu(N * N);
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
            dsu.union_sets(square1, square2);
        }
        
        for(int j = 0; j < tests; j++) {
            int startVertex, endVertex;
            cin >> startVertex >> endVertex;
            if(dsu.find(startVertex) == dsu.find(endVertex)) {
                cout << i << "." << j << " 1" << "\n";
            } else {
                cout << i << "." << j << " 0" << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}

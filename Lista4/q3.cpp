#include <iostream>

using namespace std;

int main() {
    int blocks, streets, events;

    cin >> blocks >> streets >> events;

    for (int i = 0; i < streets; i++) {
        int vertex1, vertex2, time;
        cin >> vertex1 >> vertex2 >> time;
        // add edge from vertex1 to vertex2 with weight time
    }

    for (int j = 0; i < events; j++) {
        int number;
        cin >> number;

        if (number == 1) {
            int vertex1, vertex2, time;
            cin >> vertex1 >> vertex2 >> time;
            // add edge from vertex1 to vertex2 with weight time
        }
        else {
            int vertex1, vertex2;
            cin >> vertex1 >> vertex2;
            // find shortest path from vertex1 to vertex2
        }
    }
}

// I tried to use Djikstra's algorithm, but it wasnt the best choice, so I used BFS instead

#include <iostream>

using namespace std;

int directionsX[] = {-1, 1, 0, 0}; // search through X neighbors (right and left)
int directionsY[] = {0, 0, -1, 1}; // search through Y neighbors (up and down)

struct Vertex {
    int x, y;
};

struct Queue {
    Vertex* block;
    int front, rear;
    int size; // rows * columns, avoiding the use of MAX_ROWS and MAX_COLUMNS

    Queue(int size) { // initializing Queue
        this->size = size; // I know that I have to do this, but Im still not sure why
        block = new Vertex[size];
        front = rear = 0;
    }

    ~Queue() { // deleting Queue
        delete[] block;
    }

    // Queue functions
    void push(Vertex v) {
        block[rear++] = v; // adding an element to the end of the queue
    }

    Vertex pop(Vertex v) {
        return block[front++]; // removing an element from the front of the queue
    }

    bool isEmpty() {
        return front == rear; // checking if the queue is empty
    }
};

int bfs(int** maze, Vertex* sourceVertex, Vertex* destinationVertex, int rows, int columns) {
    Queue* queue = new Queue(rows * columns); // initializing a queue
    bool** visited = new bool*[rows]; // initializing a visited array with rows length
    int** distance = new int*[rows]; // initializing a distance array with rows length

    for (int i = 0; i < rows; i++) {
        visited[i] = new bool[columns]; // creating an array for each row
        distance[i] = new int[columns]; // same as line above
        for(int j = 0; j < columns; j++) { // RIP complexity time
            visited[i][j] = false; // initializing all elements of visited as false
            distance[i][j] = 0; // initializing all elements of distance as 0
        }
    }

    queue->push(*sourceVertex); // adding the source vertex to the queue, first step of bfs
    visited[sourceVertex->x][sourceVertex->y] = true; // marking the source vertex as visited

    while (!queue->isEmpty()) {
        Vertex current = queue->pop(current); // removing the first element from the queue
        
        if (current.x == destinationVertex->x && current.y == destinationVertex->y) { // checking if the current vertex is the destination vertex
            return distance[current.x][current.y]; // if so, it returns the distance and the functions stops
        }

        for (int i = 0; i < 4; i++) { // checking in all 4 directions (neighbors)
            int neighborX = current.x + directionsX[i];
            int neighborY = current.y + directionsY[i];

            if (neighborX >= 0 && neighborX < rows && neighborY >= 0 && neighborY < columns && maze[neighborX][neighborY] != 1 && !visited[neighborX][neighborY]) {
                // let me explain this condition: firsty, it checks if neighborX and neighborY are inside the maze
                // after, it checks if the neighbor isnt a wall, represent by 1 and after, it checks if the neighbor wasnt visited yet
                queue->push({neighborX, neighborY}); // if all conditions are true, it adds the neighbor to the queue
                visited[neighborX][neighborY] = true; // marks the neighbor as visited
                distance[neighborX][neighborY] = distance[current.x][current.y] + 1;
            }
        }
    }
    return -1; // do this if the maze is impossible
}

int main() {
    int rows, columns;
    cin >> rows >> columns;

    int** maze = new int*[rows];
    for(int i = 0; i < rows; i++) { // doing this to avoid the use of MAX_ROWS and MAX_COLUMNS
        maze[i] = new int[columns]; // creating a matrix with rows and columns length
    }
    Vertex* source = new Vertex();
    Vertex* destination = new Vertex();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> maze[i][j];
            if (maze[i][j] == 2) {
                //*source = {i, j};
                source->x = i;
                source->y = j;
            }
            else if (maze[i][j] == 3) {
                //*destination = {i, j};
                destination->x = i;
                destination->y = j;
            }
            // if maze[i][j] is 1, the way is blocked and this will be resolved within the bfs function
            // if maze[i][j] is 0, it will automatically suppose it is a free way
        }
    }

    int shortestPath = bfs(maze, source, destination, rows, columns);

    if (shortestPath == -1) {
        cout << "Labirinto Impossivel" << "\n";
    }
    else {
        cout << shortestPath << "\n";
    }

    for(int i = 0; i < rows; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    delete source;
    delete destination; // deleting the last pieces of memory remaining in this code

    return 0;
}

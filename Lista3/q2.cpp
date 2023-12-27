#include <iostream>
#include <string>

using namespace std;

struct People {
    string name;
    int registration;
    int priority;
};

struct ValuePair {
    People* person;
    int index;
};

void swap(People*& a, People*& b) {
    People* temp = a;
    a = b;
    b = temp;
}

/*void initializeHashTable(ValuePair hashtable[][], int rows, int seatsPerRow) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < seatsPerRow; j++) {
            hashtable[i][j].value = -1;
            hashtable[i][j].index = i + 1;
        }
    }
}
*/
// MAX HEAP

void maxHeapify(People* array[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && array[left]->priority > array[largest]->priority) {
        largest = left;
    }

    if(right < n && array[right]->priority > array[largest]->priority) {
        largest = right;
    }

    if(largest != i) {
        swap(array[i], array[largest]);
        maxHeapify(array, n, largest);
    }
}

void buildMaxHeap(People* array[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(array, n, i);
    }
}

void insertMaxHeap(People* array[], int& n, People* person) {
    n++;
    int i = n - 1;
    array[i] = person;

    while(i > 0 && array[(i - 1) / 2]->priority < array[i]->priority) {
        swap(array[i], array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

People* removeMaxHeap(People* array[], int& n) {
    People* root = array[0];
    array[0] = array[n - 1];
    n--;

    maxHeapify(array, n, 0);

    return root;
}

// MIN HEAP

void minHeapify(People* array[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && array[left]->priority < array[smallest]->priority) {
        smallest = left;
    }

    if(right < n && array[right]->priority < array[smallest]->priority) {
        smallest = right;
    }

    if(smallest != i) {
        swap(array[i], array[smallest]);
        minHeapify(array, n, smallest);
    }
}

void buildMinHeap(People* array[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(array, n, i);
    }
}

void insertMinHeap(People* array[], int& n, People* person) {
    n++;
    int i = n - 1;
    array[i] = person;

    while(i > 0 && array[(i - 1) / 2]->priority > array[i]->priority) {
        swap(array[i], array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

People* removeMinHeap(People* array[], int& n) {
    People* root = array[0];
    array[0] = array[n - 1];
    n--;

    minHeapify(array, n, 0);

    return root;
}

int main() {
    int rows, seatsPerRow;
    cin >> rows >> seatsPerRow;
    ValuePair hashtable[rows][seatsPerRow];
    People person;
}

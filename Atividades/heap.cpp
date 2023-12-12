#include <iostream>
#include <string>

using namespace std;

void maxHeapify(int array[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if(left < size && array[left] > array[largest]) {
        largest = left;
    }

    if(right < size && array[right] > array[largest]) {
        largest = right;
    }

    if(largest != root) {
        swap(array[root], array[largest]);
        maxHeapify(array, size, largest);
    }
}

void buildHeap(int array[], int size) {
	int startIndex = 0;
    if(size % 2 == 0) {
        startIndex = size / 2;
    }
    else {
        startIndex = (size - 1) / 2;
    }

    for(int i = startIndex; i >= 0; i--) {
        maxHeapify(array, size, i);
    }
}

void displayHeap(int array[], int size) {
    cout << "Heap: " << "\n";

    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
}

int main() {
    int v1[] = {3, 10, 40, 1, 60, 34, 21, 100, 5, 31, 2, 4, 6};
    int sizeV1 = sizeof(v1) / sizeof(int);

    buildHeap(v1, sizeV1);
    displayHeap(v1, sizeV1);

    int v2[] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 11, 1001};
    int sizeV2 = sizeof(v2) / sizeof(int);

    buildHeap(v2, sizeV2);
    displayHeap(v2, sizeV2);

    int v3[] = {1, 2, 3, 9, 8, 7, 6, 5, 4, 20, 30, 40, 50, 60};
    int sizeV3 = sizeof(v3) / sizeof(int);

    buildHeap(v3, sizeV3);
    displayHeap(v3, sizeV3);

    return 0;
}

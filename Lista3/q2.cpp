#include <iostream>
#include <string>

using namespace std;

struct People {
    string name;
    int registration;
    int priority;
};

struct HashNode {
    People** heap;
    int size;
};

struct HashTable {
    HashNode** table;
    int size;
};

int hashFunction(HashTable* hashtable, int rows, int seatsPerRow) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < seatsPerRow; j++) {
            if(hashtable->table[i]->heap[j] == nullptr) {
                return i;
            }
        }
    }
    return -1; // if everything is occupied
}

People* createPerson(string name, int registration, int priority) {
    People* newPerson = new People;
    newPerson->name = name;
    newPerson->registration = registration;
    newPerson->priority = priority;

    return newPerson;
}

// MAX HEAP

void maxHeapify(People* array[], int size, int i) {
    if(i >= size) {
        return;
    }

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && array[left]->priority > array[largest]->priority) {
        largest = left;
    }

    if(right < size && array[right]->priority > array[largest]->priority) {
        largest = right;
    }

    if(largest != i) {
        swap(array[i], array[largest]);
        maxHeapify(array, size, largest);
    }
}

void buildMaxHeap(People* array[], int size) {
    if(size >= 2) {
        for(int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(array, size, i);
        }
    }
}

void insertMaxHeap(HashNode* node, People* person) {
    node->heap[node->size] = person;
    node->size++;
    buildMaxHeap(node->heap, node->size);
}

People* removeMaxHeap(HashNode* node) {
    if(node->size == 1) {
        node->size--;
        return node->heap[0];
    }

    People* root = node->heap[0];
    node->heap[0] = node->heap[node->size - 1];
    node->size--;

    maxHeapify(node->heap, node->size, 0);

    return root;
}

// MIN HEAP

void minHeapify(People* array[], int size, int i) {
    if(i >= size) {
        return;
    }

    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && array[left]->priority < array[smallest]->priority) {
        smallest = left;
    }

    if(right < size && array[right]->priority < array[smallest]->priority) {
        smallest = right;
    }

    if(smallest != i) {
        swap(array[i], array[smallest]);
        minHeapify(array, size, smallest);
    }
}

void buildMinHeap(People* array[], int size) {
    if(size >= 2) {
        for(int i = size / 2 - 1; i >= 0; i--) {
            minHeapify(array, size, i);
        }
    }
}

void insertMinHeap(HashNode* node, People* person) {
    node->heap[node->size] = person;
    node->size++;
    buildMinHeap(node->heap, node->size);
}

People* removeMinHeap(HashNode* node) {
    if(node->size == 1) {
        node->size--;
        return node->heap[0];
    }

    People* root = node->heap[0];
    node->heap[0] = node->heap[node->size - 1];
    node->size--;

    minHeapify(node->heap, node->size, 0);

    return root;
}

// 3 FUNCTIONS

void insertTheater_CAD(HashTable* hashtable, int rows, int seatsPerRow, People* person, HashNode* waitingList) {
    int row = hashFunction(hashtable, rows, seatsPerRow);

    if(row != -1) {
        cout << person->name << " (" << person->registration << ") foi alocado(a) na fileira " << row + 1 << "\n";
        insertMinHeap(hashtable->table[row], person);
    }
    else { // the theater is full
        People* leastPriorityPerson = nullptr;
        int leastPriorityRow = -1;
        for(int i = 0; i < rows; i++) {
            People* someone = hashtable->table[i]->heap[0];
            if(leastPriorityPerson == nullptr || someone->priority < leastPriorityPerson->priority) {
                leastPriorityPerson = someone;
                leastPriorityRow = i;
            }
        }
        People* someone = removeMinHeap(hashtable->table[leastPriorityRow]);

        if(someone->priority < person->priority) {
            insertMinHeap(hashtable->table[leastPriorityRow], person); // insert the new person in theater
            insertMaxHeap(waitingList, someone); // insert the person from the theater in the waiting list
            cout << person->name << " (" << person->registration << ") foi alocado(a) na fileira " << leastPriorityRow + 1 << "\n";

        }
        else if(someone->priority > person->priority) {
            insertMaxHeap(waitingList, person); // insert the new person in the waiting list
            insertMinHeap(hashtable->table[leastPriorityRow], someone); // insert the person from the theater in the theater
            cout << person->name << " (" << person->registration << ") nao foi alocado(a) em nenhuma fileira" << "\n";
        }
        else {
            if(someone->registration < person->registration) {
                insertMaxHeap(waitingList, person); // insert the new person in the waiting list
                insertMinHeap(hashtable->table[leastPriorityRow], someone); // insert the person from the theater in the theater
                cout << person->name << " (" << person->registration << ") nao foi alocado(a) em nenhuma fileira" << "\n";

            }
            else {
                insertMinHeap(hashtable->table[leastPriorityRow], person); // insert the new person in theater
                insertMaxHeap(waitingList, someone); // insert the person from the theater in the waiting list
                cout << person->name << " (" << person->registration << ") foi alocado(a) na fileira " << leastPriorityRow + 1 << "\n";

            }
        }
    }
}

void verifyTheater_VER(HashTable* HashTable, int rows, int seatsPerRow, string name, int registrationNumber, HashNode* waitingList) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < seatsPerRow; j++) {
            if(HashTable->table[i]->heap[j] != nullptr) {
                if(HashTable->table[i]->heap[j]->registration == registrationNumber && HashTable->table[i]->heap[j]->name == name) {
                    cout << "Sentado(a) na fileira " << i + 1 << "\n";
                    return;
                }
            }
        }
    }
    // If the person is not in the theater
    for(int i = 0; i < waitingList->size; i++) {
        if(waitingList->heap[i]->registration == registrationNumber && waitingList->heap[i]->name == name) {
            cout << "Sem assento" << "\n";
            return;
        }
    }
    // If the person does not exist
    cout << "Inexistente" << "\n";
}

void removeTheater_REM(HashTable* HashTable, int rows, int seatsPerRow, string name, int registrationNumber, HashNode* waitingList) {
    People* searched = nullptr;
    int row = -1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < seatsPerRow; j++) {
            if(HashTable->table[i]->heap[j] != nullptr) {
                if(HashTable->table[i]->heap[j]->registration == registrationNumber && HashTable->table[i]->heap[j]->name == name) {
                    searched = HashTable->table[i]->heap[j];
                    row = i;
                }
            }
        }
    }
    if(searched != nullptr) {
        People* removed = removeMinHeap(HashTable->table[row]);
        People* queued = removeMaxHeap(waitingList);
        insertMinHeap(HashTable->table[row], queued);
    }

    if(searched == nullptr) {
        for(int i = 0; i < waitingList->size; i++) {
            if(waitingList->heap[i]->registration == registrationNumber && waitingList->heap[i]->name == name) {
                searched = waitingList->heap[i];
                row = i;
            }
        }
    }

    if(searched != nullptr) {
        People* removed = removeMaxHeap(waitingList);
    }

    if(searched == nullptr) {
        cout << "Inexistente" << "\n";
    }
    else {
        cout << "Removido(a)";
    }
}

void clean(HashTable* hashtable, int rows, HashNode* waitingList) {
    for(int i = 0; i < rows; i++) {
        delete[] hashtable->table[i]->heap;
        delete hashtable->table[i];
    }
    delete[] hashtable->table;
    delete hashtable;
    delete[] waitingList->heap;
    delete waitingList;
}

int main() {
    int rows, seatsPerRow;
    cin >> rows >> seatsPerRow;

    HashTable* hashtable = new HashTable; // create hash table
    hashtable->size = rows;
    hashtable->table = new HashNode*[rows - 1];

    for(int i = 0; i < rows; i++) { // create hash nodes
        hashtable->table[i] = new HashNode;
        hashtable->table[i]->heap = new People*[seatsPerRow];
        hashtable->table[i]->size = 0;
        for (int j = 0; j < seatsPerRow; j++) { // possible tle issue
            hashtable->table[i]->heap[j] = nullptr;
        }
    }

    HashNode* waitingList = new HashNode;
    waitingList->heap = new People*[2 * rows * seatsPerRow];
    waitingList->size = 0;

    int commands;
    cin >> commands;

    int registrationNumber = 1;

    for(int i = 0; i < commands; i++) {
        string command;
        cin >> command;

        if(command == "CAD") {
            string name;
            cin >> name;

            int priority;
            cin >> priority;

            People* person = createPerson(name, registrationNumber, priority);
            insertTheater_CAD(hashtable, rows, seatsPerRow, person, waitingList);
            registrationNumber++;
        }

        if(command == "VER") {
            string name;
            cin >> name;

            int registration;
            cin >> registration;

            verifyTheater_VER(hashtable, rows, seatsPerRow, name, registration, waitingList);
        }
    }

    clean(hashtable, rows, waitingList);
    return 0;
}

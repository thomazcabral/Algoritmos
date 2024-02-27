#include <iostream>
#include <string>

using namespace std;

typedef struct Node {
    string object;
    int weight;
    struct Node* next; //pointer
} Node;

Node* create(string object, int weight) {
    Node* newNode = new Node;
    newNode->object = object;
    newNode->weight = weight; //pointer named value
    newNode->next = nullptr; //pointer named next
    return newNode;
}

void insert(string object, int weight, Node*& head) {
    Node* newNode = create(object, weight);
    if(head == nullptr) {
        head= newNode;
    }
    else {
        Node* current = head;
        while(current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

}

int main() {
    int size;

    cin >> size;

    for (int i = 0; i++; i < size) {
        string object;
        int weight;

        cin >> object >> weight;
    }
    // all items are added to the queue,
    
    return 0;
}

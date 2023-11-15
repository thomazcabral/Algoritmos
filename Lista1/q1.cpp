#include <iostream>

using namespace std;

typedef struct Node {
    int value;
    struct Node* next; //pointer
} Node;

bool remainder(int num1, int num2) {
    if(num1 % 2 == num2 % 2) {
        return true;
    }
    return false;
}

int abs(int num1, int num2) {
    if(num1 > num2) {
        return num1 - num2;
    }
    return num2 - num1;
}

Node* create(int value, int& k) {
    Node* newNode = new Node;
    newNode->value = value; //pointer named value
    newNode->next = nullptr; //pointer named next
    k++;
    return newNode;
}


void insert(int value, Node*& head, int& k) {
    if(head != nullptr && remainder(value, head->value)) {
        head->value = abs(value, head->value);
    }
    else {
        Node* newNode = create(value, k);
        head = newNode;
    }

}

int main() {
    int plays;

    cin >> plays;

    for(int i = 0; i < plays; i++) {
        Node* head = nullptr;
        int number;
        int k = 0;

        while(cin >> number) {
            if(number == 0) {
                break;
            }
            insert(number, head, k);
        }

        if(head != 0) {
            cout << "Pilha " << i + 1 << ": " << k << " " << head->value << "\n";
        }
        else {
            cout << "Pilha " << i + 1 << ": " << 0 << " " << -1 << "\n";
        }
    }
    return 0;
}

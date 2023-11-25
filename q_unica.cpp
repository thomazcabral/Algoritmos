#include <iostream>

using namespace std;

typedef struct Node {
    int number;
    Node* left;
    Node* right;
    Node* father;
} Node;

Node* create(int number) {
    Node* newNode = new Node;
    newNode->number = number;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->father = nullptr;

    return newNode;
}

Node* search(int value, Node*& node) { //number to be found and the root of the tree
    Node* current = node;
    while(current != nullptr && current->number != value) {
        if(current->number < value) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return current;
}

int height(int number, Node*& node) { //number to find the height and the root of the tree
    Node* current = search(number, node);
    int h = 0;
    while(current->father != nullptr) {
        current = current->father;
    }
    return h;
}

int balanceFactor(Node*& node) {
    if(node == nullptr) {
        return 0;
    }
    return (node->left - node->right);
}

void inOrder(Node*& node) {
    if(node != nullptr) {
        inOrder(node->left);
        cout << node->number << " "; //TO-DO!!! adapt to the question output 
        inOrder(node->right);
    }
}

void preOrder(Node*& node) {
    if(node != nullptr) {
        cout << node->number << " "; //TO-DO!!! adapt to the question output
        preOrder(node->left);
        preOrder(node->right);
    }
}

void postOrder(Node*& node) {
    if(node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->number << " "; //TO-DO!!! adapt to the question output 
    }
}

/*
insert funcion
remove function
rotate left function
rotate right function
balance funtion to be used on insertion and removal
main function
*/

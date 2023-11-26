#include <iostream>
#include <string>

using namespace std;

typedef struct Node {
    int number;
    Node* left;
    Node* right;
    int height;
} Node;

Node* create(int number) {
    Node* newNode = new Node;
    newNode->number = number;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 0;

    return newNode;
}

int height(Node*& node) { //number to find the height and the root of the tree
    return node->height;
}

int balanceFactor(Node* node) { //node to be analyzed
    if(node == nullptr) {
        return 0;
    }
    return (height(node->left) - height(node->right));
}

void inOrder(Node* node) { //root
    if(node != nullptr) {
        cout << "[";
        inOrder(node->left);
        cout << node->number << " "; //TO-DO!!! adapt to the question output 
        inOrder(node->right);
        cout << "]";
        cout << "\n";
    }
}

void preOrder(Node* node) { //root
    if(node != nullptr) {
        cout << "[";
        cout << node->number << " "; //TO-DO!!! adapt to the question output
        preOrder(node->left);
        preOrder(node->right);
        cout << "]";
        cout << "\n";
    }
}

void postOrder(Node* node) { //root
    if(node != nullptr) {
        cout << "[";
        postOrder(node->left);
        postOrder(node->right);
        cout << node->number << " "; //TO-DO!!! adapt to the question output 
        cout << "]";
        cout << "\n";
    }
}

Node* rotateLeft(Node*& node) {
    Node* node2 = node->left;
    Node* node3 = node->right;

    node2->left = node;
    node->right = node3;

    node->height = max(height(node->left), height(node->right)) + 1;
    node2->height = max(height(node2->left), height(node2->right)) + 1;

    return node2;
}

Node* rotateRight(Node*& node) {
    Node* node2 = node->right;
    Node* node3 = node->left;

    node2->right = node;
    node->left = node3;

    node->height = max(height(node->left), height(node->right)) + 1;
    node2->height = max(height(node2->left), height(node2->right)) + 1;

    return node2;
}

void balance(Node*& node, int number) { 
    int bal = balanceFactor(node);

    if(bal > 1) { //left imbalance
        if(number < node->left->number) {
            node = rotateRight(node); //simple rotation to the right
        }
        else {
            node->left = rotateLeft(node->left);
            node = rotateRight(node); //double rotation to the right
        }
    }

    if(bal < -1) { //right imbalance
        if(number > node->right->number) {
            node = rotateLeft(node); //simple rotation to the left
        }
        else {
            node->right = rotateRight(node->right);
            node = rotateLeft(node); //double rotation to the left
        }
    }
}

Node* insert(Node*& node, int number) { //root
    Node* current = node;

    while(current != nullptr) {
        if(number < current->number) {
            current = current->left;
        }
        else if(number > current->number) {
            current = current->right;
        }
        else {
            return node;
        }
    }

    Node* newNode = create(number);

    node->height = max(height(node->left), height(node->right)) + 1;

    balance(node, number);

    return node;
}

Node* minValue(Node* node) {
    while(node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* remove(Node*& node, int number) { //root and number to be removed
    if(node == nullptr) {
        return node;
    }

    while(node->number != number) {
        if(number < node->number) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    //node with one or no child
    if(node->left == nullptr) {
        Node* temp = node->right;
        delete node;
        balance(temp, number);
        return temp;
    }
    else if(node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        balance(temp, number);
        return temp;
    }

    //node with 2 children
    Node* temp = minValue(node->right);
    node->number = temp->number;
    node->right = remove(node->right, temp->number);
}

int main() {
    Node* tree = nullptr; //root

    while(true) {
        string command;
        cin >> command;
        if(command == "FIM") {
            break;
        }
        else {
            if(command == "ADICIONA" || command == "REMOVE" || command == "NIVEL") {
                int num;
                cin >> num;
                if(command == "ADICIONA") {
                    insert(tree, num);
                }
                else if(command == "REMOVE") {
                    remove(tree, num);
                }
                else {
                    cout << height(tree);
                }
            }
            else {
                string type;
                cin >> type;
                if(type == "PREORDEM") {
                    preOrder(tree);
                }
                else if(type == "EMORDEM") {
                    inOrder(tree);
                }
                else {
                    postOrder(tree);
                }
            }
        }
    }
    return 0;
}

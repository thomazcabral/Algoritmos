/*
Les Champs-Elysées - Joe Dassin

Je m'baladais sur l'avenue
Le cœur ouvert a l'inconnu
J'avais envie de dire bonjour
A n'importe qui
N'importe qui et ce fut toi
Je t'ai dis n'importe quoi
Il suffisait de te parler
Pour t'apprivoiser
Aux Champs-Elysées
Aux Champs-Elysées
...

*/
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
    if(node == nullptr) {
        return 0;
    }
    return node->height;
}

int balanceFactor(Node* node) { //node to be analyzed
    if(node == nullptr) {
        return 0;
    }
    return (height(node->left) - height(node->right));
}

void inOrder(Node* node, int times, int a) { //root
    if (node != nullptr) {
        inOrder(node->left, times, a);
        cout << node->number;
        a++;
        if (a != times) {
            cout << ", ";
        }
        inOrder(node->right, times, a);
    }
}


void preOrder(Node* node, int times, int a) { //root
    if(node != nullptr) {
        cout << node->number; 
        a++;
        if(a != times) {
            cout << ", ";
        }
        preOrder(node->left, times, a);
        preOrder(node->right, times, a);
    }
}

void postOrder(Node* node, int times, int a) { //root
    if(node != nullptr) {
        postOrder(node->left, times, a);
        postOrder(node->right, times, a);
        cout << node->number;
        a++;
        if(a != times) {
            cout << ", ";
        }
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

Node* insert(Node*& node, int number, int& times) { //root

    Node* newNode = create(number);

    if(node == nullptr) {
        node = newNode;
    }
    else {
        Node* current = node;
        Node* parent = nullptr;

        while(current != nullptr) {
            parent = current;
            if(number < current->number) {
                current = current->left;
            }
            else if(number > current->number) {
                current = current -> right;
            }
            else {
                return node; //analyze when the number already exists
            }
        }

        if(number < parent->number) {
            parent->left = newNode;
        }
        else if(number > parent->number) {
            parent->right = newNode;
        }
        else {
            return node; //analyze when the number already exists
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        balance(node, number);
    }
    times++;
    return node;
}

Node* minValue(Node* node) {
    Node* current = node;

    while(current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* remove(Node* node, int number, int& times) {
    if (node == nullptr) {
        return node;
    }

    if (number < node->number) {
        node->left = remove(node->left, number, times);
    } else if (number > node->number) {
        node->right = remove(node->right, number, times);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = nullptr;
            if (node->left) {
                temp = node->left;
            } else {
                temp = node->right;
            }

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
                delete temp;
            }
        } else {
            Node* temp = minValue(node->right);
            node->number = temp->number;
            node->right = remove(node->right, temp->number, times);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    balance(node, number);
    times--;
    return node;
}

bool search(Node* node, int number) {
    Node* current = node;
    while(current != nullptr && current->number != number) {
        if(number < node->number) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if(current == nullptr) {
        return false;
    }
    return true;
}


int main() {
    Node* tree = nullptr; //root
    int times = 0;

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
                    insert(tree, num, times);
                }
                else if(command == "REMOVE") {
                    if(search(tree, num)) {
                        remove(tree, num, times);
                    }
                    else {
                        cout << "Valor " << num << " inexistente" << "\n";
                    }
                }
                else {
                    if(search(tree, num)) {
                        cout << "Nivel de " << num << ": " << height(tree) << "\n";
                    }
                    else {
                        cout << "Valor " << num << " inexistente" << "\n";
                    }
                }
            }
            else {
                string type;
                cin >> type;
                if(type == "PREORDEM") {
                    cout << "[";
                    preOrder(tree, times, 0);
                    cout << "]" << "\n";
                }
                else if(type == "EMORDEM") {
                    cout << "[";
                    inOrder(tree, times, 0);
                    cout << "]" << "\n";
                }
                else {
                    cout << "[";
                    postOrder(tree, times, 0);
                    cout << "]" << "\n";
                }
            }
        }
    }
    return 0;
}

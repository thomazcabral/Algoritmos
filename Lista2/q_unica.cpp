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
        cout << node->number << " ";
        /*a++;
        if (a != times) {
            cout << ", ";
        }*/
        inOrder(node->right, times, a);
    }
}


void preOrder(Node* node, int times, int a) { //root
    if(node != nullptr) {
        cout << node->number << " "; 
        /*a++;
        if(a != times) {
            cout << ", ";
        }*/
        preOrder(node->left, times, a);
        preOrder(node->right, times, a);
    }
}

void postOrder(Node* node, int times, int a) { //root
    if(node != nullptr) {
        postOrder(node->left, times, a);
        postOrder(node->right, times, a);
        cout << node->number << " ";
        /*a++;
        if(a != times) {
            cout << ", ";
        }*/
    }
}

Node* rotateLeft(Node*& node) {
    Node* node2 = node->right;
    Node* node3 = node->left;

    node2->left = node;
    node->right = node3;

    node->height = max(height(node->left), height(node->right)) + 1;
    node2->height = max(height(node2->left), height(node2->right)) + 1;

    return node2;
}

Node* rotateRight(Node*& node) {
    Node* node2 = node->left;
    Node* node3 = node->right;

    node2->right = node;
    node->left = node3;

    node->height = max(height(node->left), height(node->right)) + 1;
    node2->height = max(height(node2->left), height(node2->right)) + 1;

    return node2;
}

Node* balance(Node*& node, int number) { 
    node->height = max(height(node->left), height(node->right)) + 1;

    int fb = balanceFactor(node);

    if (fb > 1) {
        if (number < node->left->number) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (fb < -1) {
        if (number > node->right->number) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
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
            times++;
            return node; //analyze when the number already exists
        }
        node->height = max(height(node->left), height(node->right)) + 1;

    times++;
    return balance(node, number);
	}
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
            Node* v = nullptr;
            if (node->left) {
                v = node->left;
            } else {
                v = node->right;
            }

            if (v == nullptr) {
                v = node;
                node = nullptr;
            } else {
                *node = *v;
            }
        } else {
            Node* v = minValue(node->right);
            node->number = v->number;
            node->right = remove(node->right, v->number, times);
        }
    }

    if (node == nullptr) {
        times--;
        return node;
    }
    
    node->height = max(height(node->left), height(node->right)) + 1;
    times--;
    return balance(node, number);
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

int printHeight(Node* node, int num) {
    Node* current = node;
    int height = 0;
    while(current != nullptr && current->number != num) {
        height++;
        if(num < current->number) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if(current == nullptr) {
        return 0;
    }
    return height;
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
                        cout << "Nivel de " << num << ": " << printHeight(tree, num) << "\n";
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

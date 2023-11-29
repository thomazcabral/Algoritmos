#include <iostream>
#include <string>

using namespace std;

struct Node {
    int number;
    Node* left;
    Node* right;
    Node* parent; // Parent pointer
    int height;
};

Node* createNode(int number, Node* parent = nullptr) {
    Node* newNode = new Node;
    newNode->number = number;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = parent;
    newNode->height = 1;
    return newNode;
}

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* search(Node* node, int number) {
    if(node == nullptr || number == node->number) {
        return node;
    }
    if(number < node->number) {
        return search(node->left, number);
    }
    return search(node->right, number);
}

void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

void transplant(Node*& root, Node* u, Node* v) {
    if(u->parent == nullptr) {
        root = v;
    }
    else if(u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }

    if(v != nullptr) {
        v->parent = u->parent;
    }
}

Node* min(Node* node) {
    if(node->left != nullptr) {
        return min(node->left);
    }
    return node;
}

Node* max(Node* node) {
    if(node->right != nullptr) {
        return min(node->right);
    }
    return node;
}

Node* successor(Node* node) {
    if(node->right != nullptr) {
        return min(node->right);
    }
    else {
        Node* y = node->parent;
        while(y != nullptr && node == y->right) {
            node = y;
            y = y->parent;
        }
        return y;
    }
}

void rotateLeft(Node*& root, Node* node) {
    Node* y = node->right;
    node->right = y->left;
    if(y->left != nullptr) {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nullptr) {
        root = y;
    }
    else if(node == node->parent->left) {
        node->parent->left = y;
    }
    else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;

    updateHeight(node);
    updateHeight(y);
}

void rotateRight(Node*& root, Node* node) {
    Node* y = node->left;
    node->left = y->right;
    if(y->right != nullptr) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nullptr) {
        root = y;
    }
    else if(node == node->parent->right) {
        node->parent->right = y;
    }
    else {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;

    updateHeight(node);
    updateHeight(y);
}

void balance(Node*& root, Node* node) {
    while (node != nullptr) {
        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                rotateLeft(root, node->left);
            }
            rotateRight(root, node);
        }
        else if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                rotateRight(root, node->right);
            }
            rotateLeft(root, node);
        }

        node = node->parent; // Move up the tree
    }
}

void insert(Node*& root, int number, int& times) { //root, node with the number(search)
    Node* node = createNode(number);
    Node* x = root;
    Node* y = nullptr;
    while(x != nullptr) {
        y = x;
        if(node->number < x->number) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    node->parent = y;
    if(y == nullptr) {
        root = node;
    }
    else if(node->number < y->number) {
        y->left = node;
    }
    else {
        y->right = node;
    }
    balance(root, node);
    times++;
}

void remove(Node*& root, Node* node, int& times) { //same thing as insert
    if(node->left == nullptr) {
        transplant(root, node, node->right);
        balance(root, node->right);
    }
    else if(node->right == nullptr) {
        transplant(root, node, node->left);
        balance(root, node->left);
    }
    else {
        Node* y = min(node->right);
        if(y != node->right) {
            transplant(root, node, node->right);
            y->right = node->right;
            y->right->parent = y;
            balance(root, y->right);
        }
        transplant(root, node, y);
        y->left = node->left;
        y->left->parent = y;
        balance(root, y->left);
    }
    delete node;
    times--;
}

void inOrder(Node* node, bool& first) { //root
    if (node != nullptr) {
        inOrder(node->left, first);
        if (!first) {
            cout << ",";
        }
        cout << node->number;
        first = false;
        inOrder(node->right, first);
    }
}

void preOrder(Node* node, bool& first) { //root
    if (node != nullptr) {
        if (!first) {
            cout << ",";
        }
        cout << node->number;
        first = false;
        preOrder(node->left, first);
        preOrder(node->right, first);
    }
}

void postOrder(Node* node, bool& first) { //root
    if (node != nullptr) {
        postOrder(node->left, first);
        postOrder(node->right, first);
        if (!first) {
            cout << ",";
        }
        cout << node->number;
        first = false;
    }

}

int displayHeight(Node* root, Node* node) {
    Node* current = root;
    int height = 0;
    while(current->number != node->number) {
        height++;
        if(node->number < current->number) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return height;
}

int main() {
    Node* tree = nullptr;
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
                    Node* node = search(tree, num);
                    if(node == nullptr) {
                        insert(tree, num, times);
                    }
                }
                else if(command == "REMOVE") {
                    Node* node = search(tree, num);
                    if(node != nullptr) {
                        remove(tree, node, times);
                    }
                    else {
                        cout << "Valor " << num << " inexistente" << "\n";
                    }
                }
                else {
                    Node* node = search(tree, num);
                    if(node != nullptr) {
                        cout << "Nivel de " << num << ": " << displayHeight(tree, node) << "\n";
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
                    bool first = true;
                    preOrder(tree, first);
                    cout << "]" << "\n";
                }
                else if(type == "EMORDEM") {
                    cout << "[";
                    bool first = true;
                    inOrder(tree, first);
                    cout << "]" << "\n";
                }
                else {
                    cout << "[";
                    bool first = true;
                    postOrder(tree, first);
                    cout << "]" << "\n";
                }
            }
        }
    }
}

#include <iostream>
#include <string>

using namespace std;

struct HashNode {
    string value;
    HashNode* next;
};

struct HashTable {
    HashNode** table;
    int size;
};

int calculateValue(string word, int size) {
    int sum = 0;
    int i = 1;
    for (char c : word) {
        sum += (int(c) * i);
        i++;
    }
    return ((sum * 17) % size);
}

HashNode* createNode(HashTable* hashtable, string entry) {
    HashNode* newNode = new HashNode;
    newNode->value = entry;
    newNode->next = nullptr;
    return newNode;
} 

void insert(HashTable*& hashtable, string entry) {
    int index = calculateValue(entry, hashtable->size);
    HashNode* node = createNode(hashtable, entry);

    node->next = hashtable->table[index];
    hashtable->table[index] = node;
}

string search(HashTable* hashtable, string word) { 
    int index = calculateValue(word, hashtable->size);
    if (hashtable->table[index] == nullptr) {
        return "404 - NOT FOUND";
    } else {
        HashNode* current = hashtable->table[index];
        int i = 1;
        while (current->value != word && current->value != "") {
            current = current->next;
            i++;
        } 
        if (current->value == "") {
            return "404 - NOT FOUND";
        } else {
            return to_string(index) + " " + to_string(i);
        }
    }
}

string del(HashTable*& hashtable, string word) {
    int index = calculateValue(word, hashtable->size);
    if (hashtable->table[index] == nullptr) {
        return "";
    } else {
        HashNode* current = hashtable->table[index];
        HashNode* prev = nullptr;

        while (current != nullptr && current->value != word) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                hashtable->table[index] = current->next;
            }

            string result = "DELETADO";
            delete current;
            return result;
        } else {
            return "";
        }
    }
}

int main() {
    int size;
    cin >> size;

    HashTable* hashTable = new HashTable;
    hashTable->size = size;
    hashTable->table = new HashNode*[size];

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = nullptr;
    }

    int numInsert;
    cin >> numInsert;

    for (int i = 0; i < numInsert; i++) {
        string dontCare;
        cin >> dontCare;

        string word;
        cin >> word;

        insert(hashTable, word);
    }

    int commands;
    cin >> commands;

    for (int i = 0; i < commands; i++) {
        string command;
        cin >> command;

        string name;
        cin >> name;

        if (command == "GET") {
            cout << search(hashTable, name) << "\n";
        } else if (command == "POST") {
            insert(hashTable, name);
        } else if (command == "DELETE") {
            string result = del(hashTable, name);
            if (!result.empty()) {
                cout << result << "\n";
            }
        }
    }

    for (int i = 0; i < size; i++) {
        HashNode* current = hashTable->table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    delete[] hashTable->table;
    delete hashTable;

    return 0;
}

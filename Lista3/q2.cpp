#include <iostream>
#include <string>

using namespace std;

struct Person { //hashNode
    string name;
    int registration;
    int priority;
    Person* next;
}

struct Theater { //hashTable
    Person** table;
    int lines;
    int seatsPerLine;
}

struct Queue {
    Person* head;
    Queue* next;
}

Queue* createQueue(Person* person) {
    Node* newNode = new Node;
    newNode->person = person;
    newNode->next = nullptr;

    return newNode;
}

void insertQueue(Queue* queue, Person* person) {
    Queue* current = queue;
    while(current->next != nullptr) {
        current = current->next;
    }
    current->next = createQueue(person);
}

Person* createPerson(string name, int registration, int priority) {
    Person* newPerson = new Person;
    newPerson->name = name;
    newPerson->registration = registration;
    newPerson->priority = priority;
    newPerson->next = nullptr;

    return newPerson;
}

void insertTheater(Theater* theater, string name, int registration, int priority, Queue* queue) {
    Person* person = createPerson(name, registration, priority);

    int initialIndex = 0;
    int worstPriority = 100000000; //big value
    int worstIndex = 0;
    bool seated = false;

    while(initialIndex < theater->lines and !seated) {
        int seat = 0;
        Person* current = theater->table[initialIndex];
        while(seat < theater->seatsPerLine and !seated) {
            if(current == nullptr) {
                person->next = theater->table[initialIndex];
                theater->table[initialIndex] = person;
                seated = true;
                cout << person->name << '(' << person->registration << ')' << "foi alocado(a) na fileira " << initialIndex + 1 << "\n";
            }
            else {
                if(current->priority < worstPriority) { // if there are more than 1 person with the worst priority, issues will occur
                    worstPriority = current->priority;
                    worstIndex = initialIndex;
                }
                current = current->next;
            }
            seat++;
        }
        initialIndex++;
    }
    
    if(!seated) {
        Person* current = theater->table[worstIndex];
        while(current->next->priority != worstPriority) {
            current = current->next;
        }
        if(person->priority < current->next->priority) {
            cout << person->name << (person->registration) << "nao foi alocado(a) em nenhuma fileira" << "\n";
            insertQueue(queue, person);
        }
        else if(person->priority > current->next->priority) {
            person->next = current->next->next;
            current->next = person;
        }
        else {
            if(person->registration < current->next->registration) {
                person->next = current->next->next;
                current->next = person;
            }
            else {
                cout << person->name << '(' << person->registration << ')' << "nao foi alocado(a) em nenhuma fileira" << "\n";
                insertQueue(queue, person); 
            }
        }
    }
}

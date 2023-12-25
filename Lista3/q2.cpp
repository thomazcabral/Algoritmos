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

Person* createPerson(string name, int registration, int priority) {
    Person* newPerson = new Person;
    newPerson->name = name;
    newPerson->registration = registration;
    newPerson->priority = priority;
    newPerson->next = nullptr;

    return newPerson;
}

void insert(Theater* theater, string name, int registration, int priority) {
    Person* person = createPerson(name, registration, priority);

    int initialIndex = 0;
    bool seated = false;
    while(initialIndex < theater->lines and !seated) {
        int seat = 0;
        Person* current = theater->table[initialIndex];
        while(seat < theater->seatsPerLine and !seated) {
            
        } 
    }
}

#include <iostream>
#include <string>

using namespace std;

struct Person { //hashNode
    string name;
    int registration;
    int priority;
    Person* next;
};

struct Theater { //hashTable
    Person** table;
    int lines;
    int seatsPerLine;
};

struct Queue {
    Person* head;
    Queue* next;
};

Queue* createQueue(Person* person) {
    Queue* newQueue = new Queue;
    newQueue->head = person;
    newQueue->next = nullptr;

    return newQueue;
}

void insertQueue(Queue** queue, Person* person) {
    Queue* newQueue = createQueue(person);
    if (*queue == nullptr) {
        *queue = newQueue;
    } else {
        Queue* current = *queue;
        while(current->next != nullptr) {
            current = current->next;
        }
        current->next = newQueue;
    }
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

    while(initialIndex < theater->lines && !seated) {
        int seat = 0;
        Person* current = theater->table[initialIndex];
        while(seat < theater->seatsPerLine && !seated) {
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

void removeTheater(Theater* theater, int registration, Queue* queue) {
    int initialIndex = 0;
    bool removed = false;

    while(initialIndex < theater->lines && !removed) {
        int seat = 0;
        Person* current = theater->table[initialIndex];
        while(seat < theater->seatsPerLine && !removed) {
            if(current->registration == registration && seat == 0) {
                theater->table[initialIndex] = current->next;
                cout << "Removido(a)" << "\n";
            }
            else {
                if(current->next->registration == registration) {
                    current->next = current->next->next;
                    cout << "Removido(a)" << "\n";
                }
                else {
                    current = current->next;
                }
            }
            seat++;
        }
        initialIndex++;
    }
    
    if(!removed) {
        Person* current = queue->head;
        int i = 0;
        if(current->registration == registration && i == 0) {
            queue->head = current->next;
            cout << "Removido(a)" << "\n";
        }
        else {
            if(current->next->registration == registration) {
                current->next = current->next->next;
                cout << "Removido(a)" << "\n";
            }
            else {
                current = current->next;
            }
        }
    }

    if(!removed) {
        cout << "Inexistente" << "\n";
    }
}

void situationTheater(Theater* theater, int registration, Queue* queue) {
    int initialIndex = 0;
    bool removed = false;

    while(initialIndex < theater->lines && !removed) {
        int seat = 0;
        Person* current = theater->table[initialIndex];
        while(seat < theater->seatsPerLine && !removed) {
            if(current->registration == registration && seat == 0) {
                cout << "Sentado(a) na fileira " << initialIndex + 1 << "\n";
            }
            else {
                if(current->next->registration == registration) {
                    cout << "Sentado(a) na fileira " << initialIndex + 1 << "\n";
                }
                else {
                    current = current->next;
                }
            }
            seat++;
        }
        initialIndex++;
    }
    
    if(!removed) {
        Person* current = queue->head;
        int i = 0;
        if(current->registration == registration && i == 0) {
            cout << "Sem assento" << "\n";
        }
        else {
            if(current->next->registration == registration) {
                cout << "Sem assento" << "\n";
            }
            else {
                current = current->next;
            }
        }
    }

    if(!removed) {
        cout << "Inexistente" << "\n";
    }
}

int main() {
    int lines, seatsPerLine;
    cin >> lines >> seatsPerLine;

    Theater* theater = new Theater;
    theater->lines = lines;
    theater->seatsPerLine = seatsPerLine;
    theater->table = new Person*[lines];

    for(int i = 0; i < lines; i++) {
        theater->table[i] = nullptr;
    }

    Queue* queue = nullptr;

    int numCommands;
    cin >> numCommands;

    int registrationNumber = 1;

    for(int i = 0; i < numCommands; i++) {
        string command;
        cin >> command;

        if(command == "CAD") {
            string name;
            cin >> name;

            int priority;
            cin >> priority;

            insertTheater(theater, name, registrationNumber, priority, queue);
        }
        else if(command == "REM") {
            string name;
            cin >> name;

            int registration;
            cin >> registration;

            removeTheater(theater, registration, queue);
        }
        else if(command == "VER") {
            string name;
            cin >> name;

            int registration;
            cin >> registration;

            situationTheater(theater, registration, queue);
        }
    }
    return 0;
}

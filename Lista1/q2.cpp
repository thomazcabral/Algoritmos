#include <iostream>
#include <string>

using namespace std;

typedef struct Car {
    int size;
    struct Car* next; // pointer
} Car;

Car* create(int size) {
    Car* newCar = new Car;
    newCar->size = size;
    newCar->next = nullptr;

    return newCar;
}

void insert(int size, Car*& group) {
    Car* newCar = create(size);

    if (group == nullptr) {
        group = newCar;
    } 
    else {
        Car* currentCar = group;
        while (currentCar->next != nullptr) {
            currentCar = currentCar->next;
        }
        currentCar->next = newCar; // link the car to the end
    }
}

void insertBoat(int sizeBoat, Car*& carList) {
    Car* current = carList;
    int size = sizeBoat;

    while (current != nullptr && current->size <= size) {
        size -= current->size;
        Car* temp = current;
        current = current->next;
        delete temp; // free memory
    }

    carList = current; // update carList
}

int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        int sizeBoat, numCars, travels = 0;
        cin >> sizeBoat >> numCars;
        sizeBoat *= 100; // m to cm
        Car* left = nullptr;
        Car* right = nullptr;
        char carSituation = 'l'; // left or right

        for (int j = 0; j < numCars; j++) {
            int sizeCar;
            string sideCar;
            cin >> sizeCar >> sideCar;

            if (sideCar == "esquerdo") {
                insert(sizeCar, left);
            } else {
                insert(sizeCar, right);
            }
        }

        while (left != nullptr || right != nullptr) {
            if (carSituation == 'l') {
                if (left != nullptr) {
                    insertBoat(sizeBoat, left);
                }
                travels++;
                carSituation = 'r';
            } else {
                if (right != nullptr) {
                    insertBoat(sizeBoat, right);
                }
                travels++;
                carSituation = 'l';
            }
        }

        cout << "Caso " << i + 1 << ": " << travels << endl;
    }

    return 0;
}

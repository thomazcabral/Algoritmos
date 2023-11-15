#include <iostream>
#include <string>
using namespace std;

int main() {
    int esquerda = 0;
    int direita = 0;

    string entrada;
    getline(cin, entrada);

    for (char c : entrada) {
        if (c == '{') {
            esquerda++;
        }
        if (c == '}') {
            direita++;
        }
        if (direita > esquerda) {
            break;
        }
    }

    if (esquerda == direita) {
        cout << 'S' << "\n";
    }
    else {
        cout << 'N' << "\n";
    }
}

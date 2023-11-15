#include <iostream>
#include <string>
using namespace std;

int main() {
    int tamanhoMaior = 0;
    string listaMaior = "[]";
    int j = 0;

    while (1) {
        int i = 0;
        int tamanhoAtual = 0;
        string listaAtual;
        getline(cin, listaAtual);

        if (listaAtual == "") {
            break;
        }

        if (listaAtual == "[]") {
            tamanhoAtual = 0;
        }
        else {
            if (listaAtual[2] == ']') {
                i = 1;
                tamanhoAtual = 1;
            }
            else {
                tamanhoAtual = 1;
                for (char c : listaAtual) {
                    if (c == ',') {
                        tamanhoAtual++; 
                    }
                }
            }
        }

        if (tamanhoAtual > tamanhoMaior) {
            tamanhoMaior = tamanhoAtual;
            listaMaior = listaAtual;
        }
        j++;
    }

    if (j != 0){
        cout << listaMaior << "\n";
    }
    else{
        cout << "" << "\n";
    }

    return 0;
}

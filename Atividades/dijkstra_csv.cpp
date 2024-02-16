#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void add_heap(vector<int>& elementos) {
    if (elementos.empty()) {
        return;
    }

    int tamanho = elementos.size();
    int indice = tamanho - 1;
    int valor = move(elementos[indice]);

    int pai = (indice - 1) / 2;

    while (indice > 0 && elementos[pai] < valor) {
        elementos[indice] = move(elementos[pai]);
        indice = pai;
        pai = (indice - 1) / 2;
    }

    elementos[indice] = move(valor);
}

void pop_heap(vector<int>& elementos) {
    if (elementos.empty()) return;

    int tamanho = elementos.size();
    swap(elementos[0], elementos[tamanho - 1]);

    int indice = 0;
    int filho = 2 * indice + 1;
    int valor = move(elementos[indice]);

    while (filho < tamanho - 1) {
        if (elementos[filho] < elementos[filho + 1]) {
            filho++;
        }

        if (valor < elementos[filho]) {
            elementos[indice] = move(elementos[filho]);
            indice = filho;
            filho = 2 * indice + 1;
        } else {
            break;
        }
    }

    elementos[indice] = move(valor);
}

const int MAX_STRINGS = 3606806; // Maximum number of strings in the array
const int QUANTIDADE_VERTICES = 708;

// Custom priority queue implementation
class PriorityQueue {
private:
    vector<int> elementos;

public:
    bool empty() const {
        return elementos.empty();
    }

    void push(const int& elemento) {
        elementos.push_back(elemento);
        add_heap(elementos);
    }

    int pop() {
        pop_heap(elementos);
        int topo = elementos.back();
        elementos.pop_back();
        return topo;
    }
};

class MyClass {
private:
    string aeroporto_origem[MAX_STRINGS];
    string aeroporto_destino[MAX_STRINGS];
    int distancia[MAX_STRINGS];
    int tamanho;

public:
    MyClass() {
        this->tamanho = 0;
    }

    bool permitirAdd(string inicio, string fim) {
        for (int i = this->tamanho; i > this->tamanho/2; i--) {
            if (aeroporto_origem[i] == inicio) {
                if (aeroporto_destino[i] == fim) {
                    return false;
                }
            }
        }
        return true;
    }

    void addString(string inicio, string fim, int dist) {
        if (this->tamanho == 0 || ((aeroporto_origem[this->tamanho-1] != inicio || aeroporto_destino[this->tamanho-1] != fim) && this->permitirAdd(inicio, fim))) {
            aeroporto_origem[this->tamanho] = inicio;
            aeroporto_destino[this->tamanho] = fim;
            distancia[this->tamanho] = dist;
            this->tamanho++;
        }
    }

    void displayStrings() {
        for (int i = 0; i < this->tamanho; i++) {
            cout << aeroporto_origem[i] << " " << aeroporto_destino[i] << " " << distancia[i] << "\n";
        }
    }

    int indice(string aeroporto, string* aeroportos_vertices) {
        for (int i = 0; i < QUANTIDADE_VERTICES; i++) {
            if (aeroportos_vertices[i] == aeroporto) {
                return i;
            }
        }
        return -1;
    }

    int proximo_indice(int* menores_distancias, int* vertices_passados) {
        int menor = -1;
        int vertice = -1;
        for (int i = 0; i < QUANTIDADE_VERTICES; i++) {
            if (vertices_passados[i] == -1 && (menores_distancias[i] < menor || menor == -1)) {
                menor = menores_distancias[i];
                vertice = i;
            }
        }
        return vertice;
    }

    int buscar_distancia(string entrada, string saida) {
        for (int i = 0; i < this->tamanho; i++) {
            if (aeroporto_origem[i] == entrada && aeroporto_destino[i] == saida) {
                return distancia[i];
            }
        }
        
        int vertices_passados[QUANTIDADE_VERTICES];
        int menores_distancias[QUANTIDADE_VERTICES];
        string aeroportos_vertices[QUANTIDADE_VERTICES];
        int contador = 0;
        int indice_inicio, indice_fim;
        for (int i = 0; i < this->tamanho; i++) {
            if (indice(aeroporto_destino[i], aeroportos_vertices)) {
                vertices_passados[contador] = -1;
                menores_distancias[contador] = -1;
                aeroportos_vertices[contador] = aeroporto_destino[i];
                if (aeroporto_destino[i] == entrada) {
                    indice_inicio = contador;
                } else if (aeroporto_destino[i] == saida) {
                    indice_fim = contador;
                }
                contador++;
                if (contador == QUANTIDADE_VERTICES) {
                    break;
                }
            }
        }
        
        vertices_passados[indice_inicio] = 0;
        menores_distancias[indice_inicio] = 0;
        contador = 0;
        int indice_atual = indice_inicio;
        int k_chegada;

        PriorityQueue fila_prioridade;

        fila_prioridade.push(0);

        while (!fila_prioridade.empty()) {
            int current = fila_prioridade.pop();

            for (int i = 0; i < this->tamanho; i++) {
                if (aeroporto_origem[i] == aeroportos_vertices[current]) {
                    k_chegada = indice(aeroporto_destino[i], aeroportos_vertices);
                    if (menores_distancias[k_chegada] == -1 || (menores_distancias[k_chegada] > this->distancia[i] + menores_distancias[current])) {
                        menores_distancias[k_chegada] = this->distancia[i] + menores_distancias[current];
                        fila_prioridade.push(menores_distancias[k_chegada]);
                    }
                }
            }
        }

        return menores_distancias[indice_fim];
    }
};

int main() {
    ifstream file;
    file.open("test.csv");
    string line;
    getline(file, line);

    MyClass *myObject = new MyClass();

    int contador;
    int inicio, fim;
    while (getline(file, line)) {
        contador = 0;
        inicio = -1;
        fim = -1;
        for (int i = 0; i < (int) line.size(); i++) {
            if (line[i] == ',') {
                contador++;
                if (contador == 9 && inicio == -1) {
                    inicio = i;
                } else if (contador == 10 && fim == -1) {
                    fim = i;
                    break;
                }
            }
        }

        if (line.substr(inicio+1, fim-inicio-1) != "0") {
            myObject->addString(line.substr(1, 3), line.substr(7, 3), stoi(line.substr(inicio+1, fim-inicio-1)));
        }
    }
    file.close();
    
    string entrada;
    string saida;
    cin >> entrada >> saida;
    if (entrada == saida) {
        cout << 0;
    } else {
        int resp = myObject->buscar_distancia(entrada, saida);
        cout << resp;
    }

    return 0;
}

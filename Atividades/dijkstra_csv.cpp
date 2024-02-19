#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAX_INT = 2147483647;  

const int QUANTIDADE_VERTICES = 1391;

class PriorityQueue {
private:
    vector<pair<int, int>> pq;

    void push_heap() {
        int idx = pq.size() - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (pq[parent].first > pq[idx].first) {
                swap(pq[parent], pq[idx]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void pop_heap() {
        int last = pq.size() - 1;
        swap(pq[0], pq[last]);
        pq.pop_back();

        int idx = 0;
        int leftChild, rightChild, minChild;
        while (true) {
            leftChild = 2 * idx + 1;
            rightChild = 2 * idx + 2;
            minChild = idx;

            if (leftChild < pq.size() && pq[leftChild].first < pq[minChild].first) {
                minChild = leftChild;
            }
            if (rightChild < pq.size() && pq[rightChild].first < pq[minChild].first) {
                minChild = rightChild;
            }

            if (minChild != idx) {
                swap(pq[idx], pq[minChild]);
                idx = minChild;
            } else {
                break;
            }
        }
    }

public:
    void push(int distance, int vertex) {
        pq.push_back(make_pair(distance, vertex));
        push_heap();
    }

    pair<int, int> top() {
        return pq[0];
    }

    void pop() {
        pop_heap();
    }

    bool empty() {
        return pq.empty();
    }
};

class Graph {
private:
    vector<string> aeroporto_origem;
    vector<string> aeroporto_destino;
    vector<int> distancia;
    int tamanho;

public:
    Graph(vector<string> origem, vector<string> destino, vector<int> dist) {
        this->aeroporto_origem = origem;
        this->aeroporto_destino = destino;
        this->distancia = dist;
        this->tamanho = origem.size();
    }

    int indice(const string& aeroporto, const vector<string>& aeroportos_vertices) {
        for (int i = 0; i < aeroportos_vertices.size(); ++i) {
            if (aeroporto == aeroportos_vertices[i]) {
                return i;
            }
        }
        return -1;
    }

    int buscar_distancia(const string& entrada, const string& saida) {
        vector<string> aeroportos_vertices(QUANTIDADE_VERTICES);
        vector<int> vertices_passados(QUANTIDADE_VERTICES, -1);
        vector<int> menores_distancias(QUANTIDADE_VERTICES, MAX_INT);  
        int contador = 0;
        int indice_inicio = -1, indice_fim = -1;

        for (int i = 0; i < this->tamanho; i++) {
            if (indice(aeroporto_origem[i], aeroportos_vertices) == -1) {
                vertices_passados[contador] = -1;
                menores_distancias[contador] = MAX_INT; 
                aeroportos_vertices[contador] = aeroporto_origem[i];
                if (aeroporto_origem[i] == entrada) {
                    indice_inicio = contador;
                } else if (aeroporto_origem[i] == saida) {
                    indice_fim = contador;
                }
                contador++;
            }
            if (indice(aeroporto_destino[i], aeroportos_vertices) == -1) {
                vertices_passados[contador] = -1;
                menores_distancias[contador] = MAX_INT;
                aeroportos_vertices[contador] = aeroporto_destino[i];
                if (aeroporto_destino[i] == entrada) {
                    indice_inicio = contador;
                } else if (aeroporto_destino[i] == saida) {
                    indice_fim = contador;
                }
                contador++;
            }
            if (contador == QUANTIDADE_VERTICES) {
                break;
            }
        }

        if (indice_inicio == -1 || indice_fim == -1) {
            return -1; 
        }

        vertices_passados[indice_inicio] = 0;
        menores_distancias[indice_inicio] = 0;
        contador = 0;
        int indice_atual = indice_inicio;
        int k_chegada;

        PriorityQueue fila_prioridade;

        fila_prioridade.push(0, indice_inicio);

        while (!fila_prioridade.empty()) {
            pair<int, int> current = fila_prioridade.top();
            fila_prioridade.pop();
            int current_distance = current.first;
            int current_vertex = current.second;

            for (int i = 0; i < this->tamanho; i++) {
                if (aeroporto_origem[i] == aeroportos_vertices[current_vertex]) {
                    k_chegada = indice(aeroporto_destino[i], aeroportos_vertices);
                    if (menores_distancias[k_chegada] == MAX_INT || (menores_distancias[k_chegada] > this->distancia[i] + menores_distancias[current_vertex])) {
                        menores_distancias[k_chegada] = this->distancia[i] + menores_distancias[current_vertex];
                        fila_prioridade.push(menores_distancias[k_chegada], k_chegada);
                    }
                }
            }
        }

        return menores_distancias[indice_fim];
    }
};

int main() {
    ifstream file;
    file.open("Airports2.csv");
    string line;
    getline(file, line);

    vector<string> origem;
    vector<string> destino;
    vector<int> distancias;

    int contador;
    int inicio, fim;
    while (getline(file, line)) {
        contador = 0;
        inicio = -1;
        fim = -1;
        for (int i = 0; i < static_cast<int>(line.size()); i++) {
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
            origem.push_back(line.substr(1, 3));
            destino.push_back(line.substr(7, 3));
            distancias.push_back(stoi(line.substr(inicio+1, fim-inicio-1)));
        }
    }
    file.close();
    
    string entrada;
    string saida;
    cin >> entrada >> saida;

    Graph graph(origem, destino, distancias);
    
    if (entrada == saida) {
        cout << 0;
    } else {
        int resp = graph.buscar_distancia(entrada, saida);
        if (resp == -1) {
            cout << "Sem rotas disponiveis.";
        } else {
        cout << resp;
        }
    }

    return 0;
}

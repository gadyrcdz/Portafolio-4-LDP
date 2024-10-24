#include <iostream>

class Nodo {
public:
    int valor;
    Nodo* siguiente;
    
    Nodo(int valor){
        this->valor = valor;
        this->siguiente = nullptr;
    }
};

class ListaEnlazada {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaEnlazada() {
        cabeza = nullptr;
        cola = nullptr;
    }

    void agregar(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (!cabeza) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
    }

    void idenTendencias() {
        Nodo* actual = cabeza;
        Nodo* inicioTendencia = nullptr;
        bool tendenciaAlta = false;
        bool tendenciaBaja = false;

        while (actual && actual->siguiente && actual->siguiente->siguiente) {
            //Tendencia Alta
            if (actual->valor < actual->siguiente->valor && actual->siguiente->valor < actual->siguiente->siguiente->valor) {
                if (!tendenciaAlta) {
                    if (inicioTendencia) { 
                        std::cout << "]\n"; 
                        }
                    std::cout << "[";
                    inicioTendencia = actual;
                    tendenciaAlta = true;
                    tendenciaBaja = false;
                }
                std::cout << actual->valor << ", ";
            } 
            //Tendencia Baja
            else if (actual->valor > actual->siguiente->valor && actual->siguiente->valor > actual->siguiente->siguiente->valor) {
                if (!tendenciaBaja) {
                    if (inicioTendencia) { 
                        std::cout << "]\n"; 
                        }
                    std::cout << "[";
                    inicioTendencia = actual;
                    tendenciaBaja = true;
                    tendenciaAlta = false;
                }
                std::cout << actual->valor << ", ";
            } 
            else {
                if (inicioTendencia && tendenciaAlta) {
                    std::cout << actual->valor << "]\n";
                } 
                else if (inicioTendencia && tendenciaBaja) {
                    std::cout << actual->valor << "]\n";
                }
                inicioTendencia = nullptr;
                tendenciaAlta = false;
                tendenciaBaja = false;
            }
            actual = actual->siguiente;
        }
        if (inicioTendencia) {
            std::cout << actual->valor << "]\n";
        }
    }
};

int main() {
    ListaEnlazada lista;
    int valores[] = {2, 4, 6, 8, 7, 5, 6, 3, 10, 12, 14};
    int tam = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < tam; ++i) {
        lista.agregar(valores[i]);
    }

    lista.idenTendencias();

    return 0;
}

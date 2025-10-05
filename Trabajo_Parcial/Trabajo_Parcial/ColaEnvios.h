#pragma once
#include "Envio.h"

template <typename T>
class ColaEnvios {
private:
    queue<T*> pendientes;
public:
    void encolar(T* e) {
        pendientes.push(e);
        cout << "Envio " << e->getId() << " agregado a la cola de pendientes.\n";
    }

    T* desencolar() {
        if (pendientes.empty()) {
            cout << "No hay envios pendientes.\n";
            return nullptr;
        }

        T* e = pendientes.front();
        pendientes.pop();
        e->actualizarEstado("En transito");
        cout << "Procesando envio " << e->getId() << " hacia " << e->getDestino() << endl;
        e->actualizarEstado("En transito");
        return e;
    }

    void mostrarCola() {
        if (pendientes.empty()) {
            cout << "No hay elementos en la cola.\n";
            return;
        }

        queue<T*> copia = pendientes;

        cout << "\n=== ELEMENTOS EN LA COLA ===\n";

        auto imprimir = [](T* envio) {
            cout << "Envio " << envio->getId()
                << " -> Destino: " << envio->getDestino()
                << " (Estado: " << envio->getEstado() << ")\n";
            };

        while (!copia.empty()) {
            imprimir(copia.front());
            copia.pop();
        }
    }

    bool estaVacia() const {
        return pendientes.empty();
    }
};

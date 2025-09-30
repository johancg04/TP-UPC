#pragma once
#pragma once
#include "Envio.h"
#include <queue>

class ColaEnvios {
private:
    queue<Envio*> pendientes;
public:
    void encolar(Envio* e) {
        pendientes.push(e);
        cout << "Envio " << e->getId() << " agregado a la cola de pendientes.\n";
    }

    void desencolar() {
        if (!pendientes.empty()) {
            Envio* e = pendientes.front();
            pendientes.pop();
            cout << "Procesando envio " << e->getId() << " hacia " << e->getDestino() << endl;
            e->actualizarEstado("En transito");
        }
        else {
            cout << "No hay envios pendientes.\n";
        }
    }

    void mostrarCola() {
        if (pendientes.empty()) {
            cout << "No hay envios en la cola.\n";
            return;
        }

        queue<Envio*> copia = pendientes;
        cout << "=== COLA DE ENVIOS PENDIENTES ===\n";
        while (!copia.empty()) {
            Envio* e = copia.front();
            cout << "Envio " << e->getId() << " -> " << e->getDestino()
                << " (Estado: " << e->getEstado() << ")\n";
            copia.pop();
        }
    }
};

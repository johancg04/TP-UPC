#pragma once
#include "Envio.h"

template <typename T = Envio>
class Nodo
{
private:
    T* envio;
    Nodo<T>* siguiente;

public:
    Nodo(T* e) {
        envio = e;
        siguiente = nullptr;
    }

    ~Nodo() {}

    T* getEnvio() { return envio; }
    void setEnvio(T* e) { envio = e; }

    Nodo<T>* getSiguiente() { return siguiente; }
    void setSiguiente(Nodo<T>* nodo) { siguiente = nodo; }
};
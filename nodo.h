#ifndef NODO_H
#define NODO_H

#include <vector>
#include <string>
#include <stdexcept>

template <class T>
class Nodo
{
private:
    T dato;
    Nodo<T> *siguiente;
    

public:
    T getDato()
    {
        return dato;
    }

    void setDato(T d)
    {
        dato = d;
    }

    Nodo<T> *getSiguiente()
    {
        return siguiente;
    }

    void setSiguiente(Nodo<T> *siguiente)
    {
        this->siguiente = siguiente;
    }

    
};

#endif // NODO_H
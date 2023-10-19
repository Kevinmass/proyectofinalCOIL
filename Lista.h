#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_
#include "nodo.h"


/**
 * Clase que implementa una Lista Enlasada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T>
class Lista
{
private:
  Nodo<T> *inicio;


public:
  Lista();

  Lista(const Lista<T> &li);

  ~Lista();

  bool esVacia();

  int getTamanio();

  void insertar(int pos, T dato);

  void insertarPrimero(T dato);

  void insertarUltimo(T dato);

  void remover(int pos);

  T getDato(int pos);

  void reemplazar(int pos, T dato);

  void vaciar();

  void print();

  void invertir();

  void UnirListas(Lista<T> &li1, Lista<T> &li2);

  void InsertAfter2(int oldvalue, int n, int newValue);

  void MoverAprimero(T dato);
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T>
Lista<T>::Lista() { inicio = nullptr; }

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T>
Lista<T>::Lista(const Lista<T> &li) { inicio = li.inicio; }

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T>
Lista<T>::~Lista() { vaciar(); }

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T>
bool Lista<T>::esVacia() { return inicio == nullptr; }

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T>
int Lista<T>::getTamanio()
{
  Nodo<T> *aux = inicio;
  int size = 0;

  while (aux != nullptr)
  {
    aux = aux->getSiguiente();
    size++;
  }

  return size;
}

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T>
void Lista<T>::insertar(int pos, T dato)
{
  int posActual = 0;
  Nodo<T> *aux = inicio, *nuevo;
  nuevo = new Nodo<T>;
  nuevo->setDato(dato);

  if (pos == 0)
  {
    nuevo->setSiguiente(inicio);
    inicio = nuevo;
    return;
  }

  while (aux != nullptr && posActual < pos - 1)
  {
    aux = aux->getSiguiente();
    posActual++;
  }

  if (aux == nullptr)
  {
    throw 404;
    return;
  }

  nuevo->setSiguiente(aux->getSiguiente());
  aux->setSiguiente(nuevo);
}

/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarPrimero(T dato) { insertar(0, dato); }

/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarUltimo(T dato)
{
  Nodo<T> *aux = inicio, *nuevo;
  nuevo = new Nodo<T>;
  nuevo->setDato(dato);

  if (aux == nullptr)
  {
    nuevo->setSiguiente(inicio);
    inicio = nuevo;
    return;
  }

  while (aux->getSiguiente() != nullptr)
  {
    aux = aux->getSiguiente();
  }

  nuevo->setSiguiente(aux->getSiguiente());
  aux->setSiguiente(nuevo);
}

/**
 * Elimina el nodo en la posicion 'pos' de la lista enlasada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T>
void Lista<T>::remover(int pos)
{
  Nodo<T> *aux = inicio, *aBorrar;
  int posActual = 0;

  if (pos == 0)
  {
    inicio = inicio->getSiguiente();
    delete aux;
    return;
  }

  while (aux != nullptr && posActual < pos - 1)
  {
    aux = aux->getSiguiente();
    posActual++;
  }

  if (aux == nullptr)
  {
    throw 404;
    return;
  }

  aBorrar = aux->getSiguiente();
  aux->setSiguiente(aBorrar->getSiguiente());

  delete aBorrar;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T>
T Lista<T>::getDato(int pos)
{
  Nodo<T> *aux = inicio;
  int posActual = 0;

  while (aux != nullptr && posActual < pos)
  {
    aux = aux->getSiguiente();
    posActual++;
  }

  if (aux == nullptr)
  {
    throw 404;
  }

  return aux->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T>
void Lista<T>::reemplazar(int pos, T dato)
{
  Nodo<T> *aux = inicio;
  int posActual = 0;

  while (aux != nullptr && posActual < pos)
  {
    aux = aux->getSiguiente();
    posActual++;
  }

  if (aux == nullptr)
  {
    throw 404;
  }

  aux->setDato(dato);
}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T>
void Lista<T>::vaciar()
{
  Nodo<T> *aux = inicio, *aBorrar;

  while (aux != nullptr)
  {
    aBorrar = aux;
    aux = aux->getSiguiente();
    delete aBorrar;
  }

  inicio = nullptr;
}

template <class T>
void Lista<T>::print()
{
  Nodo<T> *aux = inicio;

  while (aux != nullptr)
  {
    std::cout << aux->getDato() << "->";
    aux = aux->getSiguiente();
  }
  std::cout << "NULL" << std::endl;
}

template <class T>
void Lista<T>::invertir()
{
  Nodo<T> *aux = inicio, *siguiente = nullptr, *anterior = nullptr;

  while (aux != nullptr)
  {
    siguiente = aux->getSiguiente();
    aux->setSiguiente(anterior);
    anterior = aux;
    aux = siguiente;
  }

  inicio = anterior;
}

template <class T>
void Lista<T>::UnirListas(Lista<T> &Li1, Lista<T> &Li2)
{
  Nodo<T> *aux = Li1.inicio, *aux2 = Li2.inicio;
  int pos = 0;

  while (aux != nullptr)
  {
    insertar(pos, aux->getDato());
    aux = aux->getSiguiente();
    pos++;
  }

  while (aux2 != nullptr)
  {
    insertar(pos, aux2->getDato());
    aux2 = aux2->getSiguiente();
    pos++;
  }
}

// insertAfter2(int oldValue, int n, int newValue) que inserte un nodo
// con el valor newValue después de la enésima ocurrencia de oldValue.

template <class T>
void Lista<T>::InsertAfter2(int oldvalue, int n, int newValue)
{
  Nodo<T> *aux = inicio;
  int cont = 0;
  while (aux->getSiguiente() != nullptr)
  {
    if (aux->getDato() == oldvalue)
    {
      cont++;
    }
    if (cont == n)
    {
      Nodo<int> *nuevo = new Nodo<int>();
      nuevo->setDato(newValue);
      nuevo->setSiguiente(aux->getSiguiente());
      aux->setSiguiente(nuevo);
      break;
    }
    aux = aux->getSiguiente();
  }
}

template <class T>

void Lista<T>::MoverAprimero(T dato)
{
  Nodo<T> *aux = inicio, *anterior = nullptr;
  while (aux->getDato() != dato)
  {
    anterior = aux;
    aux = aux->getSiguiente();
  }
  if (anterior != nullptr)
  {
    anterior->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(inicio);
    inicio = aux;
  }
}

//-------------------------MODIFICACIONES-------------------------//





#endif // U02_LISTAS_LISTA_LISTA_H_

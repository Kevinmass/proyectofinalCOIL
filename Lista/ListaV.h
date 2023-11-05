#include <vector>
#include <string>
#include <stdexcept>
#include <list>

/**
 * Clase que implementa una Lista enlasada generica con nodos de tipo vector
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */

template <class T>
class ListaV
{
private:
    /**
     * Struct que implementa un nodo de la lista enlazada -> Diferente forma de implementar un nodo
     * @tparam U cualquier tipo de dato
     */
    template <class U>
    struct NodoV
    {
        U dato;
        NodoV *siguiente;
        NodoV(const U &val) : dato(val), siguiente(nullptr) {}
    };
    NodoV<std::vector<std::string>> *inicio;

public:

    /**
     * Constructor de la clase ListaV
     */
    ListaV() : inicio(nullptr) {}

    /**
     * Destructor de la clase ListaV
     */
    ~ListaV()
    {
        vaciarV();
    }

    /**
     * Funcion que vacia la listaV
     * @tparam void
     * @return void
     */
    void vaciarV()
    {
        NodoV<std::vector<std::string>> *aux = inicio;
        NodoV<std::vector<std::string>> *aBorrar;

        while (aux != nullptr)
        {
            aBorrar = aux;
            aux = aux->siguiente;
            delete aBorrar;
        }

        inicio = nullptr;
    }

    /**
     * Funcion que perimite insertar dato tipo vector a la lista
     * @tparam void
     * @return void
     */
    void insertarV(const std::vector<std::string> &datos)
    {
        NodoV<std::vector<std::string>> *nuevoNodo = new NodoV<std::vector<std::string>>(datos);
        nuevoNodo->siguiente = inicio;
        inicio = nuevoNodo;
    }

    void reemplazarV(const std::vector<std::string> &datos, std::size_t fila)
    {
        NodoV<std::vector<std::string>> *aux = inicio;
        int contadorFila = 0;

        // Iterar hasta la fila especificada
        while (aux != nullptr && contadorFila < fila)
        {
            aux = aux->siguiente;
            contadorFila++;
        }

        // Si la fila es válida, remplazar el vector de strings de esa fila
        if (aux != nullptr)
        {
            aux->dato = datos;
        }

        // Manejo de error si la fila no es válida
        throw std::out_of_range("Fila fuera de rango");
    }

    /**
     * Sobrecarga de operadores () -> permite expresar la lista como una matriz
     * @tparam void
     * @return void
     */

    std::string &operator()(std::size_t row, std::size_t col)
    {
        NodoV<std::vector<std::string>> *current = inicio;
        std::size_t currentRow = 0;

        while (currentRow < row)
        {
            current = current->siguiente;
            currentRow++;
        }

        std::vector<std::string> &rowData = current->dato;

        return rowData[col];
    }

    /**
     * Funcion que invierte la lista
     * @tparam void
     * @return void
     */

    void invertirV()
    {
        NodoV<std::vector<std::string>> *aux = inicio, *siguiente = nullptr, *anterior = nullptr;

        while (aux != nullptr)
        {
            siguiente = aux->siguiente;
            aux->siguiente = anterior;
            anterior = aux;
            aux = siguiente;
        }

        inicio = anterior;
    }

    /**
     * Funcion que retorna el tamaño de la lista
     * @tparam void
     * @return size_t
     *
     */
    int getTamanio()
    {
        NodoV<std::vector<std::string>> *aux = inicio;
        int contador = 0;

        while (aux != nullptr)
        {
            aux = aux->siguiente;
            contador++;
        }

        return contador;
    }

    // Sobrecarga del operador de corchetes para acceder a una fila específica

    std::vector<std::string> &operator[](std::size_t fila)
    {
        NodoV<std::vector<std::string>> *aux = inicio;
        int contadorFila = 0;

        // Avanzar hasta la fila especificada
        while (contadorFila < fila)
        {
            aux = aux->siguiente;
            contadorFila++;
        }

        return aux->dato;
    }

    // Tamaño de la fila especifica
    int getTamanio(std::size_t fila)
    {
        return (*this)[fila].size();
    }

   



};
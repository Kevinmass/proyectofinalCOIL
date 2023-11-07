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
        // Atributos
        U dato;

        // Puntero al siguiente nodo
        NodoV *siguiente;

        // Constructor
        NodoV(const U &val) : dato(val), siguiente(nullptr) {}
    };

    // Puntero al inicio de la lista
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
        // Puntero auxiliar para recorrer la lista
        NodoV<std::vector<std::string>> *aux = inicio;

        // Puntero para borrar los nodos
        NodoV<std::vector<std::string>> *aBorrar;

        // Recorrer la lista y borrar los nodos
        while (aux != nullptr)
        {
            aBorrar = aux;
            aux = aux->siguiente;
            delete aBorrar;
        }

        // Reiniciar el puntero al inicio
        inicio = nullptr;
    }

    /**
     * Funcion que perimite insertar dato tipo vector a la lista
     * @tparam void
     * @return void
     */
    void insertarV(const std::vector<std::string> &datos)
    {
        // Crear un nuevo nodo con los datos especificados
        NodoV<std::vector<std::string>> *nuevoNodo = new NodoV<std::vector<std::string>>(datos);

        // Insertar el nodo al inicio de la lista
        nuevoNodo->siguiente = inicio;

        // Actualizar el puntero al inicio
        inicio = nuevoNodo;
    }

    /**
     * Sobrecarga de operadores () -> permite expresar la lista como una matriz
     * @tparam void
     * @return void
     */

    std::string &operator()(std::size_t row, std::size_t col)
    {

        // Puntero auxiliar para recorrer la lista
        NodoV<std::vector<std::string>> *current = inicio;

        // Contador para la fila actual
        std::size_t currentRow = 0;

        // Avanzar hasta la fila especificada o hasta el final de la lista
        while (current != nullptr && currentRow < row)
        {
            current = current->siguiente;
            currentRow++;
        }

        // Si la fila es igual al puntero al final de la lista, la fila no es válida
        if (current == nullptr)
        {
            throw std::out_of_range("Fila fuera de rango");
        }

        // Obtener el vector de strings de la fila actual
        std::vector<std::string> &rowData = current->dato;

        // Si la columna es mayor al tamaño del vector, la columna no es válida
        if (col >= rowData.size())
        {
            throw std::out_of_range("Columna fuera de rango");
        }

        // Retornar el string de la columna especificada
        return rowData[col];
    }

    /**
     * Funcion que invierte la lista
     * @tparam void
     * @return void
     */

    void invertirV()
    {
        // Punteros auxiliares para recorrer la lista
        NodoV<std::vector<std::string>> *aux = inicio, *siguiente = nullptr, *anterior = nullptr;

        // Recorrer la lista y cambiar los punteros
        while (aux != nullptr)
        {
            siguiente = aux->siguiente;
            aux->siguiente = anterior;
            anterior = aux;
            aux = siguiente;
        }

        // Actualizar el puntero al inicio
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
        // Puntero auxiliar para recorrer la lista
        NodoV<std::vector<std::string>> *aux = inicio;
        int contador = 0;

        // Recorrer la lista y cuenta los nodos
        while (aux != nullptr)
        {
            aux = aux->siguiente;
            contador++;
        }

        // Retornar el contador
        return contador;
    }

    /**
     * Sobrecarga de operadores [] -> permite acceder a una fila de la lista
     * @tparam fila -> fila a la que se quiere acceder
     * @return vector<string> -> vector de strings de la fila especificada
     *
     */

    std::vector<std::string> &operator[](std::size_t fila)
    {
        // Puntero auxiliar para recorrer la lista
        NodoV<std::vector<std::string>> *aux = inicio;
        int contadorFila = 0;

        // Avanzar hasta la fila especificada
        while (aux != nullptr & contadorFila < fila)
        {
            aux = aux->siguiente;
            contadorFila++;
        }

        // Si la fila es igual al puntero al final de la lista, la fila no es válida
        if (aux == nullptr)
        {
            throw std::out_of_range("Fila fuera de rango");
        }

        return aux->dato;
    }

    /**
     * Funcion que retorna el tamaño de una fila de la lista
     * @tparam fila -> fila a la que se quiere acceder
     * @return int -> tamaño de la fila especificada
     *
     */
    int getTamanio(std::size_t fila)
    {
        return (*this)[fila].size();
    }
};
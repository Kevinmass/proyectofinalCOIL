#include <string.h>
#include "File.h"

class Inventario
{

private:
    int Depositos;
    std::string Articulos;
    int Cantidad;
    std::string Cantidadminima;
    std::string CantidadxDeposito;
    std::string Grupos;
    std::string CodigoBarra;

public:
    // Composicion
    file csv;
    std::vector<std::vector<std::string>> Datos;

    /**
     * Constructor de la clase Inventario
     * @tparam Char
     */
    Inventario(int Depositos, std::string Articulos, int Cantidad, std::string Cantidadminima, std::string CantidadxDeposito, std::string Grupos, std::string CodigoBarra)
    {
        this->Depositos = Depositos;
        this->Articulos = Articulos;
        this->Cantidad = Cantidad;
        this->Cantidadminima = Cantidadminima;
        this->CantidadxDeposito = CantidadxDeposito;
        this->Grupos = Grupos;
        this->CodigoBarra = CodigoBarra;
    }
    /**
     * Constructor por defecto de la clase Inventario
     * @tparam Char
     */
    Inventario()
    {
        this->Depositos = ' ';
        this->Articulos = ' ';
        this->Cantidad = ' ';
        this->Cantidadminima = ' ';
        this->CantidadxDeposito = ' ';
        this->Grupos = ' ';
        this->CodigoBarra = ' ';
    }

    /**
     * Funcion que permite ordenar el vector de vectores de string por codigo de barra
     * @tparam Vector de vectores de string
     * @return Vector de vectores de string ordenado
     */
    std::vector<std::vector<std::string>> shellSort(std::vector<std::vector<std::string>> &arr)
    {
        int n = arr.size();

        // Start with a big gap, then reduce the gap
        for (int gap = n / 2; gap > 0; gap /= 2)
        {

            for (int i = gap; i < n; i += 1)
            {

                std::vector<std::string> temp = arr[i];

                std::string codAUX = arr[i][1];
                int j;
                for (j = i; j >= gap && strcmp(arr[j - gap][1].c_str(), codAUX.c_str()) > 0; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }

        return arr;
    }

    /**
     * Funcion que permite realizar una busqueda binaria en un vector de vectores de string por codigo de barra
     * @tparam Vector de vectores de string
     * @return Posicion del elemento buscado
     */
    int binarySearch(std::vector<std::vector<std::string>> &arr, int l, int r, std::string codigoB)
    {
        if (r >= l)
        {
            int mid = l + (r - l) / 2;

            std::string codAUX = arr[mid][1];

            // Si el elemento esta en la mitad
            if (strcmp(codAUX.c_str(), codigoB.c_str()) == 0)
            {
                return mid;
            }
            // Si el elemento es menor que la mitad, entonces esta en la izquierda
            if (strcmp(codAUX.c_str(), codigoB.c_str()) > 0)
            {
                return binarySearch(arr, l, mid - 1, codigoB);
            }
            // Si el elemento es mayor que la mitad, entonces esta en la derecha
            if (strcmp(codAUX.c_str(), codigoB.c_str()) < 0)
            {
                return binarySearch(arr, mid + 1, r, codigoB);
            }
        }

        // Si el elemento no esta en el vector

        return -1;
    }

    /**
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    int GetCantidad()
    {

        Datos = csv.readV();

        Cantidad = Datos.size();

        return Cantidad;
    }

    /**
     * Funcion que retorna la cantidad de Depositos en el archivo
     * @tparam int
     * @return Depositos
     */
    int GetDepositos()
    {

        Datos = csv.readV();

        Depositos = (Datos[0].size()) - 3;

        return Depositos;
    }

    /**
     * Funcion que Muestra el inventario completo junto al grupo y nombre del articulo
     * @tparam string codigoB
     * @return void
     */

    void StockTotal(std::string codigoB)
    {
        std::cout << "Ingrese el codigo de barras (entre comillas)" << std::endl;

        std::string codigoB;
        std::vector<std::vector<std::string>> dataO;

        dataO = shellSort(Datos);

        int pos = 0;

        pos = (binarySearch(dataO, 0, GetCantidad(), codigoB));

        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        std::cout << "Grupo -    Articulo-                    ";

        for (int i = 0; i < (Datos[0].size()) - 3; i++)
        {
            std::cout << "        D" << i + 1;
        }

        std::cout << std::endl;

        for (int i = 0; i < Datos[0].size(); i++)
        {

            if (i != 1)
            {

                std::cout << Datos[pos][i] << "        ";
            }
        }
    }
};
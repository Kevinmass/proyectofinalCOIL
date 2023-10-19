#include <string.h>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>
#include "File.h"

/* Clase encargada de las funciones de manejo del Inventario del archivo --> Datos
 * @tparam Char -> Datos del archivo dado por el cliente --> Compocision con la clase file
 * @return Distintas funciones utiles para el manejo del inventario
 */

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

        // Comenzar con un gran espacio, luego reducirlo
        for (int gap = n / 2; gap > 0; gap /= 2)
        {

            // Hacer un ordenamiento con el espacio actual
            for (int i = gap; i < n; i += 1)
            {

                // Guardar el valor actual para que no se pierda
                std::vector<std::string> temp = arr[i];

                // Creamos un string aux para utilizar la funcion strcmp
                std::string codAUX = arr[i][1];
                int j;
                // Mover los elementos en el espacio si son mayores que el valor temporal de arr[i]
                for (j = i; j >= gap && strcmp(arr[j - gap][1].c_str(), codAUX.c_str()) > 0; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }

                // Colocar el valor temporal en su lugar
                arr[j] = temp;
            }
        }

        // Retornar el vector de vectores de string ordenado
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

    void StockTotal_CODIGO(std::string codigoB)
    {
        std::vector<std::vector<std::string>> dataSE;
        std::vector<std::vector<std::string>> dataO;

        // Quita los espacios en blanco sin perder los datos introducidos despues de teclear el espacio
        codigoB.erase(std::remove_if(codigoB.begin(), codigoB.end(),
                                     [](char &c)
                                     {
                                         return std::isspace<char>(c, std::locale::classic());
                                     }),
                      codigoB.end());

        Datos = csv.readV();

        dataSE = csv.DataSE(Datos, 1);

        dataO = shellSort(dataSE);

        int pos = 0;

        pos = (binarySearch(dataO, 0, GetCantidad(), codigoB));

        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        std::cout << "Grupo -    Articulo-                    ";

        for (int i = 0; i < GetDepositos(); i++)
        {
            std::cout << "        D" << i + 1;
        }

        std::cout << std::endl;

        for (int i = 0; i < Datos[0].size(); i++)
        {

            if (i != 1)
            {

                std::cout << dataSE[pos][i] << "        ";
            }
        }

        std::cout << std::endl;

        // Cantidad total de productos
        int CantidadTotal = 0;

        
        for (int i = 3; i < dataSE[pos].size(); i++)
        {
            
            std::string cantidadStr = dataSE[pos][i];
            cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

            if (!cantidadStr.empty())
            {
                CantidadTotal += std::stoi(cantidadStr);
            }
        }

        std::cout << "Cantidad total de productos: " << CantidadTotal << std::endl;
    }
};
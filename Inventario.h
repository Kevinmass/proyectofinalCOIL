#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    int GetCantidad()
    {

        Datos = csv.readV();

        Cantidad = (Datos.size()) - 1;

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

    // ShellSort --> quizas sirva
    void shellSort()
    {

        Datos = csv.readV();

        int n = Datos.size();
        int gap = n / 2;
        while (gap > 0)
        {
            for (int i = gap; i < n; i++)
            {
                int j = i;
                std::vector<std::string> temp = Datos[i];
                while (j >= gap && Datos[j - gap][2] > temp[2])
                {
                    Datos[j] = Datos[j - gap];
                    j -= gap;
                }
                Datos[j] = temp;
            }
            gap /= 2;
        }
    }

    // MEJOR CAMBIARLO POR CODIGO DE BARRAS

    int binarySearch(std::vector<std::vector<std::string>> &arr, int l, int r, std::string nombre)
    {
        if (r >= l)
        {
            int mid = l + (r - l) / 2;

            // Si el elemento esta en la mitad
            if (arr[mid][2] == nombre)
                return mid;

            // Si el elemento es menor que la mitad, entonces esta en la izquierda
            if (arr[mid][2] > nombre)
                return binarySearch(arr, l, mid - 1, nombre);

            // Si el elemento es mayor que la mitad, entonces esta en la derecha
            return binarySearch(arr, mid + 1, r, nombre);
        }

        // Si el elemento no esta en el vector
        return -1;
    }

    int StockTotal(std::string nombre)
    {

        Datos = csv.readV();

        shellSort();

        int stock = 0;
        int pos = binarySearch(Datos, 0, GetCantidad(), nombre);
        for (int i = 0; i < GetDepositos(); i++)
        {
            stock += stoi(Datos[pos][i + 3]);
        }
        return stock;
    }
};
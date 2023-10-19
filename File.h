#include <iostream>
#include <fstream>
#include <sstream>
//#include "Lista.h"
#include "ListaV.h"
#include <cctype>
#include <algorithm>

/**
 * Clase encargada de las funciones de manejo de archivo
 * @tparam Char -> nombre del archivo dado por el cliente
 * @return Data del archivo leido en forma de vector de vectores de strings
 */

class file
{

private:
public:
    file() {}

    ~file() {}

    /**
     * Funcion que lee el archivo y lo guarda en un Lista de vectores de strings
     * @tparam void
     * @return Data -> datos del archivo csv en forma de Lista de vectores de strings
     */
    ListaV<std::vector<std::string>> readV()
    {
        // incluir archivo tecleado por el usuario -> En lo posible

        std::ifstream file("InventariO.csv");
        if (!file.is_open())
        {
            std::cerr << "Failed to open file\n";
        }

        ListaV<std::vector<std::string>> Data;

        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> row;
            std::stringstream ss(line);

            std::string cell;
            while (std::getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            Data.insertarV(row);
        }
        
        Data.invertirV();

        file.close();

        return Data;
    }
    /**
     * Funcion que quita los espacios en blanco entre los strings de las diferentes posiciones del vector de vectores en la columna del codigo
     * @tparam Vector de vectores de strings
     * @return Vector de vectores de strings sin espacios en blanco
     */

    ListaV<std::vector<std::string>> DataSE_COD(ListaV<std::vector<std::string>> &arr)
    {

        ListaV<std::vector<std::string>> dataSE = arr;

        for (int i = 0; i < dataSE.getTamanio(); i++)
        {

            dataSE(i,1).erase(remove_if(dataSE(i,1).begin(), dataSE(i,1).end(), ::isspace), dataSE(i,1).end());
        }

        return dataSE;
    }
};
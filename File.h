#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Lista/ListaV.h"

//.

/**
 * Clase encargada de las funciones de manejo de archivo
 * @tparam Char -> nombre del archivo dado por el cliente
 * @return Data del archivo leido en forma de vector de vectores de strings
 */

class file{


private:
public:
    /**
     * Funcion que lee el archivo y lo guarda en un vector de vectores de strings
     * @tparam void
     * @return Data -> datos del archivo csv en forma de vector de vectores de strings
     */
    std::vector<std::vector<std::string>> readV()
    {
        // incluir archivo tecleado por el usuario -> En lo posible
        
        std::ifstream file("InventariO.csv", std::ios::in);

        if (!file.is_open())
        {
            std::cerr << "Failed to open file\n";
        }

        std::vector<std::vector<std::string>> Datos;

        std::string Linea;
        while (std::getline(file, Linea))
        {
            std::vector<std::string> Columna;
            std::stringstream ss(Linea);

            std::string Casilla;
            while (std::getline(ss, Casilla, ','))
            {
                Columna.push_back(Casilla);
            }

            Datos.push_back(Columna);
        }

        file.close();

        return Datos;
    }

    /**
     * Funcion que quita los espacios en blanco entre los strings de las diferentes posiciones del vector de vectores en la columna del codigo
     * @tparam Vector de vectores de strings
     * @return Vector de vectores de strings sin espacios en blanco
     */

    std::vector<std::vector<std::string>> DataSE(std::vector<std::vector<std::string>> &arr, int Columna)
    {

        std::vector<std::vector<std::string>> dataSE = arr;

        for (int i = 0; i < dataSE.size(); i++)
        {

            dataSE[i][Columna].erase(remove_if(dataSE[i][Columna].begin(), dataSE[i][Columna].end(), ::isspace), dataSE[i][Columna].end());
        }

        return dataSE;
    }

    ListaV<std::vector<std::string>> readL()
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

    ListaV<std::vector<std::string>> DataSE_L(ListaV<std::vector<std::string>> &arr, int columna)
    {

        ListaV<std::vector<std::string>> DatosSE = arr;

        for (int i = 0; i < DatosSE.getTamanio(); i++)
        {

            DatosSE(i, columna).erase(remove_if(DatosSE(i, columna).begin(), DatosSE(i, columna).end(), ::isspace), DatosSE(i, columna).end());
        }

        return DatosSE;
    }
};
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include "Lista/ListaV.h"

//.

/**
 * Clase encargada de las funciones de manejo de archivo
 * @tparam Char -> nombre del archivo dado por el cliente
 * @return Data del archivo leido en forma de vector de vectores de strings
 */

class file
{

private:
public:
    /**
     * Funcion que lee el archivo y lo guarda en un vector de vectores de strings
     * @tparam void
     * @return Data -> datos del archivo csv en forma de vector de vectores de strings
     */
    std::vector<std::vector<std::string>> readV(std::string csv)
    {

        // Se abre el archivo
        std::ifstream file(csv, std::ios::in);

        // Se verifica que el archivo se haya abierto correctamente
        if (!file.is_open())
        {
            std::cerr << "Failed to open file\n";
        }

        // Se crea un vector de vectores de strings
        std::vector<std::vector<std::string>> Datos;

        std::string Linea;

        // Se lee el archivo linea por linea
        while (std::getline(file, Linea))
        {
            // Se crea un vector de strings --> Columna
            std::vector<std::string> Columna;

            // Se crea un stringstream para separar los strings por comas
            std::stringstream ss(Linea);

            // Se crea un string para guardar cada string separado por comas
            std::string Casilla;

            // Se separan los strings por comas y se guardan en el vector de strings
            while (std::getline(ss, Casilla, ','))
            {
                Columna.push_back(Casilla);
            }

            // Se guarda el vector de strings en el vector de vectores de strings

            Datos.push_back(Columna);
        }

        // Se cierra el archivo
        file.close();

        // Se retorna el vector de vectores de strings
        return Datos;
    }

    /**
     * Funcion que quita los espacios en blanco entre los strings de las diferentes posiciones del vector de vectores en la columna del codigo
     * @tparam Vector de vectores de strings
     * @return Vector de vectores de strings sin espacios en blanco
     */

    std::vector<std::vector<std::string>> DataSE(std::vector<std::vector<std::string>> &arr, int Columna)
    {

        // Se crea un vector de vectores de strings
        std::vector<std::vector<std::string>> dataSE = arr;

        // Se quitan los espacios en blanco de la columna del ingresado
        for (int i = 0; i < dataSE.size(); i++)
        {

            dataSE[i][Columna].erase(remove_if(dataSE[i][Columna].begin(), dataSE[i][Columna].end(), ::isspace), dataSE[i][Columna].end());
        }

        return dataSE;
    }

    /**
     * Funcion que lee el archivo y lo guarda en un Lista de vectores de strings
     * @tparam void
     * @return Data -> datos del archivo csv en forma de Lista de vectores de strings
     */

    ListaV<std::vector<std::string>> readL(std::string csv)
    {
        
        // Se abre el archivo
        std::ifstream file(csv, std::ios::in);

        // Se verifica que el archivo se haya abierto correctamente
        if (!file.is_open())
        {
            std::cerr << "Failed to open file\n";
        }
        
        // Se crea una ListaV de vectores de strings
        ListaV<std::vector<std::string>> Data;

        // Se lee el archivo linea por linea
        std::string line;
        while (std::getline(file, line))
        {   
            // Se crea un vector de strings --> Columna
            std::vector<std::string> row;

            // Se crea un stringstream para separar los strings por comas
            std::stringstream ss(line);

            // Se crea un string para guardar cada string separado por comas
            std::string cell;

            // Se separan los strings por comas y se guardan en el vector de strings
            while (std::getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            // Se guarda el vector de strings en la ListaV de vectores de strings

            Data.insertarV(row);
        }

        // Se invierte la ListaV de vectores de strings para que quede en el orden correcto
        Data.invertirV();

        // Se cierra el archivo
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

        // Se crea un ListaV de vectores de strings
        ListaV<std::vector<std::string>> DatosSE = arr;

        // Se quitan los espacios en blanco de la columna del ingresado
        for (int i = 0; i < DatosSE.getTamanio(); i++)
        {

            DatosSE(i, columna).erase(remove_if(DatosSE(i, columna).begin(), DatosSE(i, columna).end(), ::isspace), DatosSE(i, columna).end());
        }

        return DatosSE;
    }
};
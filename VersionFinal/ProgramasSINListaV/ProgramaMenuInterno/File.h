#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

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
    std::vector<std::vector<std::string>> readV()
    {

        // Se abre el archivo
        std::ifstream file("InventariO.csv", std::ios::in);

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
};
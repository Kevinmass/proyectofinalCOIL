#include <iostream>
#include <fstream>
#include <sstream>
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
        // incluir archivo tecleado por el usuario -> En lo posible

        std::ifstream file("Inventario.csv", std::ios::in);

        if (!file.is_open())
        {
            std::cerr << "Failed to open file\n";
        }

        std::vector<std::vector<std::string>> data;

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

            data.push_back(row);
        }

        file.close();

        return data;
    }

    /**
     * Funcion que quita los espacios en blanco entre los strings de las diferentes posiciones del vector de vectores en la columna del codigo
     * @tparam Vector de vectores de strings
     * @return Vector de vectores de strings sin espacios en blanco
     */

    std::vector<std::vector<std::string>> DataSE_COD(std::vector<std::vector<std::string>> &arr)
    {

        std::vector<std::vector<std::string>> dataSE = arr;

        for (int i = 0; i < dataSE.size(); i++)
        {

            dataSE[i][1].erase(remove_if(dataSE[i][1].begin(), dataSE[i][1].end(), ::isspace), dataSE[i][1].end());
        }

        return dataSE;
    }
};
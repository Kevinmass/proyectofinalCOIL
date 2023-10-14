#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/**
 * Clase encargada de las funciones de manejo de archivo
 * @tparam Char -> nombre del archivo dado por el cliente
 * @return Data del archivo leido en forma de vector de vectores de strings
 */

class file
{

private:
    char Archivo;

public:
    /**
     * Constructor de la clase file
     * @tparam Char
     */

    file(char Archivo)
    {
        this->Archivo = Archivo;
    }
    /**
     * Constructor por defecto de la clase file
     * @tparam Char
     */
    file()
    {
        this->Archivo = ' ';
    }

    /**
     * Funcion que retorna el nombre del archivo
     * @tparam Char
     * @return Archivo
     */
    char file::setARCHIVO(char Archivo)
    {
        this->Archivo = Archivo;
    }

    /**
     * Funcion que lee el archivo y lo guarda en un vector de vectores de strings
     * @tparam Char
     * @return Data
     */
    std::vector<std::vector<std::string>> file::readV()
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
     * Funcion que lee el archivo y lo guarda en un string
     * @tparam Char
     * @return Data
     */
    std::string file::readS()
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

        //convertir data a string

        std::string dataString;

        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                dataString += data[i][j];
                dataString += " ";
            }
            dataString += "\n";
        }

        file.close();

        return dataString;

        
    }
};
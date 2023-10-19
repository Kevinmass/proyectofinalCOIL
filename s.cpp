#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <cctype>
#include "ListaV.h"
#include <algorithm>

using namespace std;

// Ordenar el arreglo de vectores de vectores para poder utilizar busqueda binaria

std::vector<std::vector<std::string>> shellSort(std::vector<std::vector<std::string>> &arr)
{
    int n = arr.size();

    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; i += 1)
        {

            std::vector<std::string> temp = arr[i];

            string codAUX = arr[i][1];
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

int binarySearch(std::vector<std::vector<std::string>> &arr, int l, int r, std::string codigoB)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        string codAUX = arr[mid][1];

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

int main()
{
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

    ListaV<std::vector<std::string>> dataSE = Data;

    for (int i = 0; i < dataSE.getTamanio(); i++)
    {

        dataSE(i, 1).erase(remove_if(dataSE(i, 1).begin(), dataSE(i, 1).end(), ::isspace), dataSE(i, 1).end());
    }

    cout << "Data nueva sin espacios en blanco: " << endl;

    for (int i = 0; i < dataSE.getTamanio(); i++)
    {
        for (int j = 0; j < dataSE.getTamanio(0); j++)
        {
            cout << dataSE(i, j) << " ";
        }
        cout << endl;
    }
}

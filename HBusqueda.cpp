#include <vector>
#include <string>

//Busqueda binaria de un nombre en un vector de vectores de string

int binarySearch(std::vector<std::vector<std::string>> &arr, int l, int r, std::string nombre)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        // Si el elemento esta en la mitad
        if (arr[mid][0] == nombre)
            return mid;

        // Si el elemento es menor que la mitad, entonces esta en la izquierda
        if (arr[mid][0] > nombre)
            return binarySearch(arr, l, mid - 1, nombre);

        // Si el elemento es mayor que la mitad, entonces esta en la derecha
        return binarySearch(arr, mid + 1, r, nombre);
    }

    // Si el elemento no esta en el vector
    return -1;
}


//Ordenar vector de vectores de string por nombre









#include "Inventario.h"
#include <iostream>
using namespace std;

int main()
{
    Inventario inventario;
    string codigo;
    getline(cin, codigo);
    inventario.stock(codigo);
    cout<< inventario.total_art_dif();
}
#include "Inventario.h"
#include <iostream>
using namespace std;

int main()
{

    std::string nombre;
    int aux;
    Inventario inventario;
    getline(cin, nombre);
    cout << nombre << endl;
    /*
"BANQUETA TAPIZADA COST BCO  BASE PINTADA NEGRO"
*/
    inventario.stock(nombre);
}
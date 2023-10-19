#include "Inventario.h"

using namespace std;

int main()
{
    Inventario inventario;
    string codigo;

    cout << inventario.GetCantidad() << endl;
    cout << inventario.GetDepositos() << endl;

    cout << "Ingrese el codigo de barra: ";
    
    getline(cin, codigo);

    inventario.StockTotalC(codigo);

    
    




    

    
    


}
#include <iostream>
class Procesador_Inventario
{
private:
public:
    void menu();
};

void Procesador_Inventario::menu()
{
    int x;
    bool menu = true;
    std::cout << "          - - -  Programa Procesador de Inventario  - - -\n";
    std::cout << "\nCARGANDO PROGRAMA...\n";
    do
    {
        std::cout << "Que desea hacer?\n";
        std::cout << "1. Cantidad total de articulos diferentes.\n";
        std::cout << "2. Cantidad total de articulos.\n";
        std::cout << "3. Listado de articulos que estan en el minimo de stock.\n";
        std::cout << "4. Listado de articulos que estan en el minimo de stock y por deposito.\n";
        std::cout << "5. Stock individual de cada articulo.\n";
        std::cout << "6. Stock individual de cada articulo segun deposito.\n";
        std::cout << "7. Los articulos que igualan o superen determinada cantidad en stock.\n";
        std::cout << "8. Salir.\n";
        std::cout << "\n\n\nIngrese el numero de la opcion que desea: ";
        std::cin >> x;
        switch (x)
        {
        case 1:
            system("cls");
            std::cout << "\n\n          - - -  Cantidad total de articulos diferentes  - - -\n\n\n";
            break;
        case 2:
            system("cls");
            std::cout << "\n\n          - - -  Cantidad total de articulos  - - -\n\n\n";
            break;
        case 3:
            system("cls");
            std::cout << "\n\n          - - -  Listado de articulos que estan en el minimo de stock  - - -\n\n\n";
            break;
        case 4:
            system("cls");
            std::cout << "\n\n          - - -  Listado de articulos que estan en el minimo de stock y por deposito  - - -\n\n\n";
            break;
        case 5:
            system("cls");
            std::cout << "\n\n          - - -  Stock individual de cada articulo  - - -\n\n\n";
            break;
        case 6:
            system("cls");
            std::cout << "\n\n          - - -  Stock individual de cada articulo segun deposito  - - -\n\n\n";
            break;
        case 7:
            system("cls");
            std::cout << "\n\n          - - -  Los articulos que igualan o superen determinada cantidad en stock  - - -\n\n\n";
            break;
        case 8:
            system("cls");
            std::cout << "Saliendo...\n";
            menu = false;
            break;
        default:
            std::cout << "\n\n\n\n***       Opcion no valida        ***\n\n\n\n";
            break;
        }
    } while (menu == true);
}
/**Cantidad total de articulos diferentes.
 *Cantidad total de articulos.
 *Listado de articulos que estan en el minimo de stock.
 *Listado de articulos que estan en el minimo de stock y por deposito.
 *Stock individual de cada articulo.
 * Stock individual de cada articulo segun deposito.
 *Los articulos que igualan o superen determinada cantidad en stock*/
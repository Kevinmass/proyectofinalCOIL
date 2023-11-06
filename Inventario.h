#include <string.h>
#include <cctype>
#include <algorithm>
#include <ctime>
#include "File.h"
#include "Cola/Cola.h"

/* Clase encargada de las funciones de manejo del Inventario del archivo --> Datos
 * @tparam Char -> Datos del archivo dado por el cliente --> Compocision con la clase file
 * @return Distintas funciones utiles para el manejo del inventario
 */
class Inventario
{
private:
    int Depositos;
    int Cantidad;

public:
    // Composicion

    file csv;

    std::vector<std::vector<std::string>> Datos;
    std::vector<std::vector<std::string>> dataSE;
    std::vector<std::vector<std::string>> dataO;
    ListaV<std::vector<std::string>> DatosL;
    ListaV<std::vector<std::string>> DatosSE;

    int argc;
    char **argv;

    /**
     * Constructor de la clase Inventario
     * @tparam Int argc cantidad de argumentos
     * @tparam Char **argv argumentos
     */
    Inventario(int argc, char **argv)
    {
        this->argc = argc;
        this->argv = argv;
    }

    /**
     * Constructor por defecto de la clase Inventario
     * @tparam Char
     */
    Inventario()
    {
        this->Depositos = ' ';
        this->Cantidad = ' ';
        this->argc = ' ';
    }

    /**
     * Funcion que llama al resto de funciones
     * @tparam int
     * @return Cantidad
     */

    void menu()
    {

        std::cout << "\t\tMANAGER DE STOCK" << std::endl;
        switch (argc)
        {
        case 1:
            std::cout << "\n\n\n***DEBUG MENU***\n\n\n"
                      << std::endl;
            std::cout << "FUNCIONES DISPONIBLES\n\n-\"total_art_dif\" Cantidad total de articulos diferentes. \n-\"total_art\" Cantidad total de articulos. \n-\"min_stock\" [n] Listado de articulos con cantidad n o menos de stock.\n-\"min_stock\" [n],[deposito] Listado de articulos con cantidad n o menos de stock segun un deposito.\n-\"stock\" [nombre_articulo] El stock total del articulo ingresado como argumento.\n-\"stock\" [nombre_articulo],[deposito] El stock del articulo en un deposito.\n-\"max_Stock\" [n] Listado de aquellos articulos cuyo stock es igual o supera el numero n.\n-\"Datos_xgrupos\" Muestra el inventario completo de los articulos de los grupos encontrados en el archivo" << std::endl;
            break;
        case 2:
            std::cout << "Agregue algun parametro o llame al ejecutable solo para iniciar modo debug" << std::endl;
            break;
        case 3:
            if (strcmp(argv[1], "total_art_dif") == 0)
            {
                std::cout << "Cantidad total de articulos diferentes: ";
                total_art_dif();
            }
            else if (strcmp(argv[1], "total_art") == 0)
            {
                total_art();
            }
            else if (strcmp(argv[1], "Datos_xgrupos") == 0)
            {
                Datos_xgrupos();
            }
            else
            {
                std::cout << "Error en el argumento" << std::endl;
            }
            break;
        case 4:
            if (strcmp(argv[1], "min_stock") == 0)
            {
                int n = atoi(argv[2]);
                min_stock(n);
            }
            else if (strcmp(argv[1], "stock") == 0)
            {
                std::string n = argv[2];
                stock(n);
            }
            else if (strcmp(argv[1], "max_stock") == 0)
            {
                int n = atoi(argv[2]);
                max_stock(n);
            }
            else
            {
                std::cout << "Error en el argumento" << std::endl;
            }
            break;
        case 5:
            if (strcmp(argv[1], "min_stock") == 0)
            {
                int n = atoi(argv[2]), n1 = atoi(argv[3]);
                min_stock(n, n1);
            }
            else if (strcmp(argv[1], "stock") == 0)
            {
                std::string n = argv[2];
                int n1;
                stock(n, n1);
            }
            else
            {
                std::cout << "Error en el argumento" << std::endl;
            }

            break;

        default:
            std::cout << "Error en la cantidad de argumentos" << std::endl;
            break;
        }
    }

    /**
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    int GetCantidad()
    {

        DatosL = csv.readL(argv[argc-1]);

        Cantidad = DatosL.getTamanio();

        return Cantidad;
    }

    /**
     * Funcion que retorna la cantidad de Depositos en el archivo
     * @tparam int
     * @return Depositos
     */
    int GetDepositos()
    {

        DatosL = csv.readL(argv[argc-1]);

        Depositos = (DatosL.getTamanio(0)) - 5;

        return Depositos;
    }

    /**
     * Funcion que permite ordenar el vector de vectores de string por codigo de barra
     * @tparam Vector de vectores de string
     * @return Vector de vectores de string ordenado
     */
    std::vector<std::vector<std::string>> shellSort(std::vector<std::vector<std::string>> &arr, int columna)
    {
        int n = arr.size();

        // Comenzar con un gran espacio, luego reducirlo
        for (int gap = n / 2; gap > 0; gap /= 2)
        {

            // Hacer un ordenamiento con el espacio actual
            for (int i = gap; i < n; i += 1)
            {

                // Guardar el valor actual para que no se pierda
                std::vector<std::string> temp = arr[i];

                // Creamos un string aux para utilizar la funcion strcmp
                std::string codAUX = arr[i][columna];
                int j;
                // Mover los elementos en el espacio si son mayores que el valor temporal de arr[i]
                for (j = i; j >= gap && strcmp(arr[j - gap][columna].c_str(), codAUX.c_str()) > 0; j -= gap)
                {
                    arr[j] = arr[j - gap];
                }

                // Colocar el valor temporal en su lugar
                arr[j] = temp;
            }
        }

        // Retornar el vector de vectores de string ordenado
        return arr;
    }

    /**
     * Funcion que permite realizar una busqueda binaria en un vector de vectores de string por codigo de barra
     * @tparam Vector de vectores de string
     * @return Posicion del elemento buscado
     */
    int binarySearch(std::vector<std::vector<std::string>> &arr, int l, int r, std::string Identificador, int columna)
    {
        if (r >= l)
        {
            int mid = l + (r - l) / 2;

            std::string codAUX = arr[mid][columna];

            // Si el elemento esta en la mitad
            if (strcmp(codAUX.c_str(), Identificador.c_str()) == 0)
            {
                return mid;
            }
            // Si el elemento es menor que la mitad, entonces esta en la izquierda
            if (strcmp(codAUX.c_str(), Identificador.c_str()) > 0)
            {
                return binarySearch(arr, l, mid - 1, Identificador, columna);
            }
            // Si el elemento es mayor que la mitad, entonces esta en la derecha
            if (strcmp(codAUX.c_str(), Identificador.c_str()) < 0)
            {
                return binarySearch(arr, mid + 1, r, Identificador, columna);
            }
        }

        // Si el elemento no esta en el vector
        std::cout << "No se encuentra el elemento" << std::endl;
        return -1;
    }

    /**
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    void total_art_dif() // funciona
    {
        DatosL = csv.readL(argv[argc-1]);

        Cantidad = DatosL.getTamanio();

        std::cout << Cantidad - 1;
    }

    /**
     * Funcion que muestre la cantidad total de articulos
     * @tparam void
     * @return void
     */

    void total_art() // funciona
    {
        Datos = csv.readV(argv[argc-1]);
        int fin = Datos[0].size();
        int suma = 0, cont = 0;
        std::string cantidadStr;
        for (int i = 1; i < Datos.size(); i++)
        {
            int total = 0;

            for (int j = 3; j < fin; j++) // Comienza desde el indice 3 y llega hasta el numero de depositos.
            {
                cantidadStr = Datos[i][j];
                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());

                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    for (int h = 0; h < strlen(cantidadStr.c_str()) - 1; h++)
                    {
                        cantidadStr[h] = cantidadStr[h + 1];
                    }
                    // Se pasa de valor char a int y se suman
                    total += std::stoi(cantidadStr);
                    suma += std::stoi(cantidadStr);
                }
            }

            std::cout << "Articulo: " << Datos[i][2] << " - Stock total: " << total << std::endl; // verificar si es Datos[i][1] o Datos[i][2]
        }
        std::cout << "El total de productos es: " << suma << std::endl;
    }

    /**
     * Listado de articulos con cantidad n o menos de stock segun un deposito
     * @tparam int n numero de stock
     * @tparam int deposito numero de deposito
     * @return void
     */

    void min_stock(int n) // funciona
    {
        int fin = 0, auxStock = 0, cont;
        std::string cantidadStr;
        Cola<int> cola;
        // Se lee el csv
        Datos = csv.readV(argv[argc-1]);

        fin = Datos[0].size();

        for (int i = 1; i < Datos.size(); i++)
        {
            auxStock = 0;
            for (int j = 3; j < fin; j++)
            {
                cantidadStr = Datos[i][j];
                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());
                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    for (int h = 0; h < strlen(cantidadStr.c_str()) - 1; h++)
                    {
                        // Se mueve el numero para eliminar la primera comilla para que funcione el stoi
                        cantidadStr[h] = cantidadStr[h + 1];
                    }
                    // Se pasa de valor char a int y se suman
                    auxStock += std::stoi(cantidadStr);
                }
            }
            if (auxStock <= n)
            {
                // Los Articulos que se encuentren en el rango se encola su posicion
                cola.encolar(i);
            }
        }
        cont = cola.Tamanio();
        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << "Codigo de barras\t\t\t\tArticulo" << std::endl;
            for (int i = 0; i < cont; i++)
            {
                std::cout << Datos[cola.peek()][1] << "\t\t\t" << Datos[cola.peek()][2] << "\t\t" << std::endl;
                cola.desencolar();
            }
        }
    }

    /**
     * Listado de articulos con cantidad n o menos de stock segun un deposito
     * @tparam int n numero de stock
     * @tparam int deposito numero de deposito
     * @return void
     */
    void min_stock(int n, int deposito) // funciona
    {
        int fin = 0, auxStock = 0, cont;
        std::string cantidadStr;
        Cola<int> cola;
        // Se lee el csv
        Datos = csv.readV(argv[argc-1]);

        fin = Datos[0].size();

        for (int i = 1; i < Datos.size(); i++)
        {
            auxStock = 0;
            cantidadStr = Datos[i][deposito + 3];
            // Se eliminan los espacios en blanco
            cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());
            // Se chequea que no este vacio el string
            if (cantidadStr != "\"\"")
            {
                for (int h = 0; h < strlen(cantidadStr.c_str()) - 1; h++)
                {
                    // Se mueve el numero para eliminar la primera comilla para que funcione el stoi
                    cantidadStr[h] = cantidadStr[h + 1];
                }
                // Se pasa de valor char a int y se suman
                auxStock += std::stoi(cantidadStr);
            }
            if (auxStock <= n)
            {
                // Los Articulos que se encuentren en el rango se encola su posicion
                cola.encolar(i);
            }
        }
        cont = cola.Tamanio();
        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << "Codigo de barras\t\t\t\tArticulo" << std::endl;
            for (int i = 0; i < cont; i++)
            {
                std::cout << Datos[cola.peek()][1] << "\t\t\t" << Datos[cola.peek()][2] << "\t\t" << std::endl;
                cola.desencolar();
            }
        }
    }

    /**
     * Funcion que Muestra el inventario completo junto al grupo y nombre del articulo
     * @tparam string NombreArticulo
     * @return void
     */

    void stock(std::string NombreArticulo)
    {
        int t0, t1;

        t0 = clock();

        // Quita los espacios en blanco sin perder los datos introducidos despues de teclear el espacio
        NombreArticulo.erase(std::remove_if(NombreArticulo.begin(), NombreArticulo.end(),
                                            [](char &c)
                                            {
                                                return std::isspace<char>(c, std::locale::classic());
                                            }),
                             NombreArticulo.end());
        Datos = csv.readV(argv[argc-1]);
        dataSE = csv.DataSE(Datos, 2);
        dataO = shellSort(dataSE, 2);

        int pos = 0;

        pos = (binarySearch(dataO, 1, GetCantidad() - 1, NombreArticulo, 2));
        if (pos == -1)
        {
            return;
        }

        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        DatosL = csv.readL(argv[argc-1]);

        DatosSE = csv.DataSE_L(DatosL, 2);

        std::cout << std::endl;

        std::cout << "-Nombre del Articulo " << NombreArticulo << " ENCONTRADO" << std::endl;
        std::cout << "- Codigo de barras del Articulo: " << DatosSE(pos, 1) << std::endl;

        // Cantidad x deposito del producto
        std::cout << std::endl;
        std::cout << "--Cantidad por deposito--" << std::endl;
        for (int i = 3; i < DatosSE.getTamanio(pos); i++)
        {
            std::cout << "Deposito " << i - 2 << ": " << DatosSE(pos, i) << std::endl;
        }

        std::cout << std::endl;

        // Cantidad total de productos
        int CantidadTotal = 0;

        for (int i = 3; i < DatosSE.getTamanio(pos); i++)
        {

            std::string cantidadStr = DatosSE(pos, i);
            cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

            if (!cantidadStr.empty())
            {
                CantidadTotal += std::stoi(cantidadStr);
            }
        }

        std::cout << "Cantidad total de productos: " << CantidadTotal << std::endl;

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     * Funcion que Muestra el inventario completo junto al grupo y nombre del articulo
     * @tparam string NombreArticulo
     * @return void
     */

    void stock(std::string NombreArticulo, int nro_deposito)
    {
        int t0, t1;

        t0 = clock();

        // Quita los espacios en blanco sin perder los datos introducidos despues de teclear el espacio
        NombreArticulo.erase(std::remove_if(NombreArticulo.begin(), NombreArticulo.end(),
                                            [](char &c)
                                            {
                                                return std::isspace<char>(c, std::locale::classic());
                                            }),
                             NombreArticulo.end());

        Datos = csv.readV(argv[argc-1]);

        dataSE = csv.DataSE(Datos, 2);

        dataO = shellSort(dataSE, 2);

        int pos = 0;

        pos = (binarySearch(dataO, 0, GetCantidad(), NombreArticulo, 2));

        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        std::cout << std::endl;

        std::cout << "-Nombre del Articulo " << NombreArticulo << " ENCONTRADO" << std::endl;
        std::cout << "- Codigo de barras del Articulo: " << dataSE[pos][1] << std::endl;

        // Cantidad del producto en x deposito
        std::cout << std::endl;
        std::cout << "--Cantidad por deposito--" << std::endl;

        std::cout << "Deposito " << nro_deposito << ": " << dataSE[pos][nro_deposito] << std::endl;

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     * Listado de aquellos articulos cuyo stock es igual o supera el numero n
     * @tparam int n numero de stock
     * @return void
     */

    void max_stock(int n) // funciona
    {
        int fin = 0, auxStock = 0, cont;
        std::string cantidadStr;
        Cola<int> cola;
        // Se lee el csv
        Datos = csv.readV(argv[argc-1]);

        fin = Datos[0].size();

        for (int i = 1; i < Datos.size(); i++)
        {
            auxStock = 0;
            for (int j = 3; j < fin; j++)
            {
                cantidadStr = Datos[i][j];
                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());
                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    for (int h = 0; h < strlen(cantidadStr.c_str()) - 1; h++)
                    {
                        // Se mueve el numero para eliminar la primera comilla para que funcione el stoi
                        cantidadStr[h] = cantidadStr[h + 1];
                    }
                    // Se pasa de valor char a int y se suman
                    auxStock += std::stoi(cantidadStr);
                }
            }
            if (auxStock >= n)
            {
                // Los Articulos que se encuentren en el rango se encola su posicion
                cola.encolar(i);
            }
        }
        cont = cola.Tamanio();
        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << "Codigo de barras\t\t\t\tArticulo" << std::endl;
            for (int i = 0; i < cont; i++)
            {
                std::cout << Datos[cola.peek()][1] << "\t\t\t" << Datos[cola.peek()][2] << "\t\t" << std::endl;
                cola.desencolar();
            }
        }
    }

    /**
     * Funcion que Muestra el inventario completo de los articulos de los grupos encontrados en el archivo
     * @tparam void
     * @return void
     */

    void Datos_xgrupos()
    {

        int t0, t1, t2, t3;

        t0 = clock();
        Datos = csv.readV(argv[argc-1]);

        dataO = shellSort(Datos, 0);
        int Pnum = 1;

        std::cout << "--GRUPOS DE ARTICULOS-- " << std::endl;

        std::cout << std::endl;
        std::vector<std::string> grupos;

        for (int i = 0; i < dataO.size(); i++)
        {

            std::string grupo = dataO[i][0];
            grupo.erase(std::remove(grupo.begin(), grupo.end(), '\"'), grupo.end());

            if (grupo != "\0" && grupo != "Grupo")
            {
                std::cout << Pnum << ". " << grupo << std::endl;
                grupos.push_back(grupo);
                Pnum++;
            }
        }

        grupos.push_back("FIN");

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;

        std::cout << "Ingrese el numero del grupo que desea ver: " << std::endl;

        Datos = csv.readV(argv[argc-1]);

        int n = 0;
        int pos = 0;

        int numGrupo = 0;

        std::cin >> numGrupo;

        t2 = clock();

        std::cout << std::endl;

        std::cout << "--ARTICULOS DEL GRUPO " << grupos[numGrupo - 1] << "-- " << std::endl;

        std::string grupoAUX1 = grupos[numGrupo];
        std::string grupoAUX2 = grupos[numGrupo - 1];

        grupoAUX1 = "\"" + grupoAUX1 + "\"";
        grupoAUX2 = "\"" + grupoAUX2 + "\"";

        for (int i = 1; i < Datos.size(); i++)
        {
            pos++;
            std::string DatosAUX = Datos[i][0];

            if (strcmp(DatosAUX.c_str(), grupoAUX2.c_str()) == 0)
            {
                break;
            }
        }

        for (int i = pos; i < Datos.size(); i++)

        {
            n++;
            std::string DatosAUX = Datos[i][0];
            if (strcmp(DatosAUX.c_str(), grupoAUX1.c_str()) == 0)
            {
                break;
            }
        }

        n = n - 1;

        if (numGrupo == grupos.size() - 1)
        {
            n = Datos.size() - pos;
        }

        for (int i = pos; i < n + pos; i++)
        {

            std::cout << "-----> "
                      << "Nombre del Articulo: " << Datos[i][2] << std::endl;
            std::cout << "            Codigo de barra: " << Datos[i][1] << std::endl;
            std::cout << std::endl;
            std::cout << "       --Cantidad por deposito--" << std::endl;

            for (int j = 3; j < Datos[i].size(); j++)
            {
                std::cout << "       " << Datos[0][j] << ": " << Datos[i][j] << std::endl;
            }
            std::cout << std::endl;

            // Cantidad total de productos
            int CantidadTotal = 0;

            for (int j = 3; j < Datos[i].size(); j++)
            {

                std::string cantidadStr = Datos[i][j];
                cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

                if (!cantidadStr.empty())
                {
                    CantidadTotal += std::stoi(cantidadStr);
                }
            }

            std::cout << "Cantidad total del producto: " << CantidadTotal << std::endl;
        }

        t3 = clock();

        double time2 = (double(t3 - t2) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time2 << std::endl;
    }
};
/*
-total_art_dif Cantidad total de articulos diferentes.
-total_art Cantidad total de articulos.
-min_stock [n] Listado de articulos con cantidad n o menos de stock.
-min_stock [n],[deposito] Listado de articulos con cantidad n o menos de stock segun un deposito.
-stock [nombre_articulo] El stock total del articulo ingresado como argumento.
-stock [nombre_articulo],[deposito] El stock del articulo en un deposito.
-max_Stock [n] Listado de aquellos articulos cuyo stock es igual o supera el numero n.*/
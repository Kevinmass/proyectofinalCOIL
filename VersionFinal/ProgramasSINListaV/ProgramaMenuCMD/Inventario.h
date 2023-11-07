#include <string.h>
#include <ctime>
#include "File.h"
#include "Cola/Cola.h"

/* Clase encargada de las funciones de manejo del Inventario del archivo --> Datos
 * @tparam Char -> Datos del archivo dado por el cliente --> Compocision con la clase file.h
 * @return Distintas funciones utiles para el manejo del inventario
 */
class Inventario
{
private:
    int Depositos;
    int Cantidad;
    int min;
    int max;
    int minD;
    int maxD;

public:
    // Composicion
    file csv;

    // Estructuras globales
    std::vector<std::vector<std::string>> Datos;
    std::vector<std::vector<std::string>> dataSE;
    std::vector<std::vector<std::string>> dataO;

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
        this->Depositos = 0;
        this->Cantidad = 0;
        this->min = 0;
        this->max = 0;
        this->minD = 0;
        this->maxD = 0;
        this->argc = 0;
    }

    /**
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    int GetCantidad()
    {

        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene la cantidad de productos --> total de filas
        Cantidad = Datos.size();

        return Cantidad;
    }

    /**
     * Funcion que retorna la cantidad de Depositos en el archivo
     * @tparam int
     * @return Depositos
     */
    int GetDepositos()
    {

        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene la cantidad de depositos --> total de columnas - 3 (se descuentan las columnas de grupo, codigo de barra y nombre del articulo)
        Depositos = (Datos[0].size()) - 3;

        return Depositos;
    }

    /**
     * Funciones para definir limites de stock global --> min
     * @tparam int
     * @return void
     */
    void setMinStock(int n)
    {
        min = n;
    }

    /**
     * Funciones para definir  limites de stock global --> max
     *  @tparam int
     *  @return void
     */

    void setMaxStock(int n)
    {
        max = n;
    }

    /**
     * Funciones para definir limites de stock por deposito --> min
     *  @tparam int
     *  @return void
     */

    void setMinStockD(int n)
    {
        minD = n;
    }

    /**
     * Funciones para definir limites de stock por deposito --> max
     *  @tparam int
     *  @return void
     */

    void setMaxStockD(int n)
    {
        maxD = n;
    }

    /**
     * Funciones para obtener los limites de stock global --> min
     *
     * @return int
     */

    int getMinStock()
    {
        return min;
    }

    /**
     * Funciones para obtener los limites de stock global --> max
     *
     * @return int
     */

    int getMaxStock()
    {
        return max;
    }

    /**
     * Funciones para obtener los limites de stock por deposito --> min
     *
     * @return int
     */

    int getMinStockD()
    {
        return minD;
    }

    /**
     * Funciones para obtener los limites de stock por deposito --> max
     *
     * @return int
     */

    int getMaxStockD()
    {
        return maxD;
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
            // Se calcula la mitad del vector
            int mid = l + (r - l) / 2;

            // Creamos un string aux para utilizar la funcion strcmp
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

        return -1;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    void total_art_dif()
    {
        int t0, t1;

        t0 = clock();
        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        Cantidad = Datos.size();

        // Se retorna la cantidad de articulos diferentes --> total de filas - 1 (se descuenta la fila de los nombres de las columnas)
        std::cout << "Cantidad de articulos diferentes --->" << Cantidad - 1;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << std::endl;
        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Funcion que muestre la cantidad total de articulos
     * @tparam void
     * @return void
     */

    void total_art()
    {
        int t0, t1;

        t0 = clock();

        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        int suma = 0, cont = 0, fin = 0;

        // Se obtiene el numero de columnas
        fin = Datos[0].size();

        std::string cantidadStr;

        // Se recorre el vector de vectores de string --> inicia en 1 para no contar la fila de los nombres de las columnas
        for (int i = 1; i < Datos.size(); i++)
        {

            int total = 0;

            for (int j = 3; j < fin; j++) // Comienza desde el índice 3 y llega hasta el número de depósitos --> se descuentan las columnas de grupo, codigo de barra y nombre del articulo
            {
                // Se guarda el string de la cantidad
                cantidadStr = Datos[i][j];

                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());

                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    // Se recorre el string para eliminar la comilla
                    for (int h = 0; h < strlen(cantidadStr.c_str()) - 1; h++)
                    {
                        // Se mueve el numero para eliminar la primera comilla para que funcione el stoi
                        cantidadStr[h] = cantidadStr[h + 1];
                    }
                    // Se pasa de valor char a int y se suman
                    total += std::stoi(cantidadStr);
                    suma += std::stoi(cantidadStr);
                }
            }

            std::cout << "Articulo: " << Datos[i][1] << " - Stock total: " << total << std::endl;
        }
        std::cout << std::endl;
        std::cout << "El total de productos es:  " << suma << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Listado de artículos con cantidad n o menos de stock según un depósito
     * @tparam int n numero de stock
     * @tparam int deposito numero de deposito
     * @return void
     */

    void min_stock(int n)
    {
        int t0, t1;

        t0 = clock();
        int fin = 0, auxStock = 0, cont = 0;
        std::string cantidadStr;

        // Se crea una cola para guardar las posiciones de los articulos que se encuentren en el rango
        Cola<int> cola;

        // Se crea una cola para guardar la cantidad de articulos que se encuentren en el rango
        Cola<int> colaCAN;

        // Se lee el csv
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene el numero de columnas
        fin = Datos[0].size();

        for (int i = 1; i < Datos.size(); i++)
        {

            auxStock = 0;
            for (int j = 3; j < fin; j++)
            {
                // Se guarda el string de la cantidad
                cantidadStr = Datos[i][j];
                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());
                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    // Se recorre el string para eliminar la comilla
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

                // Se encola la cantidad de articulos que se encuentren en el rango
                colaCAN.encolar(auxStock);
            }
        }
        // Se obtiene el tamaño de la cola
        cont = cola.Tamanio();
        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "----ARTICULOS A REPONER----" << std::endl;
            std::cout << std::endl;

            std::cout << "Los siguientes articulos tienen un stock menor o igual a " << n << std::endl;
            std::cout << std::endl;

            for (int i = 0; i < cont; i++)
            {
                std::cout << "[" << cola.peek() << "] --> Codigo de barra: " << Datos[cola.peek()][1] << std::endl;
                std::cout << "          Nombre del articulo: " << Datos[cola.peek()][2] << std::endl;
                std::cout << "          Cantidad total: " << colaCAN.peek() << std::endl;
                std::cout << std::endl;
                cola.desencolar();
                colaCAN.desencolar();
            }
        }

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Listado de artículos con cantidad n o menos de stock según un depósito
     * @tparam int n numero de stock
     * @tparam int deposito numero de deposito
     * @return void
     */
    void min_stock(int n, int deposito) // funciona
    {
        int t1, t0;

        t0 = clock();
        int auxStock = 0, depositoAUX = 0;
        std::string cantidadStr;

        // Se crea una cola para guardar las posiciones de los articulos que se encuentren en el rango
        Cola<int> cola;

        // Se crea una cola para guardar la cantidad de articulos que se encuentren en el rango
        Cola<int> colaCAN;

        // Se lee el csv
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene el numero de columnas --> se suma 2 para llegar al numero de deposito (arranca desde la columna 0)
        depositoAUX = deposito + 2;

        // Se recorre el vector de vectores de string
        for (int i = 1; i < Datos.size(); i++)
        {

            // Se inicializa el auxiliar en 0
            auxStock = 0;

            // Se guarda el string de la cantidad
            cantidadStr = Datos[i][depositoAUX];

            // Se eliminan los espacios en blanco
            cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());
            // Se chequea que no este vacio el string
            if (cantidadStr != "\0")
            {
                // Se transforma el string a int
                auxStock = std::stoi(cantidadStr);
            }

            // Si es vacio se le asigna 0
            if (cantidadStr.empty())
            {
                auxStock = 0;
            }

            // Se chequea si el stock es menor o igual al numero ingresado
            if (auxStock <= n)
            {
                // Los Articulos que se encuentren en el rango se encola su posicion
                cola.encolar(i);

                // Se encola la cantidad de articulos que se encuentren en el rango
                colaCAN.encolar(auxStock);
            }
        }
        int cont = cola.Tamanio();
        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "----ARTICULOS A REPONER EN EL DEPOSITO " << deposito << "----" << std::endl;
            std::cout << std::endl;

            std::cout << "Los siguientes articulos tienen un stock menor o igual a " << n << std::endl;
            std::cout << std::endl;

            for (int i = 0; i < cont; i++)
            {
                std::cout << "[" << cola.peek() << "] --> Codigo de barra: " << Datos[cola.peek()][1] << std::endl;
                std::cout << "          Nombre del articulo: " << Datos[cola.peek()][2] << std::endl;
                std::cout << "          Cantidad total: " << colaCAN.peek() << std::endl;
                std::cout << std::endl;
                cola.desencolar();
                colaCAN.desencolar();
            }
        }
        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Funcion que Muestra el inventario completo junto al grupo y nombre del articulo
     * @tparam string NombreArticulo
     * @return void
     */

    void stock(std::string NombreArticulo)
    {
        int t0, t1;

        t0 = clock();

        // Se guarda el nombre del articulo en un string auxiliar --> para mostrarlo al final
        std::string aux = NombreArticulo;

        // Quita los espacios en blanco sin perder los datos introducidos despues de teclear el espacio
        NombreArticulo.erase(std::remove_if(NombreArticulo.begin(), NombreArticulo.end(),
                                            [](char &c)
                                            {
                                                return std::isspace<char>(c, std::locale::classic());
                                            }),
                             NombreArticulo.end());
        // Se lee el csv
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene el vector de vectores de string sin espacios en la colunma 2 (nombre del articulo)
        dataSE = csv.DataSE(Datos, 2);

        // Se ordena el vector de vectores de string por nombre del articulo
        dataO = shellSort(dataSE, 2);

        int pos = 0;

        // Se busca el articulo en el vector de vectores de string ordenado --> la posicion (fila) se guarda en la variable pos
        pos = (binarySearch(dataO, 1, GetCantidad() - 1, NombreArticulo, 2));

        // Si no se encuentra el articulo se muestra un mensaje
        if (pos == -1)
        {
            std::cout << "No se encontro el articulo" << std::endl;
            return;
        }

        // Se muestra datos del articulo

        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        std::cout << std::endl;

        std::cout << "-Nombre del Articulo " << aux << " --> ENCONTRADO" << std::endl;
        std::cout << "- Codigo de barras del Articulo: " << dataSE[pos][1] << std::endl;

        // Cantidad x deposito del producto
        std::cout << std::endl;
        std::cout << "--Cantidad por deposito--" << std::endl;
        for (int i = 3; i < dataSE[pos].size(); i++)
        {
            std::cout << "Deposito " << i - 2 << ": " << dataSE[pos][i] << std::endl;
        }

        std::cout << std::endl;

        // Cantidad total de productos
        int CantidadTotal = 0;

        // Se recorre el vector de vectores de string para sumar la cantidad total de productos
        for (int i = 3; i < dataSE[pos].size(); i++)
        {

            // Se guarda el string de la cantidad
            std::string cantidadStr = dataSE[pos][i];

            // Se eliminan los espacios en blanco
            cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

            // Se chequea que no este vacio el string
            if (!cantidadStr.empty())
            {
                // Se pasa de valor char a int y se suman
                CantidadTotal += std::stoi(cantidadStr);
            }
        }

        // Se muestra la cantidad total de productos

        std::cout << "Cantidad total de productos: " << CantidadTotal << std::endl;

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
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

        // Se lee el csv
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene el vector de vectores de string sin espacios en la colunma 2 (nombre del articulo)
        dataSE = csv.DataSE(Datos, 2);

        // Se ordena el vector de vectores de string por nombre del articulo
        dataO = shellSort(dataSE, 2);

        int pos = 0;

        // Se busca el articulo en el vector de vectores de string ordenado --> la posicion (fila) se guarda en la variable pos
        pos = (binarySearch(dataO, 0, GetCantidad(), NombreArticulo, 2));

        // Si no se encuentra el articulo se muestra un mensaje
        if (pos == -1)
        {
            std::cout << "No se encontro el articulo" << std::endl;
            return;
        }

        // Se muestra datos del articulo
        std::cout << "--DATOS DEL PRODUCTO-- " << std::endl;

        std::cout << std::endl;

        std::cout << "-Nombre del Articulo " << NombreArticulo << " --> ENCONTRADO" << std::endl;
        std::cout << "-Codigo de barras del Articulo: " << dataSE[pos][1] << std::endl;

        // Cantidad del producto en x deposito
        std::cout << std::endl;
        std::cout << "-Cantidad en el deposito " << nro_deposito << " --> " << dataSE[pos][nro_deposito + 2] << std::endl;

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Listado de aquellos artículos cuyo stock es igual o supera el número n
     * @tparam int n numero de stock
     * @return void
     */

    void max_stock(int n) // funciona
    {
        int t0 = clock();
        int fin = 0, auxStock = 0, cont;
        std::string cantidadStr;

        // Se crea una cola para guardar las posiciones de los articulos que se encuentren en el rango
        Cola<int> cola;

        // Se crea cola para guardar la cantidad de articulos que se encuentren en el rango
        Cola<int> colaCAN;

        // Se lee el csv
        Datos = csv.readV(argv[argc - 1]);

        // Se obtiene el numero de columnas
        fin = Datos[0].size();

        // Se recorre el vector de vectores de string
        for (int i = 1; i < Datos.size(); i++)
        {

            // Se inicializa el auxiliar en 0
            auxStock = 0;

            for (int j = 3; j < fin; j++)
            {
                // Se guarda el string de la cantidad
                cantidadStr = Datos[i][j];

                // Se eliminan los espacios en blanco
                cantidadStr.erase(std::remove_if(cantidadStr.begin(), cantidadStr.end(), ::isspace), cantidadStr.end());

                // Se chequea que no este vacio el string
                if (cantidadStr != "\"\"")
                {
                    // Se recorre el string para eliminar la comilla
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
                // Se encola la cantidad de articulos que se encuentren en el rango
                colaCAN.encolar(auxStock);
            }
        }

        // Se obtiene el tamaño de la cola
        cont = cola.Tamanio();

        // se Muestran todos los articulos guardados
        if (cola.Tamanio() == 0)
        {
            std::cout << "No hay articulos con stock mayor o igual a " << n << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "----ARTICULOS EXCEDENTES----" << std::endl;
            std::cout << std::endl;

            std::cout << "Los siguientes articulos tienen un stock mayor o igual a " << n << std::endl;
            std::cout << std::endl;

            for (int i = 0; i < cont; i++)
            {
                std::cout << "[" << cola.peek() << "] --> Codigo de barra: " << Datos[cola.peek()][1] << std::endl;
                std::cout << "          Nombre del articulo: " << Datos[cola.peek()][2] << std::endl;
                std::cout << "          Cantidad total: " << colaCAN.peek() << std::endl;
                std::cout << std::endl;
                cola.desencolar();
                colaCAN.desencolar();
            }
        }
        int t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;
    }

    /**
     *
     * Integrantes: Sebastian Mateo Chicaiza Erazo, Juan David Erazo Unda, Kevin Massholder, Juan Ignacio Muruzabal
     * Año: 2023
     * Funcion que Muestra el inventario completo de los articulos de los grupos encontrados en el archivo
     * (Funcion mas lenta, pero con completo acceso a un grupo)
     * @tparam void
     * @return void
     *
     *
     * Nota: esta funcion utiliza la ListaV, por lo que a veces puede fallar al mostrar los datos
     */

    void Datos_xgrupos()
    {

        int t0, t1, t2, t3;

        t0 = clock();

        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        // Se ordena el vector de vectores de string por grupo
        dataO = shellSort(Datos, 0);

        // Variable para mostrar el numero de grupo
        int Pnum = 1;

        std::cout << "--GRUPOS DE ARTICULOS-- " << std::endl;

        std::cout << std::endl;

        // Vector para guardar los grupos
        std::vector<std::string> grupos;

        // Se recorre el vector de vectores de string
        for (int i = 0; i < dataO.size(); i++)
        {

            // Se guarda el string del grupo
            std::string grupo = dataO[i][0];

            // Se eliminan los espacios en blanco
            grupo.erase(std::remove(grupo.begin(), grupo.end(), '\"'), grupo.end());

            // Se chequea que no este vacio el string y que no se repita el grupo --> dato[0][0]
            if (grupo != "\0" && grupo != "Grupo")
            {
                // Se muestra el grupo
                std::cout << Pnum << ". " << grupo << std::endl;

                // Se guarda el grupo en el vector
                grupos.push_back(grupo);

                // Se aumenta el numero de grupo
                Pnum++;
            }
        }

        // Se agrega el grupo FIN para poder agregar una posicion extra al vector
        grupos.push_back("FIN");

        std::cout << std::endl;

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time << std::endl;

        int n = 0;
        int pos = 0;
        int numGrupo = 0;
        int min = 0, max = 0, minD = 0, maxD = 0;

        std::cout << "Ingrese el numero del grupo que desea ver: " << std::endl;

        std::cin >> numGrupo;

        std::cout << "Ingrese el minimo de stock y el maximo de stock por deposito: " << std::endl;

        std::cin >> minD >> maxD;

        std::cout << "Ingrese el minimo de stock y el maximo de stock del total del producto: " << std::endl;

        std::cin >> min >> max;

        // Se lee el archivo
        Datos = csv.readV(argv[argc - 1]);

        // Se definen los limites de stock
        setMinStockD(minD);
        setMaxStockD(maxD);
        setMinStock(min);
        setMaxStock(max);

        t2 = clock();

        std::cout << std::endl;

        std::cout << "--ARTICULOS DEL GRUPO " << grupos[numGrupo - 1] << "-- " << std::endl;

        std::cout << std::endl;

        // Se guarda el nombre del grupo siguiente al ingresado
        std::string grupoAUX1 = grupos[numGrupo];

        // Se guarda el nombre del grupo ingresado
        std::string grupoAUX2 = grupos[numGrupo - 1];

        // Se agregan las comillas para que funcione la funcion strcmp
        grupoAUX1 = "\"" + grupoAUX1 + "\"";
        grupoAUX2 = "\"" + grupoAUX2 + "\"";

        // Se recorre el vector de vectores de string
        for (int i = 1; i < GetCantidad(); i++)
        {
            // Se aumenta la posicion, posiciones de los articulos del grupo hasta que se tope con el siguiente al grupo ingresado --> limite inferior
            pos++;

            // Se guarda el string del grupo
            std::string DatosAUX = Datos[i][0];

            // Se comparan los grupos --> hasta que se tope con el grupo siguiente al ingresado
            if (strcmp(DatosAUX.c_str(), grupoAUX2.c_str()) == 0)
            {
                break;
            }
        }

        // Se recorre el vector de vectores de string partiendo desde el limite inferior
        for (int i = pos; i < GetCantidad(); i++)
        {
            // Se aumenta la posicion, posiciones de los articulos del grupo hasta que se tope con el siguiente al grupo ingresado --> limite superior
            n++;

            // Se guarda el string del grupo
            std::string DatosAUX = Datos[i][0];

            // Se comparan los grupos --> hasta que se tope con el grupo siguiente al ingresado
            if (strcmp(DatosAUX.c_str(), grupoAUX1.c_str()) == 0)
            {
                break;
            }
        }

        // Se disminuye en 1 la variable n para que no se pase del limite superior
        n = n - 1;

        // Condicion para el ultimo grupo, ya que no tiene grupo siguiente para definir sus limites
        if (numGrupo == grupos.size() - 1)
        {
            n = GetCantidad() - pos;
        }

        // Se muestra el numero de articulos del grupo
        int contador = 1;

        // Se recorre el vector de vectores de string partiendo desde el limite inferior hasta el limite superior + n (para que no se pase del limite superior)
        for (int i = pos; i < n + pos; i++)
        {

            // Se muestra el nombre del articulo
            std::cout << "[ " << contador << " ]"
                      << " "
                      << "Nombre del Articulo: " << Datos[i][2] << std::endl;
            contador++;
            std::cout << "            Codigo de barra: " << Datos[i][1] << std::endl;
            std::cout << std::endl;
            std::cout << "       --Cantidad por deposito--" << std::endl;

            // Se recorre el vector de vectores de string partiendo desde la columna 3 (primer deposito) hasta el numero de depositos
            for (int j = 3; j < Datos[i].size(); j++)
            {

                // Se guarda el string de la cantidad
                std::string cantidadStr = Datos[i][j];

                int aux = 0;

                // Se eliminan las comillas
                cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

                // Se chequea que no este vacio el string
                if (!cantidadStr.empty())
                {
                    // Se pasa de valor char a int
                    aux = std::stoi(cantidadStr);
                }

                // Se muestra el numero de deposito y la cantidad y su estado segun los limites de stock
                if (aux > getMinStockD() && aux < getMaxStockD())
                {
                    std::cout << "       " << Datos[0][j] << ": " << Datos[i][j] << " ---> Estado:  normal" << std::endl;
                }

                else if (aux <= getMinStockD())
                {
                    std::cout << "       " << Datos[0][j] << ": " << Datos[i][j] << " ---> Estado:  se debe reponer" << std::endl;
                }

                else if (aux >= getMaxStockD())
                {
                    std::cout << "       " << Datos[0][j] << ": " << Datos[i][j] << " ---> Estado:  Maximo alcanzado/excediendo" << std::endl;
                }
            }
            std::cout << std::endl;

            // Cantidad total de productos
            int CantidadTotal = 0;

            // Se recorre el vector de vectores de string partiendo desde la columna 3 (primer deposito) hasta el numero de depositos
            for (int j = 3; j < Datos[i].size(); j++)
            {

                // Se guarda el string de la cantidad
                std::string cantidadStr = Datos[i][j];

                // Se eliminan las comillas
                cantidadStr.erase(std::remove(cantidadStr.begin(), cantidadStr.end(), '\"'), cantidadStr.end());

                // Se chequea que no este vacio el string
                if (!cantidadStr.empty())
                {
                    // Se pasa de valor char a int y se suman
                    CantidadTotal += std::stoi(cantidadStr);
                }
            }

            // Se muestra la cantidad total de productos
            std::cout << "Cantidad total del producto: " << CantidadTotal << std::endl;

            std::cout << std::endl;

            // Se muestra el estado del producto total segun los limites de stock

            if (CantidadTotal > getMinStock() && CantidadTotal < getMaxStock())
            {
                std::cout << "Estado del producto total: normal" << std::endl;
            }

            else if (CantidadTotal <= getMinStock())
            {
                std::cout << "Estado del producto total: se debe reponer" << std::endl;
            }

            else if (CantidadTotal >= getMaxStock())
            {
                std::cout << "Estado del producto total: maximo/excediendo capacidad limite" << std::endl;
            }

            std::cout << std::endl;
        }

        t3 = clock();

        double time2 = (double(t3 - t2) / CLOCKS_PER_SEC);

        std::cout << "Tiempo de ejecucion: " << time2 << std::endl;

        std::cout << std::endl;
    }

    /**
     * Funcion menu que permite el acceso rapido a las funciones del inventario
     * (Funcion mas rapida, pero con acceso limitado a un grupo)
     * @tparam void
     * @return void
     */

    void menu_interno()
    {

        std::cout << std::endl;
        std::cout << "       ----MENU DE ACCIONES----" << std::endl;

        std::cout << std::endl;

        std::cout << "1. Cantidad total de articulos diferentes." << std::endl;
        std::cout << "2. Cantidad total de articulos." << std::endl;
        std::cout << "3. Listado de articulos con cantidad n o menos de stock." << std::endl;
        std::cout << "4. Listado de articulos con cantidad n o menos de stock segun un deposito." << std::endl;
        std::cout << "5. El stock total del articulo ingresado como argumento." << std::endl;
        std::cout << "6. El stock del articulo en un deposito." << std::endl;
        std::cout << "7. Listado de aquellos articulos cuyo stock es igual o supera el numero n." << std::endl;
        std::cout << "8. Mostrar el inventario completo de los articulos de los grupos encontrados en el archivo." << std::endl;
        std::cout << "9. Salir." << std::endl;

        std::cout << std::endl;

        std::cout << "Ingrese el numero de la opcion que desea realizar: " << std::endl;

        int opcion = 0;

        std::cin >> opcion;

        std::cout << std::endl;

        std::string nombre;
        std::string nombre2;
        int deposito = 0, n2 = 0, deposito2 = 0;

        switch (opcion)
        {
        case 1:
            total_art_dif();
            break;

        case 2:
            total_art();
            break;

        case 3:
            std::cout << "Ingrese el numero de stock: " << std::endl;
            int n;
            std::cin >> n;
            min_stock(n);
            break;

        case 4:
            std::cout << "Ingrese el numero de stock: " << std::endl;
            std::cin >> n2;
            std::cout << "Ingrese el numero de deposito: " << std::endl;
            std::cin >> deposito;
            min_stock(n2, deposito);
            break;

        case 5:
            std::cout << "Ingrese el nombre del articulo (entre comillas):   --> ejemplo: ANAFE INDUCCION SMART COOK I4" << std::endl;
            std::cout << "Nota: Si el archvo csv tiene tildes, modifique el archivos csv y quite las tildes" << std::endl;
            std::getline(std::cin >> std::ws, nombre);
            std::cout << std::endl;
            stock(nombre);
            break;

        case 6:
            std::cout << "Ingrese el nombre del articulo (entre comillas):   --> ejemplo: ANAFE INDUCCION SMART COOK I4" << std::endl;
            std::cout << "Nota: Si el archvo csv tiene tildes, modifique el archivos csv y quite las tildes" << std::endl;
            std::getline(std::cin >> std::ws, nombre2);
            std::cout << "Ingrese el numero de deposito: " << std::endl;
            std::cin >> deposito2;
            stock(nombre2, deposito2);
            break;

        case 7:
            std::cout << "Ingrese el numero de stock: " << std::endl;
            int n3;
            std::cin >> n3;
            max_stock(n3);
            break;

        case 8:

            Datos_xgrupos();

        case 9:

            break;
        }

        std::cout << std::endl;

        std::cout << "Desea realizar otra accion? (s/n)" << std::endl;

        char respuesta;

        std::cin >> respuesta;

        if (respuesta == 's')
        {
            menu_interno();
        }

        else
        {
            return;
        }
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
            std::cout << "\n***DEBUG MENU***\n\n\n"
                      << std::endl;
            std::cout << "FUNCIONES DISPONIBLES\n\n-\"total_art_dif\" Cantidad total de articulos diferentes. \n-\"total_art\" Cantidad total de articulos. \n-\"min_stock\" [n] Listado de articulos con cantidad n o menos de stock.\n-\"min_stock\" [n],[deposito] Listado de articulos con cantidad n o menos de stock segun un deposito.\n-\"stock\" [nombre_articulo] El stock total del articulo ingresado como argumento (nombre entre comillas) --> ejemplo: BANQUETA TAPIZADA COST BCO  BASE PINTADA NEGRO .\n-\"stock\" [nombre_articulo],[deposito] El stock del articulo en un deposito (nombre ).\n-\"max_Stock\" [n] Listado de aquellos articulos cuyo stock es igual o supera el numero n.\n-\"Datos_xgrupos\" Muestra el inventario completo de los articulos de los grupos encontrados en el archivo  --> sujeto a fallas, reiniciar si este fuera el caso" << std::endl;
            break;
        case 2:

            menu_interno();

        case 3:
            if (strcmp(argv[1], "total_art_dif") == 0)
            {
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
};
/*
total_art_dif Cantidad total de artículos diferentes.
-total_art Cantidad total de artículos.
-min_stock [n] Listado de artículos con cantidad n o menos de stock.
-min_stock [n],[deposito] Listado de artículos con cantidad n o menos de stock según un depósito.
-stock [nombre_articulo] El stock total del artículo ingresado como argumento.
-stock [nombre_articulo],[depósito] El stock del artículo en un depósito.
-max_Stock [n] Listado de aquellos artículos cuyo stock es igual o supera el número n.*/
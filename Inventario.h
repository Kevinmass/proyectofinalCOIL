#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "File.h"

class Inventario
{

private:
    int Depositos;
    std::string Articulos;
    int Cantidad;
    std::string Cantidadminima;
    std::string CantidadxDeposito;
    std::string Grupos;
    std::string CodigoBarra;

public:
    // Composicion
    file csv;
    std::vector<std::vector<std::string>> Datos;

    /**
     * Constructor de la clase Inventario
     * @tparam Char
     */
    Inventario(int Depositos, std::string Articulos, int Cantidad, std::string Cantidadminima, std::string CantidadxDeposito, std::string Grupos, std::string CodigoBarra)
    {
        this->Depositos = Depositos;
        this->Articulos = Articulos;
        this->Cantidad = Cantidad;
        this->Cantidadminima = Cantidadminima;
        this->CantidadxDeposito = CantidadxDeposito;
        this->Grupos = Grupos;
        this->CodigoBarra = CodigoBarra;
    }
    /**
     * Constructor por defecto de la clase Inventario
     * @tparam Char
     */
    Inventario()
    {
        this->Depositos = ' ';
        this->Articulos = ' ';
        this->Cantidad = ' ';
        this->Cantidadminima = ' ';
        this->CantidadxDeposito = ' ';
        this->Grupos = ' ';
        this->CodigoBarra = ' ';
    }

    /**
     * Funcion que retorna la cantidad de Productos en el archivo
     * @tparam int
     * @return Cantidad
     */

    int Inventario::GetCantidad()
    {

        Datos = csv.readV();

        Cantidad = (Datos.size())-1;

        return Cantidad;
    }

    /**
     * Funcion que retorna la cantidad de Depositos en el archivo
     * @tparam int
     * @return Depositos
     */
    int Inventario::GetDepositos()
    {

        Datos = csv.readV();

        Depositos = (Datos[0].size()) - 3;

        return Depositos;
    }
};
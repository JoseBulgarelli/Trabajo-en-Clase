//Clase que define los atributos y métodos de una Ventanilla.
//Las funcionalidades de esta clase son: Crear una ventanilla, agregar la cantidad de atendidos
//y cambiar el último tiquete atendido.
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Ventanilla {
public:
    int cantidadAtendidos;
    string nombre;
    string ultimoAtendido;

    Ventanilla(int cantidadAtendidos, string nombre) {
        this->cantidadAtendidos = cantidadAtendidos;
        this->nombre = nombre;
        ultimoAtendido = "N";
    }

    Ventanilla() {

    }

    ~Ventanilla() {}

    void agregarAtendido() {
        cantidadAtendidos++;
    }

    string getUltimoAtendido() {
        return ultimoAtendido;
    }

    void setUltimoAtendido(string tiquete) {
        ultimoAtendido = tiquete;
    }

    void setCantidadAtendidos(int atendidos) {
        cantidadAtendidos = atendidos;
    }

    string getNombre() {
        return nombre;
    }

    friend ostream& operator <<(ostream& os, const Ventanilla& ventanilla) {
        os << ventanilla.nombre;
        return os;
    }
};
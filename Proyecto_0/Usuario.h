//Clase que define los atributos y métodos de un Área.
//Las funcionalidades de esta clase son: Crear un usuario y agregar tiquetes atendidos.
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Usuario {
public:
    string descripcion;
    int cantidadTiquetes;
    int prioridad;

    Usuario(string descripcion, int prioridad) {
        this->descripcion = descripcion;
        this->prioridad = prioridad;
        cantidadTiquetes = 0;
    }

    Usuario() {

    }

    ~Usuario() {}

    void agregarTiquete() {
        cantidadTiquetes++;
    }

    string getDescripcion() {
        return descripcion;
    }

    int getCantidadTiquetes() {
        return cantidadTiquetes;
    }

    int getPrioridad() {
        return prioridad;
    }

    void setCantidadTiquetes(int cantidad) {
        cantidadTiquetes = cantidad;
    }

    friend ostream& operator <<(ostream& os, const Usuario& usuario) {
        os << usuario.descripcion;
        return os;
    }
};
//Clase que define los atributos y métodos de un Servicio.
//Las funcionalidades de esta clase son: Crear un servicio y agregar tiquetes atendidos.
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <string>
#include <ostream>

using std::string;
using std::ostream;

class Servicio {
public:
    string descripcion;
    int prioridad;
    string areaDescripcion;
    int cantidadTiquetes;

    Servicio(string descripcion, int prioridad, string area) {
        this->descripcion = descripcion;
        this->prioridad = prioridad;
        this->areaDescripcion = area;
        cantidadTiquetes = 0;
    }

    Servicio() {

    }

    ~Servicio() {}

    void agregarTiquete() {
        cantidadTiquetes++;
    }

    string getDescripcion() {
        return descripcion;
    }

    string getAreaDescripcion() {
        return areaDescripcion;
    }

    int getPrioridad() {
        return prioridad;
    }

    void setCantidadTiquetes(int cantidad) {
        cantidadTiquetes = cantidad;
    }

    friend ostream& operator <<(ostream& os, const Servicio& servicio) {
        os << servicio.descripcion;
        return os;
    }
};
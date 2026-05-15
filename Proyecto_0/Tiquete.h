//Clase que define los atributos y métodos de un Tiquete.
//Las funcionalidades de esta clase son: Crear un tiquete y atender ese tiquete.
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <string>
#include <time.h>
#include <ostream>

using std::string;
using std::ostream;

class Tiquete {
public:
    string nombre;
    time_t creacion;
    time_t espera;
    time_t atendido;

    Tiquete(string nombre) {
        this->nombre = nombre;
        creacion = time(0);
    }

    Tiquete() {

    }

    ~Tiquete() {}

    void atender() {
        atendido = time(0);
        espera = atendido - creacion;
    }

    time_t getEspera() {
        return espera;
    }

    friend ostream& operator <<(ostream& os, const Tiquete& tiquete) {
        os << tiquete.nombre;
        return os;
    }
};
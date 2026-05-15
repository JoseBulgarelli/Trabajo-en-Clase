//Clase que define los atributos y métodos de un Área.
//Las funcionalidades de esta clase son: Agregar ventanas, tiquetes y servicios al área 
//y ver sus ventanas.
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <stdexcept>
#include <string>
#include <ostream>
#include "List.h"
#include "LinkedList.h"
#include "PriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "Ventanilla.h"
#include "Tiquete.h"
#include "Servicio.h"

using std::string;
using std::to_string;
using std::runtime_error;
using std::ostream;

class Area {
public:
    List<Servicio>* servicios;
    List<Ventanilla>* ventanillas;
    PriorityQueue<Tiquete>* tiquetes;
    List<Tiquete>* tiquetesAtendidos; // Hijo estoy llando
    int cantidadVentanillas;
    int cantidadTiquetesAtendidos; // Hijo estoy crineado
    int cantidadTiquetes; // Son im crine
    string descripcion;
    string codigo;

    Area(string descripcion, string codigo, int cantidadVentanillas) { //Crea un objeto Area con su descripción y el código para el tiquete.
        this->descripcion = descripcion;
        this->codigo = codigo;
        cantidadTiquetesAtendidos = 0;
        cantidadTiquetes = 0;
        ventanillas = new LinkedList<Ventanilla>();
        this->tiquetes = new HeapPriorityQueue<Tiquete>();
        tiquetesAtendidos = new LinkedList<Tiquete>();
        servicios = new LinkedList<Servicio>();
        cambiarCantidadVentanillas(cantidadVentanillas);
    }

    Area() {} //Crea un objeto vacío.

    ~Area() { //Destrulle el objeto Area.
        // RIP
    }

    void mostrarVentanillas() { //Muestra todas las ventanas de un Area.
        ventanillas->print();
    }

    void cambiarCantidadVentanillas(int cantidad) { //Agrega la cantidad de ventanas escogidas.
        if (cantidad <= 0)
            throw runtime_error("Cantidad de ventanas fuera de rango.");
        cantidadVentanillas = cantidad;
        ventanillas->clear();
        ventanillas->goToStart();
        Ventanilla ventanilla;
        for (int i = 1; i <= cantidad; i++) {
            ventanilla = Ventanilla(0, codigo + to_string(i));
            ventanillas->append(ventanilla);
        }
    } //Cambiar el codigo de aqui para que primero copie las ventanillas de la lista y luego agregue nuevas (Asi no se pierden los atendidos)

    string getDescripcion() {
        return descripcion;
    }

    Ventanilla getVentanilla(int pos) {
        return ventanillas->trueGetElement(pos);
    }

    Servicio getServicio(int pos) {
        return servicios->trueGetElement(pos);
    }

    List<Servicio>* getServicios() {
        return servicios;
    }

    string getCodigo() {
        return codigo;
    }

    int getCantidadTiquetes() {
        return tiquetes->getSize();
    }

    int getCantidadTiquetesAtendidos() {
        return cantidadTiquetesAtendidos;
    }

    int getCantidadVentanillas() {
        return cantidadVentanillas;
    }

    int getCantidadServicios() {
        return servicios->getSize();
    }

    bool ventanillaExiste(string nombre) {
        ventanillas->goToStart();
        for (int i = 0; i < cantidadVentanillas; i++) {
            if (ventanillas->getElement().getNombre() == nombre)  // Faltaba el next() (creo????)
                return true;
            if (i + 1 != cantidadVentanillas)
                ventanillas->next();
        }
        ventanillas->goToStart();
        return false;
    }

    int posicionVentanilla(string nombre) {
        ventanillas->goToStart();
        for (int i = 0; i < cantidadVentanillas; i++) {
            if (ventanillas->getElement().nombre == nombre)
                return i;
            if (i + 1 != cantidadVentanillas)
                ventanillas->next();
        }
    }

    void agregarTiquete(Tiquete tiquete, int prioridad) {
        cantidadTiquetes++;
        tiquetes->insert(tiquete, prioridad);
    }

    void atenderTiquete(string ventanilla) {
        cantidadTiquetesAtendidos++;
        ventanillas->goToStart();
        Ventanilla yoinkySploinky;
        for (int i = 0; i < ventanillas->getSize(); i++) {
            if (ventanillas->getElement().nombre == ventanilla) {
                yoinkySploinky = ventanillas->getElement();
                yoinkySploinky.setUltimoAtendido(tiquetes->min().nombre);
                yoinkySploinky.agregarAtendido();
                break;
            }
            ventanillas->next();
        }
        ventanillas->setElement(yoinkySploinky);
        Tiquete T = tiquetes->removeMin();
        T.atender();
        tiquetesAtendidos->append(T);
    }

    friend ostream& operator <<(ostream& os, const Area& area) {
        os << area.descripcion;
        return os;
    }
};
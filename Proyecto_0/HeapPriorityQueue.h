//Clase que define los atributos y métodos de un Heap con prioridad.
//Las funcionalidades de esta clase son: Agregar elementos al Heap, eliminar elementos del Heap,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"
#include "Pair.h"
#include "MinHeap.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
	MinHeap<Pair<int, E>>* pairs;

public:
	HeapPriorityQueue(int max = DEFAULT_MAX) { //Crea un objeto de Min Heap Priority.
		pairs = new MinHeap<Pair<int, E>>(max);
	}
	~HeapPriorityQueue() { //Destruye el objeto.
		clear();
		delete pairs;
	}
	void insert(E element, int priority) { //Agrega un elemento al Heap.
		Pair<int, E> p(priority, element);
		pairs->insert(p);
	}
	E min() { //Regresa el valor minimo en el Heap.
		Pair<int, E> p = pairs->first();
		return p.value;
	}
	E remove(int pos) {
		Pair<int, E> p = pairs->remove(pos);
		return p.value;
	}
	E removeMin() { //Elimina el valor minimo en el Heap.
		Pair<int, E> p = pairs->removeFirst();
		return p.value;
	}
	void clear() { //Limpia el objeto.
		pairs->clear();
	}
	int getSize() { //Regresa el tamaño del Heap.
		return pairs->getSize();
	}
	bool isEmpty() { //Regresa si el Heap esta vacío.
		return pairs->isEmpty();
	}
	void print() { //Imprime los contenidos del Heap.
		pairs->print();
	}
	E getElement(int pos) {
		Pair<int, E> p = pairs->getElement(pos);
		return p.value;
	}
};
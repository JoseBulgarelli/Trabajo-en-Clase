//Clase que define los atributos y métodos de un Min Heap.
//Las funcionalidades de esta clase son: Agregar elementos al Heap, eliminar elementos del Heap,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <stdexcept>
#include <iostream>
#include "Util.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class MinHeap {
private:
	E* elements;
	int size;
	int max;

	int leftChild(int pos) { //Regresa la posicion del hijo izquierdo.
		return 2 * pos + 1;
	}
	int rightChild(int pos) { //Regresa la posicion del hijo derecho.
		return 2 * pos + 2;
	}
	int parents(int pos) { //Regresa la posicion de los padres.
		return (pos - 1) / 2;
	}
	void swap(int pos1, int pos2) { //Cambia los elementos en 2 posiciones.
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}
	bool isLeaf(int pos) { //Regresa si una posicion es una hoja.
		return leftChild(pos) >= size;
	}
	int minChild(int pos) { //Regresa la posicion del hijo menor.
		if (rightChild(pos) < size && elements[rightChild(pos)] < elements[leftChild(pos)])
			return rightChild(pos);
		return leftChild(pos);
	}
	void cascadeUp(int pos) { //Mueve el elemento hasta su posición más alta.
		while (pos != 0 && elements[pos] < elements[parents(pos)]) {
			swap(pos, parents(pos));
			pos = parents(pos);
		}
	}
	void cascadeDown(int pos) { //Mueve el elemento hasta su posición más baja.
		while (!isLeaf(pos) && elements[minChild(pos)] < elements[pos]) {
			int minPos = minChild(pos);
			swap(pos, minPos);
			pos = minPos;
		}
	}

public:
	MinHeap(int max = DEFAULT_MAX) { //Crea un objeto MinHeap.
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~MinHeap() { //Destruye el objeto MinHeap.
		clear();
		delete[] elements;
	}
	void insert(E element) { //Inserta un elemento en el MinHeap.
		if (size == max)
			throw runtime_error("Heap is full.");
		elements[size] = element;
		cascadeUp(size);
		size++;
	}
	E first() { //Regresa el elemento en la raíz del MinHeap.
		if (size == 0)
			throw runtime_error("Head is empty.");
		return elements[0];
	}
	E removeFirst() { //Elimina el elemento en la raíz del MinHeap.
		return remove(0);
	}
	E remove(int pos) { //Elimina un elemento en la posición del MinHeap.
		if (size == 0)
			throw runtime_error("Heap is empty.");
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of range.");
		swap(pos, size - 1);
		size--;
		cascadeDown(pos);
		return elements[size];
	}
	E getElement(int pos) {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of range.");
		return elements[pos];
	}
	void clear() { //Borrado lógico del MinHeap.
		size = 0;
	}
	int getSize() { //Regresa el tamaño del MinHeap.
		return size;
	}
	bool isEmpty() { //Revisa si el MinHeap esta vacío.
		return size == 0;
	}
	void print() { //Imprime los datos en el MinHeap.
		cout << "[";
		for (int i = 0; i < size; i++) {
			if (i == size - 1)
				cout << elements[i];
			else
				cout << elements[i] << ", ";
		}
		cout << "]" << endl;
	}
};
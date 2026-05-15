//Clase que define los atributos y métodos un Linked Stack.
//Las funcionalidades de esta clase son: Agregar elementos al Stack, eliminar elementos del Stack,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#pragma once

#include <stdexcept>
#include <iostream>
#include "Node.h"
#include "Stack.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedStack : public Stack<E> {
private:
	Node<E>* top;
	int size;

public:
	LinkedStack() { //Crea un objeto LinkedStack.
		size = 0;
		top = nullptr;
	}

	~LinkedStack() { //Elimina el objeto.
		clear();
	}

	void push(E element) { //Agrega un elemento al Stack.
		top = new Node<E>(element, top);
		size++;
	}

	E pop() { //Quita un objeto del Stack.
		if (size == 0)
			throw runtime_error("Stack is empty.");
		E result = top->element;
		Node<E>* temp = top;
		top = top->next;
		delete temp;
		size--;
		return result;
	}

	E topValue() { //Regresa el elemento en la cima del Stack.
		if (size == 0)
			throw runtime_error("Stack is empty.");
		return top->element;
	}

	void clear() { //Borra los elementos del Stack.
		Node<E>* temp;
		for (int i = 0; i < size; i++) {
			temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	bool isEmpty() { //Regresa si el Stack esta vacío.
		return size == 0;
	}

	int getSize() { //Regresa el tamaño del Stack.
		return size;
	}

	void print() { //Imprime los elementos del Stack.
		Node<E>* temp = top;
		cout << "[";
		for (int i = 0; i < size; i++) {
			if (i == size - 1)
				cout << temp->element;
			else
				cout << temp->element << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};
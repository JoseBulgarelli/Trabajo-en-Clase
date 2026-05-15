//Clase que define los atributos de un Nodo.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

template <typename E>
class Node {
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next = nullptr) { //Crea un Nodo con un elemento y con un puntero next (opcional).
		this->element = element;
		this->next = next;
	}
	Node(Node<E>* next = nullptr) { //Crea un nodo con un puntero next (opcional).
		this->next = next;
	}
};
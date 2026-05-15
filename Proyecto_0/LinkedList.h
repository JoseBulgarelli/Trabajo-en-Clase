//Clase que define los atributos y métodos un Linked List.
//Las funcionalidades de esta clase son: Agregar elementos al List, eliminar elementos del List,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedList : public List<E> {
private:
	Node<E>* head;
	Node<E>* current;
	Node<E>* tail;
	int size;
public:
	LinkedList() {
		head = current = tail = new Node<E>();
		size = 0;
	}
	~LinkedList() {
		clear();
		delete head;
	}
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = tail->next;
		size++;
	}
	void append(E element) {
		tail->next = new Node<E>(element);
		tail = tail->next;
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element");
		E result = current->next->element;
		Node<E>* temp = current->next;
		current->next = temp->next;
		delete temp;
		size--;
		if (current->next == nullptr)
			tail = current;
		return result;
	}
	void clear() {
		while (head->next != nullptr) {
			current = head->next;
			head->next = current->next;
			delete current;
		}
		tail = current = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index is out of bounds.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current)
				temp = temp->next;
			current = temp;
		}
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail;
	}
	int getPos() {
		int pos = 0;
		Node<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
	void print() {
		Node<E>* temp = head->next;
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

	E trueGetElement(int pos) {
		goToPos(pos);
		return getElement();
	}

	E trueRemove(int pos) {
		goToPos(pos);
		return remove();
	}

	void swap(int pos1, int pos2) {
		E temp1 = trueGetElement(pos1);
		E temp2 = trueGetElement(pos2);
		setElement(temp1);
		goToPos(pos1);
		setElement(temp2);
	}

	bool isEmpty() {
		return size == 0;
	}
};
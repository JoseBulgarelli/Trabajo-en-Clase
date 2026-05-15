//Clase abstracta que define los métodos de un PriorityQueue.
//Las funcionalidades de esta clase son: Agregar elementos al Queue, eliminar elementos del Queue,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

template <typename E>
class PriorityQueue {
public:
	PriorityQueue() {} //Crea un objeto Priority Queue.
	PriorityQueue(const PriorityQueue<E>&) = delete; //Evita que se pueda copiar los datos de un Priority Queue a otro.
	void operator=(const PriorityQueue<E>&) = delete; //Evita que se pueda copiar los datos de un Priority Queue a otro.

	virtual ~PriorityQueue() {} //Destruye el objeto.
	virtual void insert(E element, int priority) = 0; //Agrega un elemento con prioridad.
	virtual E min() = 0; //Revisa el elemento con mayor prioridad.
	virtual E remove(int pos) = 0; // Empanadas
	virtual E removeMin() = 0; //Elimina el elemento con mayor prioridad.
	virtual void clear() = 0; //Borra los datos del objeto.
	virtual int getSize() = 0; //Regresa el tamaño del Priority Queue.
	virtual bool isEmpty() = 0; //Revisa si el Priority Queue esta vacío.
	virtual void print() = 0; //Imprime los datos del Priority Queue.
	virtual E getElement(int pos) = 0; // Enchiladas
};
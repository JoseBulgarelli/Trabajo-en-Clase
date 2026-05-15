//Clase abstracta que define los métodos de un Stack.
//Las funcionalidades de esta clase son: Agregar elementos al Stack, eliminar elementos del Stack,
//ver sus elementos y sus datos.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

template <typename E>

class Stack {
public:
	Stack() {} //Crea un objeto Stack.
	Stack(const Stack<E>& other) = delete; //Evita que se pueda copiar los datos de un Stack a otro.
	void operator=(const Stack<E>& other) = delete; //Evita que se pueda copiar los datos de un Stack a otro.
	virtual ~Stack() {} //Destruye el objeto.

	virtual void push(E element) = 0; //Agrega un elemento.
	virtual E pop() = 0; //Quita un elemento.
	virtual E topValue() = 0; //Muestra el elemento en la cima del Stack.
	virtual void clear() = 0; //Borra los elementos del objeto.
	virtual bool isEmpty() = 0; //Regresa si el Stack esta vacío.
	virtual int getSize() = 0; //Regresa el tamaño del Stack.
	virtual void print() = 0; //Imprime los datos del Stack.
};
//Clase que define los atributos y métodos un Pair.
//Las funcionalidades de esta clase son: Comparar un objeto Pair a otro objeto.
//Creadores: El profe, Jose Alberto Bulgarelli e Ignacio Castillo.
#pragma once

#include <iostream>

using std::ostream;

template <typename K, typename V>
class Pair {
public:
	K key;
	V value;

	Pair() {}
	Pair(K key) { //Crea un Pair con una llave.
		this->key = key;
	}
	Pair(K key, V value) { //Crea un Pair con una llave y un valor.
		this->key = key;
		this->value = value;
	}
	bool operator==(const Pair<K, V>& other) { //Compara Pair==E.
		return key == other.key;
	}
	bool operator!=(const Pair<K, V>& other) { //Compara Pair!=E.
		return key != other.key;
	}
	bool operator<(const Pair<K, V>& other) { //Compara Pair<E.
		return key < other.key;
	}
	bool operator<=(const Pair<K, V>& other) { //Compara Pair<=E.
		return key <= other.key;
	}
	bool operator>(const Pair<K, V>& other) { //Compara Pair>E.
		return key > other.key;
	}
	bool operator>=(const Pair<K, V>& other) { //Compara Pair=>E.
		return key >= other.key;
	}
	friend ostream& operator<<(ostream& os, const Pair<K, V>& p) { //Dicta como se escribe un Pair en consola.
		os << "(" << p.key << ", " << p.value << ")";
		return os;
	}
};
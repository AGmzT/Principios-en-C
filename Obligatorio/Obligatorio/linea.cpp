/* 41603546 */ // sustituiir con los 7 dígitos de la cédula
/*
 Modulo que implemente el archivo linea.h
 
 */

//#include "../include/linea.h"
#include "linea.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* Cadena;

struct _rep_linea {
	char caracter;
	_rep_linea* siguiente;
	_rep_linea* anterior;
	_rep_linea * ultimo; //el ultimo caracter de la linea
	int posicion;// posicion que ocupa en la linea
};

typedef _rep_linea* TLinea;
//
//Pos-condicion: Crea una linea vacía
TLinea createLine() {
	TLinea linea = new _rep_linea;
	linea->caracter = '\0';
	linea->siguiente = NULL;
	linea->anterior = NULL;
	linea->ultimo = NULL;
	linea->posicion = 0;
	return linea;
}

//pos-condicion: Retorna true si la linea "linea" es vacia
bool isEmptyLine(TLinea linea) {
	return (linea->siguiente == linea);
}

//pre-condicion: linea != NULL
//Inserta el caracter letra al inicio de la linea.
void insertCharLine(char letra, TLinea& linea) {
	TLinea nueva = new _rep_linea;
	if (linea->siguiente == NULL) {
		linea->ultimo = nueva;
		nueva->siguiente = NULL;
	}
	else {
		nueva->siguiente = linea->siguiente;
		nueva->ultimo = linea->ultimo;
		linea->siguiente->anterior = nueva;
		TLinea iter = nueva->siguiente;
		while (iter != NULL) {
			iter->posicion++;
			iter = iter->siguiente;
		}
		iter = NULL;
		delete iter;
	}
	nueva->anterior = linea;
	linea->siguiente = nueva;
	nueva->caracter = letra;
	nueva->posicion = 1;
}

//pre-condición linea != NULL
//Retorna el primer caracter de la linea "linea"
char firstCharLine(TLinea linea) {
	return linea->caracter;
}

//pre-condicion linea !=NULL
//Retorna un puntero a al siguiente nodo de "linea"
TLinea nextLine(TLinea linea) {
	return linea->siguiente;
}

//Retorna la cantidad de elementos que tiene la linea "linea"
int countNodesLine(TLinea linea) {
	return linea->ultimo->posicion;
}

//pre-condicion: linea != NULL
//pos-condicion: Elimina el primer nodo de la linea "linea"
void deleteFirstChar(TLinea& linea) {
	TLinea iter = linea->siguiente;
	if (iter->siguiente == NULL) {
		linea->siguiente = NULL;
		linea->ultimo = NULL;
	}
	else {
		TLinea aux = iter;
		while (aux->siguiente != NULL) {
			aux->posicion--;
			aux = aux->siguiente;
		}
		aux = NULL;
		delete aux;
		linea->siguiente = iter->siguiente;
		iter->siguiente->anterior = linea;
	}
	delete iter;
}

//pre-condicion: linea != NULL
//pos-condicion: Elimina el ultimo nodo de la linea "linea"
void deleteLastChar(TLinea& linea) {
	TLinea aux = linea->ultimo;
	linea->ultimo = aux->anterior;
	aux->anterior->siguiente = NULL;
	delete aux;
	aux = NULL;
}

//Pos-condicion: Destruye toda la memoria utilizada por linea
void destroyLine(TLinea& linea) {
	if (linea->siguiente == NULL) delete linea;
	else {
		while (linea->siguiente != NULL) {
			deleteLastChar(linea);
		}
		delete linea;
	}
}
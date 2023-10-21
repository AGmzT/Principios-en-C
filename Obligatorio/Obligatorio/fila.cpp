/* 4160354 */ // sustituiir con los 7 dígitos de la cédula
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//#include "../include/fila.h"
//#include "../include/linea.h"
#include "fila.h"
#include "linea.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* Cadena;

struct _rep_fila {
	TLinea linea; //puntero al primer caracter de la linea
	int cant_caracteres; // cantidad de caracteres de linea = posicion del ultimo caracter
	_rep_fila* siguiente;
};

typedef struct _rep_fila* TFila;

//Pos-condición crea una fila vacía.
TFila createRow() {
	TFila fila = new _rep_fila;
	fila->siguiente = NULL;
	fila->linea = NULL;
	fila->cant_caracteres = 0;
	return fila;
}

//Pos-Condición retorna true si la fila es vacía.
bool isEmptyRow(TFila fila) {
	return (fila->siguiente == NULL);
}

//Pos-Condición Inserta una nueva fila al principio de "fila"
void insertRow(TFila& fila, TLinea linea) {
	TFila nueva = new _rep_fila;
	if (fila->siguiente == NULL) {
		nueva->siguiente = NULL;
	}
	else {
		nueva->siguiente = fila->siguiente;
	}
	fila->siguiente = nueva;
	nueva->linea = linea;
	nueva->cant_caracteres = countNodesLine(linea);
}

//pre-condicion: fila !=NULL
//pos-condicion: retorna un puntero al primer nodo de la fila "fila"
TLinea headRow(TFila fila) {
	return fila->linea;
}

//pre-condicion: fila !=NULL
//pos-condicion: Retorna un puntero al siguente elemento de la fila "fila"
TFila nextRow(TFila fila) {
	return fila->siguiente;
}

//pre-condicion: fila != NULL
//elimina el ultimo nodo de la fila "fila"
void deleteFirstRow(TFila& fila) {
	TFila iter = fila;
	TFila aux = fila->siguiente;
	while (aux->siguiente != NULL) {
		iter = iter->siguiente;
		aux = aux->siguiente;
	}
	TLinea linea = aux->linea;
	destroyLine(linea);
	iter->siguiente = NULL;
	iter = NULL;
	delete aux;
	aux = NULL;
}

//Elimina toda la memoria de la fila "fila"
void deleteRows(TFila& fila) {
	if (fila->siguiente == NULL) delete fila;
	else {
		while (fila->siguiente != NULL) {
			deleteFirstRow(fila);
		}
		delete fila;
	}
}

//Pos-Condición modifica el primer elemento de la fila "fila" agregando
// los caracteres al inicio del primer elemento "linea" de la fila.
void modifyRow(TFila& fila, Cadena caracteres) {
	int largo = static_cast<int>(strlen(caracteres));
	TLinea linea = headRow(fila);
	insertCharLine(' ', linea);
	for (int i = largo - 1; i >= 0; i--) {
		insertCharLine(caracteres[i], linea);
	}
	fila->linea = linea;
}
/* 41603546 */ // sustituiir con los 7 dígitos de la cédula

//#include "../include/archivo.h"
//#include "../include/linea.h"

#include "archivo.h"
#include "linea.h"
#include "fila.h"


//#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Representación de 'archivo'.
// Se debe definir en 'archivo.cpp'.
// struct _rep_archivo;
// Declaración del tipo 'TArchivo'

struct _rep_archivo {
	Cadena nombre;
	Cadena extension;
	bool writePermission;
	_rep_fila* fila;
};

typedef struct _rep_archivo* TArchivo;

//Crea un archivo vacío con nombre nombreArchivo, extensión extension y con permiso de lectura/escritura
//El archivo no contiene filas.
TArchivo createEmptyFile(Cadena nombreArchivo, Cadena extension) {
	TArchivo nuevo = new _rep_archivo;
	nuevo->nombre = new char[strlen(nombreArchivo) + 1];
	strcpy(nuevo->nombre, nombreArchivo);
	nuevo->extension = new char[strlen(extension) + 1];
	strcpy(nuevo->extension, extension);
	nuevo->writePermission = true;
	nuevo->fila = createRow();
	return nuevo;
}

//Retorna un puntero a un array con el nombre del archivo "archivo"
char* getFileName(TArchivo archivo) {
	size_t largoNomb = strlen(archivo->nombre);
	size_t largoExt = strlen(archivo->extension);
	Cadena nombreCompleto = new char[largoNomb + 1 + largoExt];
	strcpy(nombreCompleto, archivo->nombre);
	nombreCompleto[largoNomb] = '.';
	strcpy(nombreCompleto + largoNomb + 1, archivo->extension);

	return nombreCompleto;
}

//Retorna true si archivo tiene permiso de escritura
bool haveWritePermission(TArchivo archivo) {
	return archivo->writePermission;
}

//retorna true si archivo no tiene filas;
bool isEmptyFile(TArchivo archivo) {
	TFila fila = archivo->fila;
	return isEmptyRow(fila);
}

//Retorna un puntero a la primer Fila de archivo
TLinea getFirstRow(TArchivo archivo) {
	return headRow(archivo->fila);
}

//pos-condición: Retorna un puntero a la linea de la primer fila del archivo "archivo"
TLinea getFirstLine(TArchivo archivo) {
	return headRow(archivo->fila);
}


//Retorna un puntero a la siguiente Fila de archivo
TLinea getNextRow(TArchivo archivo) {
	return headRow(nextRow(archivo->fila));
}

//Retorna retorna un puntero a la primer fila del archivo "archivo"
TFila firstRowFile(TArchivo archivo) {
	return archivo->fila;
}

//Retorna la cantidad de Fila que tiene el archivo "archivo"
int getCountRow(TArchivo archivo) {
	int contador = 0;
	TFila aux = firstRowFile(archivo);
	while (aux != NULL) {
		contador++;
		aux = nextRow(aux);
	}
	aux = NULL;
	return contador;
}

//Retorna la cantidad de caracteres que tiene el archvio "archivo"
int getCountChars(TArchivo archivo) {
	int cantidad_Caract = 0;
	TFila iter = firstRowFile(archivo);
	while (iter != NULL) {
		TLinea aux = headRow(iter);
		if (aux != NULL) {
			cantidad_Caract = cantidad_Caract + countNodesLine(aux);
		}
		aux = NULL;
		iter = nextRow(iter);
	}
	iter = NULL;
	return cantidad_Caract;
}

//imprime la Linea del archivo indicada por "numero_linea"
//pre-condición el archivo tiene por lo menos numero_linea de lineas
void printLineFile(TArchivo archivo, int numero_linea) {
	TFila iter = archivo->fila;
	for (int i = 1; i < numero_linea; i++) {
		iter = nextRow(iter);
	}
	TLinea aux = headRow(iter);
	while (aux != NULL) {
		if (firstCharLine(aux) != '\0')	printf("%c", firstCharLine(aux));
		aux = nextLine(aux);
	}
	printf("\n");
	aux = NULL;
	iter = NULL;
}

//Elimina los cant cantidad de caracteres finales del "archivo"
//En caso que el archivo tenga menos caracteres los elimina a todos
void deleteCharterFile(TArchivo& archivo, int cant) {
	int borrar = cant;
	while (borrar > 0) {
		TFila iterFila = nextRow(archivo->fila);
		TFila aux = archivo->fila;
		while (iterFila != NULL && !isEmptyRow(iterFila)) {
			iterFila = nextRow(iterFila);
		}
		TLinea iterLinea = headRow(iterFila);
		if (borrar < countNodesLine(iterLinea)) {
			for (int i = borrar; i > 0; i--) {
				deleteLastChar(iterLinea);
			}
			borrar = 0;
		}
		else {
			borrar = borrar - countNodesLine(iterLinea);
			deleteFirstRow(aux);
		}
	}
}

//Cambia el nombre del archivo "archivo" por nuevoNombre
void setName(TArchivo& archivo, Cadena nuevoNombre) {
	archivo->nombre = nuevoNombre;
}

//Cambia la extension del "archivo" por nuevoNombre
void setExtension(TArchivo& archivo, Cadena nuevaExtension) {
	archivo->extension = nuevaExtension;
}

//Inserta el texto "texto" como una nueva fila al comienzo del archivo 
void insertChartsNewRow(TArchivo& archivo, Cadena texto) {
	TFila fila = archivo->fila;
	TLinea nuevaLinea = createLine();
	int largo = static_cast<int>(strlen(texto));
	for (int i = (largo - 1); i > -1; i--) {
		insertCharLine(texto[i], nuevaLinea);
	}
	insertRow(fila, nuevaLinea);
}

//pre-condicion El archivo tiene por lo menos una fila
//Inserta el texto "texto" al inicio de la primer fila del archivo
void insertChartsFirstRow(TArchivo& archivo, Cadena texto) {
	int largo = static_cast<int>(strlen(texto));
	TLinea linea = getNextRow(archivo);
	for (int i = largo - 1; i >= 0; i--) {
		insertCharLine(texto[i], linea);
	}
}

//si valor == true se le asigna el permiso de escritura de "archivo"
//si valor == false se le quita el permiso de escritura de "archivo"
//pre-condicion archivo !=NULL
void setWritePermission(TArchivo& archivo, bool valor) {
	archivo->writePermission = valor;
}

//elimina toda la memoria utilizada por "archivo"
void destroyFile(TArchivo& archivo) {
	TFila fila = firstRowFile(archivo);
	deleteRows(fila);
	delete[] archivo->nombre;
	delete[] archivo->extension;
	delete archivo;
}

/* 41603546 */ // sustituiir con los 7 dígitos de la cédula

//#include "../include/linea.h"
//#include "../include/fila.h"
//#include "../include/directorio.h"
#include "linea.h"
#include "fila.h"
#include "directorio.h"
#include "archivo.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


using namespace std;

struct archivoLista {
	TArchivo archivo;
	archivoLista* siguiente;
};

typedef struct archivoLista* ListaArchivo;

struct _rep_directorio {
	Cadena nombre;
	ListaArchivo listaArchivos;
	_rep_directorio* hermano;
	_rep_directorio* hijo;
};

typedef struct _rep_directorio* TDirectorio;

//Crea el directorio de nombre Raíz del filesystem 
TDirectorio createRootDirectory() {
	TDirectorio raiz = new _rep_directorio;
	raiz->nombre = new char[strlen("Raiz") + 1];
	strcpy(raiz->nombre, "Raiz");
	raiz->listaArchivos = new archivoLista;// esta es la celda dummy
	raiz->listaArchivos->archivo = NULL;
	raiz->listaArchivos->siguiente = NULL;
	raiz->hermano = NULL;
	raiz->hijo = NULL;
	return raiz;
}

//retorna true si el directorio "directorio" no tiene archivos
bool isEmptyDirectory(TDirectorio directorio) {
	if (directorio->listaArchivos->siguiente == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//retorna true si el archivo de nombre "nombreArchivo existe en el directorio "directorio"
bool existFileDirectory(TDirectorio directorio, Cadena nombreArchivo) {
	bool res = false;
	if (!isEmptyDirectory(directorio)) {
		ListaArchivo lista = directorio->listaArchivos->siguiente;
		while (lista != NULL && res == false) {
			if (0 == strcmp(getFileName(lista->archivo), nombreArchivo)) res = true;
			lista = lista->siguiente;
		}
		lista = NULL;
	}
	return res;
}

//pre-condicion existe el archivo de nombre nombreArchivo en el directorio "directorio"
//pos-condicion: retorna un puntero al archivo de nombre "nombreArchivo"
TArchivo getFileDirectory(TDirectorio directorio, Cadena nombreArchivo) {
	ListaArchivo lista = directorio->listaArchivos->siguiente;
	TArchivo res = lista->archivo;
	while (lista != NULL) {
		if (lista->archivo != NULL && 0 == strcmp(getFileName(lista->archivo), nombreArchivo)) {
			res = lista->archivo;
		}
		lista = lista->siguiente;
	}
	lista = NULL;
	return res;
}

//pre-condicion: No existe en directorio un archivo de nombre "nombreArchivo"
//crea un archivo vacio con nombre nombreArchivo y permiso de lectura/escritura
void createFileInDirectory(TDirectorio& directorio, Cadena nombreArchivo) {
	ListaArchivo nuevo = new archivoLista;
	char delimitador = '.';
	Cadena	nombre = new char;
	nombre = strtok(nombreArchivo, &delimitador);
	Cadena extension = new char;
	extension = strtok(nullptr, &delimitador);
	nuevo->archivo = createEmptyFile(nombre, extension);
	if (directorio->listaArchivos->siguiente == NULL) {
		directorio->listaArchivos->siguiente = nuevo;
	}
	else {
		ListaArchivo aux = directorio->listaArchivos;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
		aux = NULL;
	}
	nuevo->siguiente = NULL;

}

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: inserta una nueva fila al comienzo del archivo nombreArchivo conteniendo los chars texto
void insertTextFile(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto) {
	TArchivo  archivo = getFileDirectory(directorio, nombreArchivo);
	insertChartsNewRow(archivo, texto);
}

//pre condicion: el archivo nombreArchivo existe en directorio
//pos-condicion: agrega al comienzo de la primera fila del archivo de nombre nombreArchivo los caracteres de texto
//desplazando los caracteres existentes hacia la derecha
void insertCharsFileFirstLine(TDirectorio& directorio, Cadena nombreArchivo, Cadena texto) {
	TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
	insertChartsFirstRow(archivo, texto);

}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina el archivo del directorio "directorio" y toda la memoria utilizada por este.
void deleteFileDirectory(TDirectorio& directorio, Cadena nombreArchivo) {
	ListaArchivo aux = directorio->listaArchivos;
	TArchivo archivoBorrar = getFileDirectory(directorio, nombreArchivo);
	while (aux->siguiente->archivo != archivoBorrar) {
		aux = aux->siguiente;
	}
	ListaArchivo punteroBorrar = aux->siguiente;
	destroyFile(punteroBorrar->archivo);
	aux->siguiente = punteroBorrar->siguiente;
	delete punteroBorrar;
	aux = NULL;
}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: elimina los "cantidad" caracteres finales del archivo nombreArchivo
void deleteCharsFile(TDirectorio& directorio, Cadena nombreArchivo, int cantidad) {
	TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
	deleteCharterFile(archivo, cantidad);
}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: le setea el permiso de escritura al archivo de nombre nombreArchivo
void setFilePermission(TDirectorio& directorio, Cadena nombreArchivo, bool permisoEscritura) {
	TArchivo archivo = getFileDirectory(directorio, nombreArchivo);
	setWritePermission(archivo, permisoEscritura);
}

//pre-condicion: existe el archivo de nombre "nombreArchivo" en el directorio "directorio"
//pos-condicion: imprime el contenido del archivo "nombreArchivo"
void printFile(TDirectorio& directorio, Cadena nombreArchivo) {
	TArchivo  archivo = getFileDirectory(directorio, nombreArchivo);
	int cantFilas = getCountRow(archivo);
	for (int i = 2; i <= cantFilas; i++) {
		printLineFile(archivo, i);
	}
}

//pos-condicion destruye toda la memoria de directorio
void destroyDirectory(TDirectorio& directorio) {
	ListaArchivo lista = directorio->listaArchivos;
	while (lista != NULL) {
		ListaArchivo aux = lista;
		if (lista->archivo != NULL) {
			TArchivo archivo = lista->archivo;
			destroyFile(archivo);
		}
		lista = lista->siguiente;
		delete aux;
	}
	Cadena nombre = directorio->nombre;
	TDirectorio hermano = directorio->hermano;
	TDirectorio hijo = directorio->hijo;
	delete lista;
	delete nombre;
	delete hermano;
	delete hijo;
	delete directorio;
}

void listaArchivos(TDirectorio directorio) {
	ListaArchivo lista = directorio->listaArchivos;
	int n = 0;
	while (lista != NULL) {
		printf("nodo %d listaArchivo %p\n", n, lista);
		if (lista->archivo != NULL) {
			printf("----nodo de archivo %p\n", lista->archivo);
			printf("----nombre de archivo: %s\n", getFileName(lista->archivo));
			TArchivo archivo = lista->archivo;
			TFila fila = firstRowFile(archivo);
			int i = 0;
			while (fila != NULL) {
				printf("--------fila pos %d nodo %p\n", i, fila);
				if (headRow(fila) != NULL) {
					TLinea linea = headRow(fila);
					int j = 0;
					while (linea != NULL) {
						printf("------------linea pos %d nodo %p\n", j, linea);
						if (firstCharLine(linea) != NULL) printf("letra %c\n", firstCharLine(linea));
						else printf("nodo dummy\n");
						linea = nextLine(linea);
						j++;
					}
				}
				fila = nextRow(fila);
				i++;
			}
		}
		lista = lista->siguiente;
		n++;
	}
}
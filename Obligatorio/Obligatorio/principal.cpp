/* 41603546 */ // sustituiir con los 7 dígitos de la cédula
/*
Módulo principal de la tarea 1.FILE SYSTEM

Intérprete de comandos para probar los módulos.

  Laboratorio de EDA 2023
  UTU - LATU - Turno Nocturno 
  Profesor Ferando Arrieta
*/

//#include "include/archivo.h"
//#include "include/linea.h"
//#include "include/fila.h"
//#include "include/directorio.h"
//#include "include/utils.h"

#include "linea.h"
#include "fila.h"
#include "archivo.h"
#include "directorio.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAX_PALABRA 64
#define MAX_LINEA 256
#define MAX_RUTA 256
#define MAX_PARAMETRO 10
#define MAX_PARAMETRODIR 1
#define MAX_COMANDO 10
#define MAX_NOMBRE 15
#define MAX_EXTENSION 3
#define TEXTO_MAX 50

enum _retorno {OK, ERROR, NO_IMPLEMENTADA};
typedef enum _retorno TipoRet;
typedef char* Cadena;

  
TipoRet CREARSISTEMA(TDirectorio &s);
TipoRet CREATE (TDirectorio &sistema, Cadena nombreArchivo);
TipoRet DELETE (TDirectorio &sistema, Cadena nombreArchivo);
TipoRet ATTRIB (TDirectorio &sistema, Cadena nombreArchivo, Cadena parametro);
TipoRet IF (TDirectorio &sistema, Cadena nombreArchivo, Cadena texto);
TipoRet IN (TDirectorio &sistema, Cadena nombreArchivo, Cadena texto);
TipoRet DF (TDirectorio &sistema, Cadena nombreArchivo, Cadena cantidad);
TipoRet TYPE (TDirectorio &sistema, Cadena nombreArchivo);
TipoRet DESTRUIRSISTEMA (TDirectorio &sistema);


void ejecutarPrincipal();
Cadena modCad(Cadena texto);

// programa principal
int main() {
    ejecutarPrincipal();

    return 0;
} // main

Cadena modCad(Cadena texto) {
    int largo = static_cast<int>(strlen(texto))-1;
    if (texto[largo - 1] == '"') largo--;
    if (texto[1] == '"') largo--;
    
    Cadena nuevoTexto = new char[largo];
    char del1[] = " \"";
    
    if (texto[1] == '"')
        nuevoTexto = strtok(texto, del1);
    else nuevoTexto = strtok(texto, " ");
    
    if (nuevoTexto[strlen(nuevoTexto) - 1] == '"')
        nuevoTexto[strlen(nuevoTexto) - 1] = '\0';
    
    return nuevoTexto;
}

//****************************** Funciones a implementar ************************************

TipoRet CREARSISTEMA(TDirectorio& sistema) {
    sistema = createRootDirectory();
    return OK;
}

TipoRet CREATE(TDirectorio& sistema, Cadena nombreArchivo) {

    if (!existFileDirectory(sistema, nombreArchivo)) {
        createFileInDirectory(sistema, nombreArchivo);
        return OK;
    }
    else {
        return ERROR;
    }
}

TipoRet DELETE(TDirectorio& sistema, Cadena nombreArchivo) {
    if (existFileDirectory(sistema, nombreArchivo)) {
        TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
        if (haveWritePermission(archivo)) {
            deleteFileDirectory(sistema, nombreArchivo);
            return OK;
        }
        else return ERROR;
    }
    else return ERROR;    
}

TipoRet ATTRIB(TDirectorio& sistema, Cadena nombreArchivo, Cadena parametro) {
    if (existFileDirectory(sistema, nombreArchivo) ) {
        if (0 == strcmp("+W", parametro)) {
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
            setWritePermission(archivo, true);
            return OK;
        }
        else if (0 == strcmp("-W", parametro)) {
            TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
            setWritePermission(archivo, false);
            return OK;
        }
        return ERROR;
    }
    else return ERROR;
}

TipoRet IF(TDirectorio& sistema, Cadena nombreArchivo, Cadena texto) {
    if (existFileDirectory(sistema, nombreArchivo)) {
        TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
        if (haveWritePermission(archivo)) {
            Cadena nuevo = modCad(texto);
            int largoEntrada = static_cast<int>(strlen(nuevo));
            int largoArchivo = static_cast<int>(getCountChars(archivo));
            char nuevoTexto[TEXTO_MAX+1];
            if (largoEntrada >= TEXTO_MAX) {
                strncpy(nuevoTexto, nuevo, TEXTO_MAX);
                nuevoTexto[TEXTO_MAX] = '\0';
                deleteCharsFile(sistema, nombreArchivo, largoArchivo);
                insertChartsNewRow(archivo, nuevoTexto);
            }
            else {
                int resto = TEXTO_MAX - largoEntrada;
                if (resto < largoArchivo) deleteCharterFile(archivo, largoArchivo - resto);
                insertChartsNewRow(archivo, nuevo);
            }
            return OK;
        }
        else return ERROR;
    }
    else return ERROR;
}

TipoRet IN(TDirectorio& sistema, Cadena nombreArchivo, Cadena texto) {
    if (existFileDirectory(sistema, nombreArchivo)) {
        TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
        if (haveWritePermission(archivo)) {
            Cadena nuevo = modCad(texto);
            int largoEntrada = static_cast<int>(strlen(nuevo));
            int largoArchivo = static_cast<int>(getCountChars(archivo));
            char nuevoTexto[TEXTO_MAX+1];
            if (largoEntrada >= TEXTO_MAX) {
                strncpy(nuevoTexto, texto, TEXTO_MAX);
                nuevoTexto[TEXTO_MAX] = '\0';
                deleteCharsFile(sistema, nombreArchivo, largoArchivo);
                insertChartsFirstRow(archivo, nuevoTexto);
            }
            else {
                int resto = TEXTO_MAX - largoEntrada;
                if (resto < largoArchivo) deleteCharterFile(archivo, largoArchivo - resto);
                insertChartsFirstRow(archivo, nuevo);
            }
            return OK;
        }
        else return ERROR;
    }
    else return ERROR;
}

TipoRet DF(TDirectorio& sistema, Cadena nombreArchivo, Cadena cantidad) {
    if (existFileDirectory(sistema, nombreArchivo)) {
        TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
        if (haveWritePermission(archivo)) {
            int largo = getCountChars(archivo);
            int l = atoi(cantidad);
            if (l > largo) l = largo;
            deleteCharsFile(sistema, nombreArchivo, l);
            return OK;
        }
        else return ERROR;
    }
    else return ERROR;
}

TipoRet TYPE(TDirectorio& sistema, Cadena nombreArchivo) {
    if (existFileDirectory(sistema, nombreArchivo)) {
        TArchivo archivo = getFileDirectory(sistema, nombreArchivo);
        if (getCountChars(archivo) == 0) printf("El archivo no posee contenido\n");
        else printFile(sistema, nombreArchivo);
        return OK;
    }
    else return ERROR;
}

TipoRet DESTRUIRSISTEMA(TDirectorio& sistema) {
    destroyDirectory(sistema);
    return OK;
}

void ejecutarPrincipal() {
    char restoLinea[MAX_LINEA + 1];
    char comando[MAX_PALABRA];
    char parametro[MAX_PALABRA];
    char texto[MAX_PALABRA];
    char nombrearchivo[MAX_NOMBRE];
    char cantidad[MAX_PALABRA];
    //char parametro;
    TDirectorio sistema;
    int sistemaInicializado = false;
    bool salir = false;
    while (!salir) {
        printf("#");
        // leer el comando
        leerChars(comando);
        if (!strcmp(comando, "ATTRIB")) {
            leerChars(nombrearchivo);
            leerChars(parametro);
        }
        else if (!strcmp(comando, "CREATEFILE"))
            leerChars(nombrearchivo);

        else if (!strcmp(comando, "DELETE"))
            leerChars(nombrearchivo);

        else if (!strcmp(comando, "IF")) {
            leerChars(nombrearchivo);
            leerRestoLinea(texto);
        }
        else if (!strcmp(comando, "IN")) {
            leerChars(nombrearchivo);
            leerRestoLinea(texto);
        }
        else if (!strcmp(comando, "DF")) {
            leerChars(nombrearchivo);
            leerChars(cantidad);
        }
        else if (!strcmp(comando, "TYPE"))
            leerChars(nombrearchivo);


        // *********************** Procesamiento de comandos ***********************************


        if (0 == strcmp(comando, "CREARSISTEMA")) {
            if (!sistemaInicializado) {
                TipoRet salida = CREARSISTEMA(sistema);
                if (salida == OK) {
                    sistemaInicializado = true;
                    printf("*** SYSTEM INICIALIZED ***\n");
                    printf("OK\n");
                }
            }
            else
                printf("EL SISTEMA YA FUE INICIALIZADO\n");

        }
        else if (0 == strcmp(comando, "CREATEFILE")) {

            TipoRet salida = CREATE(sistema, nombrearchivo);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "DELETE")) {
            TipoRet salida = DELETE(sistema, nombrearchivo);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "ATTRIB")) {
            TipoRet salida = ATTRIB(sistema, nombrearchivo, parametro);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "IF")) {
            TipoRet salida = IF(sistema, nombrearchivo, texto);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "IN")) {
            TipoRet salida = IN(sistema, nombrearchivo, texto);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "DF")) {
            TipoRet salida = DF(sistema, nombrearchivo, cantidad);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "TYPE")) {
            TipoRet salida = TYPE(sistema, nombrearchivo);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");

        }
        else if (0 == strcmp(comando, "DESTRUIRSISTEMA")) {
            TipoRet salida = DESTRUIRSISTEMA(sistema);
            if (salida == OK)
                printf("OK\n");
            else if (salida == ERROR)
                printf("ERROR\n");
        }
        else
            printf("Comando no reconocido.\n");

        fgets(restoLinea, MAX_LINEA + 1, stdin);
    } // while
}


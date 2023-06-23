#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;




int tablero[4][4]; /** @brief tablero de juego*/
int auxiliar[4][4]; /** @brief tablero auxiliar*/
int puntaje = 0; /** @brief puntaje*/
int movimientos =0; /** @brief cantidad de moviemientos*/
bool derrota = false; /** @brief verifica la derrota*/
bool victoria = false; /** @brief verifica la victoria*/

struct jugador{ /** @brief representa un jugador*/
    char alias[10];
    char cedula[8];
    char nombre[20];
    char apellido[30];
    char localidad[30];
    int anio;
    int mes;
    int dia;
    bool estado;
};

jugador jugadorLog; /** @brief jugador que inicio sesion y que esta jugando en el momento*/

jugador listaJugadores[100];/** @brief array donde se almacenan los jugadores */
int topeJugadores = 0; /** @brief siguiente lugar vacio en la listaJugadores */

struct partida{
    char alias[10];
    char resultado;
    int puntaje;
    int movimientos;
    char fechaHora[20];
};

partida listaPartidas[200];/** @brief array donde se almacenan las partidas jugadas */
int topePartidas = 0; /** @brief siguiente lugar vacio en la listaPartidas */

/**
 * @brief Copia cierta cantidad de elementos de una array a otro
 * @param cantidad cantidad de elementos a copiar
 * @param campo array tipo char destino
 * @param entrada array tipo char origen
*/
void rellenarCampo(int cantidad, char campo[], char entrada[]){
    for(int i = 0; i < cantidad; i ++){
        campo[i] = entrada[i];
    }
}

/** @brief elimina todos los elementos de un arreglo para asi poder 
 * reescribrirlos de forma segura
 * @param campo arreglo a reescribirlos
*/
 
void limpiarArreglo(char campo[]){
    int c = 0;
    while(campo[c]!= '\0'){
      campo[c] = '\0';
      c++;
    }
}

/**
 * @brief Crea un jugador con solo el alias como parametro y 
 * pidiendo el resto de los datos por terminal,
 * automaticamente lo inserta en la listaJugador y
 * aumenta en 1 el topeJugadores
 * @param alias array de tipo char tamaño maximo 10
 * 
*/
void crearJugador(char alias[10]){
    jugador nuevo;
    rellenarCampo(10, nuevo.alias, alias);
    printf("ingrese la cedula, sin punto ni guiones\n");
    scanf("%8s", nuevo.cedula);
    printf("ingrese el nombre, hasta 20 caracteres\n");
    scanf("%20s", nuevo.nombre);
    printf("ingrese apellido, hasta 30 caracteres\n");
    scanf("%30s", nuevo.apellido);
    printf("ingrese la localidad, hasta 30 caracteres\n");
    scanf("%30s", nuevo.localidad);
    printf("ingrese el dia de nacimiento, en formato dd\n");
    scanf("%d", &nuevo.dia);
    printf("ingrese el mes de nacimiento, en formato mm\n");
    scanf("%d", &nuevo.mes);
    printf("ingrese el año de nacimiento, en formato aaaa\n");
    scanf("%d", &nuevo.anio);
    nuevo.estado = true;
    printf("Jugador creardo correctamente\n");
    listaJugadores[topeJugadores] = nuevo;
    topeJugadores++;
}

/**
 * @brief Crea un jugador 
 * automaticamente lo inserta en la listaJugador y
 * aumenta en 1 el topeJugadores
 * @param alias array de tipo char tamaño maximo 10 representa el alias
 * @param cedula array tipo char de tamaño 8 representa la cedula
 * @param nombre array tipo char
 * @param apellido array tipo char
 * @param localidad array tipo char
 * @param anio int
 * @param mes int
 * @param dia int
 * @param activo true o false
*/
void crearJugador(char alias[], char cedula[], char nombre[], char apellido[], char localidad[], int anio, int mes, int dia, bool activo){
    jugador nuevo;
    rellenarCampo(10, nuevo.alias, alias);
    rellenarCampo(8, nuevo.cedula, cedula);
    rellenarCampo(20, nuevo.nombre, nombre);
    rellenarCampo(30, nuevo.apellido, apellido);
    rellenarCampo(30, nuevo.localidad, localidad);
    nuevo.anio = anio;
    nuevo.mes = mes;
    nuevo.dia = dia;
    nuevo.estado = activo;
    int indice = topeJugadores;
    listaJugadores[indice] = nuevo;
    topeJugadores ++;
}

/**
 * @brief Modifica el juegador
 * @param indice lugar que ocupa el jugador en listaJugadores
 * 
*/
void modificarJugador(int indice){
    rellenarCampo(10, listaJugadores[indice].alias, jugadorLog.alias);
    printf("ingrese la cedula, sin punto ni guiones\n");
    limpiarArreglo(listaJugadores[indice].cedula);
    scanf("%8s", listaJugadores[indice].cedula);
    printf("ingrese el nombre, hasta 20 caracteres\n");
    limpiarArreglo(listaJugadores[indice].nombre);
    scanf("%20s", listaJugadores[indice].nombre);
    printf("ingrese apellido, hasta 30 caracteres\n");
    limpiarArreglo(listaJugadores[indice].apellido);
    scanf("%30s", listaJugadores[indice].apellido);
    printf("ingrese la localidad, hasta 30 caracteres\n");
    limpiarArreglo(listaJugadores[indice].localidad);
    scanf("%30s", listaJugadores[indice].localidad);
    printf("ingrese el dia de nacimiento, en formato dd\n");
    scanf("%d", &listaJugadores[indice].dia);
    printf("ingrese el mes de nacimiento, en formato mm\n");
    scanf("%d", &listaJugadores[indice].mes);
    printf("ingrese el año de nacimiento, en formato aaaa\n");
    scanf("%d", &listaJugadores[indice].anio);
    listaJugadores[indice].estado = true;
    printf("Jugador ha sido modificado correctamente\n");
}

/***
 * @brief una partida nueva, la inserta en listaPartidas y 
 * aumenta en uno el topePartidas
 * @param alias array tipo char 
 * @param fecha array tipo char
 * @param resultado char "G" o "P"
 * @param puntaje int
 * @param movimientos int
*/
void crearPartida(char alias[], char resultado, int puntaje, int movimientos, char fecha[]){
    partida nueva;
    rellenarCampo(10, nueva.alias, alias);
    nueva.resultado = resultado;
    nueva.puntaje = puntaje;
    nueva.movimientos = movimientos;
    rellenarCampo(20, nueva.fechaHora, fecha);
    listaPartidas[topePartidas] = nueva;
    topePartidas++;
}

/** @brief Compara dos alias para determinar cual precede alfabeticamente
    @param primero array tipo char tamaño maximo 10
    @param segundo array tipo char tamaño maximo 10
    @return retorna 1 en caso de primero preceder a segundo
            retorna -1 en cado de segundo preceder a primero
*/
int compararAlias(char primero[10], char segundo[10]){
    int lugar;
    int i = 0;
    while(primero[i] != '\0' && segundo[i] != '\0' && i < 10){
        lugar = 0;
        if(primero[i] < segundo[i]) {
            lugar = 1;
            return lugar;
        }
        else if(primero[i] > segundo[i]) {
            lugar = -1;
            return lugar;
        }
        i++;
    }
    if(lugar != 1 && lugar != -1) lugar = 0;
    return lugar;
}

/** @brief busca el alias dentro de listaJugadores
    @param aliasBuscado array tipo char tamaño maximo 10
    @return retorna un int que representa el indice que ocupa el jugador que se esta buscando
            retorna -1 en cado de no encontrar el jugador
*/
int chequearAlias(char aliasBuscado[10]){

    int indice =0;
    bool igualdad;
    while(indice < topeJugadores){
        int i = 0;
        while(aliasBuscado[i] != '\0' && 
            listaJugadores[indice].alias[i]!= '\0' && i < 10){
                if(aliasBuscado[i] == listaJugadores[indice].alias[i])
                    igualdad = true;
                else{
                    igualdad = false;
                    break;
                }
            i++;
        }
        if(igualdad) return indice;
        indice++;
    }
    if(!igualdad) indice = -1;
    return indice;
}

/// @brief Comprueba si el jugador esta activo o no
/// @param indice int lugar que ocupara el jugador dentro de listaJugadores
/// @return true si esta activo, falso, si no
bool chequearEstado( int indice){
    return listaJugadores[indice].estado;
}

/**
 *  @brief ordena alfabeticamente la listaJugadores segun el alias
 *          usa el metodo por insercion 
*/
void ordenarJugadores(){
    int j;
    jugador tmp;
    for (int i = 1; i < topeJugadores; i++){
        j = i;
        tmp = listaJugadores[i];
        while ((j > 0) && ((compararAlias(tmp.alias, listaJugadores[j-1].alias))==1)){
            listaJugadores[j] = listaJugadores[j-1]; 
            j -= 1;
        }
        listaJugadores[j] = tmp; 
    }
}

/**
 * @brief Imprime en pantalla los elementos de un array char
 * @param largo int tamaño del char
 * @param campo array char 
*/
void mostrarCampo(int largo, char campo[]){
    for(int j = 0; j < largo; j++){
        if(campo[j] != '\0') putchar(campo[j]);
        else putchar(' ');
    }
}

/**
 *@brief imprime en pantalla los datos del jugador
  @param indice del jugador en la listaJugadores
*/
void verJugador(int indice){
    mostrarCampo(10, listaJugadores[indice].alias);
    putchar('\t');
    mostrarCampo(8, listaJugadores[indice].cedula);
    putchar('\t');
    mostrarCampo(20, listaJugadores[indice].nombre);
    putchar('\t');
    mostrarCampo(30, listaJugadores[indice].apellido);
    putchar('\t');
    mostrarCampo(30, listaJugadores[indice].localidad);
    putchar('\t');
    printf("%2d/",listaJugadores[indice].dia);
    printf("%2d/",listaJugadores[indice].mes);
    printf("%d\t",listaJugadores[indice].anio);
    if(listaJugadores[indice].estado) printf("Activo\n");
    else{ printf("No Activo\n");}       
}

/**
 * @brief compara dos fechas y determina cual precede
 * @param fecha1, fecha2  array char 
 * @return retorna 1 en caso de fecha1 preceder a fecha2
        retorna -1 en cado de fecha2 preceder a fecha1
*/
int compararFechas(char fecha1[], char fecha2[]){
    int lugar = 0;
    int i = 0;
    while(fecha1[i] != '\0' && fecha2[i] != '\0' && i < 20){
        if(fecha1[i] < fecha2[i]) {
            lugar = 1;
            return lugar;
        }
        else if(fecha1[i] > fecha2[i]) {
            lugar = -1;
            return lugar;
        }
        i++;
    }
    return lugar;
}

/**
 * @brief ordena la listaPartidas segun la fecha en orden descendente
*/
void ordenarFechas(){
    int j;
    partida temp;
    for(int i =1; i < topePartidas; i++){
        j = i;
        temp = listaPartidas[i];
        while((j>0) && ((compararFechas(temp.fechaHora, listaPartidas[j-1].fechaHora) == -1))){
            listaPartidas[j] = listaPartidas[j-1];
            j -= 1;
        }
        listaPartidas[j] = temp;
    }
}

/**
 * @brief ordena las partidas segun el puntaje  en orden descendente 
 * y en caso de igualdad segun la cantidad de movimientos en orden ascendente 
*/
void ordenarPuntajeMov(){
    int j;
    partida temp;
    for(int i = 1; i < topePartidas; i++){
        j = i;
        temp = listaPartidas[i];
        while( j > 0 && temp.puntaje >= listaPartidas[j-1].puntaje){
            if(temp.puntaje > listaPartidas[j-1].puntaje){
                listaPartidas[j] = listaPartidas[j-1];
                j -= 1;
            }
            else if(temp.puntaje == listaPartidas[j-1].puntaje){
                if(temp.movimientos < listaPartidas[j-1].movimientos){
                    listaPartidas[j] = listaPartidas[j-1];
                    j -= 1;
                }
            }
        }
        listaPartidas[j] = temp;
    }
}

/**
 * @brief imrime en pantalla los datos una partida
 * @param indice de la partida en la listaPartidas
*/
void verPartida(int indice){
    for(int j = 0; j < 10; j++){
        if(listaPartidas[indice].alias[j] != '\0') putchar(listaPartidas[indice].alias[j]);
        else putchar(' ');
    }
    putchar('\t');
    printf("%-9c\t", listaPartidas[indice].resultado);
    printf("%-10d\t", listaPartidas[indice].puntaje);
    printf("%-11d\t", listaPartidas[indice].movimientos);
    for(int j = 0; j < 20; j++){
        if(listaPartidas[indice].fechaHora[j] != '\0') putchar(listaPartidas[indice].fechaHora[j]);
        else putchar(' ');
    }
    putchar('\n');
}

/// @brief imprime el tablero
void imprimirTablero(){ // imprime el tablero
    printf("-----------------------------------------------------------------\n");
    for(int i = 0; i < 4; i++){
        printf("|\t\t|\t\t|\t\t|\t\t|\n");
        for( int j = 0; j < 4; j++){
            if(tablero[i][j]!=0){
                printf("|\t%d\t", tablero[i][j]);
            }else{
                printf("|\t\t");
            }
        }
        printf("|\n");
        printf("|\t\t|\t\t|\t\t|\t\t|\n");
        printf("-----------------------------------------------------------------\n");

    }
    printf("Puntaje: %d\t\tMovimientos: %d\n", puntaje, movimientos);
    printf("-----------------------------------------------------------------\n");
}

/**
 * @brief crea el tablero inicial con todos los valores en 0,
    excepto dos posiciones random a las que se asigna el valor 2.
*/
void tableroInicial(){
    srand(time(NULL));
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            tablero[i][j] = 0;
    }
    //posicion random 1
    int fila = rand() % 4;
    int col =  rand() % 4;
    tablero[fila][col] = 2;
    /*
    posicion random 2, ya que hay 1 en 16 pisibilidades de que
    ambas posiciones coincidan, se verifica que no sean igual,
    en caso de serlo genera otra posicion.
    */
    int fila2 = rand() % 3;
    int col2 =  rand() % 3;
    while(tablero[fila2][col2] != 0){
        fila2 = rand() % 3;
        col2 =  rand() % 3;
    }
    tablero[fila2][col2] = 2;
}

/** @brief Determina si el juego se perdio o gano,
    Si no hay celda con valor 0 y ademas no se puede hacer movimientos,
    o sea no hay dos celda juntas que sean iguales, entonces se perdio el juego.
    Si alguna celda alcanza el valor 2048 entonces se gano el juego.
*/
void estado(){
   int contadorCeros = 0; // contador de ceros
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tablero[i][j] == 0)
                contadorCeros ++;
            if(tablero[i][j] == 2048)        
                victoria = true;
        }
    }
    int contadorIguales = 0;// contador de celdas iguales
    if(contadorCeros == 0){
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if ((i <3 && j < 3)){
                    if((tablero[i][j] == tablero[i][j+1]) || (tablero[i][j] == tablero[i+1][j]))
                        contadorIguales ++;   
                }else if (i ==3 && j < 3){
                    if(tablero[i][j] == tablero[i][j+1])
                        contadorIguales ++;
                }else if (i < 3 && j == 3){
                    if(tablero[i][j] == tablero[i+1][j])
                        contadorIguales ++;
                }
            }
        }
    }
    if(contadorCeros == 0 && contadorIguales == 0)
        derrota = true;
}

/** @brief genera un tablero auxiliar copia del tablero original
    para hacer una comparacion 
*/
void crearAuxiliar(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            auxiliar[i][j] = tablero[i][j];
        }
    }
}

/** @brief Genera un nuevo valor, 2 o 4, en una celda con valor 0, 
    siempre y cuando el movimiento anterior haya modificado el tablero*/
void nuevoValor(){

    int contador = 0;// contador de diferencias entre tableros
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(auxiliar[i][j] != tablero[i][j])
                contador++;
        }
    }
    // si hay al menos una diferencia entre tableros
    if(contador > 0){
        int fila = rand() % 4;
        int col =  rand() % 4;
        while(tablero[fila][col] != 0){
            fila = rand() % 4;
            col =  rand() % 4;
        }
        tablero[fila][col] = 2+ (2*rand()%2);    
    }
}

/*
Logica de movimientos: cuando se realiza un movimiento las celdas con 
valores distintos a 0 deben correrse hacia la dirección indicada, 
habiendo dos celdas iguales estas deben fucionarse
quedando una celda con el doble de valor, 
si hay tres celdas iguales deberan quedar una celda del doble valor y
otra con valor original, si hay cuatro celdas iguales deberan quedar 
dos celdas con el doble valor, no quedar una con el cuadruple valor 
por que las celdas no deben fucionarse más de una vez.
Primero se comparan de a dos celdas de la misma columna o fila con el fin
de correr las celdas no 0, se tiene que repitir tres para asegurarse de correr
todas las celdas.
Segundo se comparan de a dos las celdas para fucionar aquellas que sean iguales
Tercero se vuelven a comparar las seldas pra correr la celdas en caso de que 
hayan surgido celdas 0 en el segundo paso.
Los ultimos dos pasos solo tienen que hacer una vez por fila o columna.
*/
void moverIzq(){ /** @brief mueve hacia la izquierda*/ 
    for(int i = 0; i < 4; i++){
        for( int m = 1; m <= 3; m++){// contador de comparaciones
            for(int j = 0; j < 3; j++){
                if (tablero[i][j] == 0 && tablero[i][j+1] != 0){
                    tablero[i][j] = tablero[i][j+1];
                    tablero[i][j+1] = 0;
                    }
            }
        }
        for(int j = 0; j < 3; j++){
            if (tablero[i][j] == tablero[i][j+1]){
                tablero[i][j] = tablero[i][j] *2 ;
                tablero[i][j+1] = 0;
                puntaje = puntaje + tablero[i][j];
            } 
            if(tablero[i][j] == 0 && tablero[i][j+1] != 0){
                tablero[i][j] = tablero[i][j+1];
                tablero[i][j+1] = 0;
            }
        }

    }    
}

void moverDer(){  /** @brief mueve hacia la derecha*/
    for(int i = 0; i < 4; i++){
        for( int m = 1; m <= 3; m++){// contador de comparaciones
            for(int j = 3; j > 0; j--){
                if (tablero[i][j] == 0 && tablero[i][j-1] != 0){
                    tablero[i][j] = tablero[i][j-1];
                    tablero[i][j-1] = 0;
                }
            }
        }
       for(int j = 3; j > 0; j--){
            if (tablero[i][j] == tablero[i][j-1]){
                tablero[i][j] = tablero[i][j] * 2;
                tablero[i][j-1] = 0;
                puntaje = puntaje + tablero[i][j];
            } 
            if (tablero[i][j] == 0 && tablero[i][j-1] != 0){
                tablero[i][j] = tablero[i][j-1];
                tablero[i][j-1] = 0;
            }
        }
    }
}

void moverArriba(){  /** @brief mueve hacia arriba*/
    for(int j = 0; j < 4; j++){
       for( int m = 1; m <= 3; m++){// contador de comparciones
            for(int i = 0; i < 3; i++){
                if (tablero[i][j] == 0 && tablero[i+1][j] != 0){
                    tablero[i][j] = tablero[i+1][j];
                    tablero[i+1][j] = 0;
                }
            }
        }
        for(int i = 0; i < 3; i++){
            if (tablero[i][j] == tablero[i+1][j]){
                tablero[i][j] = tablero[i][j] * 2;
                tablero[i+1][j] = 0; 
                puntaje = puntaje + tablero[i][j];       
            }
            if (tablero[i][j] == 0 && tablero[i+1][j] != 0){
                tablero[i][j] = tablero[i+1][j];
                tablero[i+1][j] = 0;
            }
        }
    }
}

void moverAbajo(){  /** @brief mueve hacia abajo*/
    for(int j = 0; j < 4; j++){
        for( int m = 1; m <= 3; m++){// contador de comparciones
            for(int i = 3; i >0; i--){
                if (tablero[i][j] == 0 && tablero[i-1][j] != 0){
                    tablero[i][j] = tablero[i-1][j];
                    tablero[i-1][j] = 0;
                }
            }
        }
        for(int i = 3; i >0; i--){
                if (tablero[i][j] == tablero[i-1][j]){
                    tablero[i][j] = tablero[i][j] * 2;
                    tablero[i-1][j] = 0;
                    puntaje = puntaje + tablero[i][j];        
                }
                if (tablero[i][j] == 0 && tablero[i-1][j] != 0){
                    tablero[i][j] = tablero[i-1][j];
                    tablero[i-1][j] = 0;
                }
            }
    }
}

/**
 * @brief obtiene la fecha actual de sistema.
 * @param fecha char donde sera almacenada la fecha
*/
void obtenerFecha(char fecha[20]){
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (fecha,20,"%Y-%m-%d %H-%M-%S",timeinfo);

}

void jugar(){  /** @brief realiza la mecanica del juego*/
    char fechaIncio[20];
    obtenerFecha(fechaIncio);
    bool seguirJugando = true;
    do{
        tableroInicial();
        printf("Los movimientos son:\n");
        printf("Izquierda:\ta\nDerecha:\td\nArriba:\t\tw\nAbajo\t\ts\n\n");
        printf("Para cancelar el juego presiona 'c' pero perderas el juego\n");
        imprimirTablero();
        while(derrota == false && victoria == false){
            crearAuxiliar();
            char mov;
            scanf(" %c", &mov);
            if( mov != 'c'){
                movimientos ++;
                char mensaje[30];
                switch (mov){
                case 'a':
                    {moverIzq();
                    char mensajeA [30]= "Moviste hacia a la izquierda";
                    rellenarCampo(30, mensaje, mensajeA);}
                    break;
                case 'd':
                    {moverDer();
                    char mensajeB [30]= "Moviste hacia a la derecha";
                    rellenarCampo(30, mensaje, mensajeB);}
                    break;
                case 'w':
                    {moverArriba();
                    char mensajeC [30]= "Moviste hacia a arriba";
                    rellenarCampo(30, mensaje, mensajeC);}
                    break;
                case 's':
                    {moverAbajo();
                    char mensajeD [30]= "Moviste hacia a abajo";
                    rellenarCampo(30, mensaje, mensajeD);break;}
                    break;    
                default:
                    printf("ingresa una tecla valida");
                    break;
                }
                /*
                Realiza la limpieza de la pantalla
                segun sobre sistema se este corriendo
                */
                #ifdef _WIN32
                system("cls");
                #else
                    system("clear");
                #endif
           
                printf("----------------------------------\n");
                printf("%s\n", mensaje);
                nuevoValor();
                imprimirTablero();
                estado();
            }
            else if(mov == 'c'){
                printf("Vas a cancelar el juego? s/n\n");
                char opcion;
                scanf(" %c", &opcion);
                while(opcion != 's' && opcion != 'n'){
                    scanf(" %c", &opcion);
                }  
                if(opcion == 's'){
                    derrota = true;
                }else if(opcion == 'n'){
                    derrota = false;
                }
            }
        }
        if(derrota){
            crearPartida(jugadorLog.alias, 'P', puntaje, movimientos, fechaIncio);
            printf("Lo siento has perdido. Deseas jugar otra vez? s/n\n");
            }
        if(victoria){
            crearPartida(jugadorLog.alias, 'G', puntaje, movimientos, fechaIncio);
            printf("Felicitaciones has ganado. Deseas jugar otra vez? s/n\n");
            }
        char opcion;
        scanf(" %c", &opcion);
        while(opcion != 's' && opcion != 'n'){
            scanf(" %c", &opcion);
        }  
        if(opcion == 's'){
                seguirJugando = true;
                derrota = false;
                victoria = false;

            }else if(opcion == 'n'){
                seguirJugando = false;
            }
    }while(seguirJugando == true);
}

void presentasion(){
    printf("    ////////   /////////   //     //   /////////\n");
    printf("          //   //     //   //     //   //     //\n");
    printf("          //   //     //   //     //   //     //\n");
    printf("    ////////   //     //   /////////   /////////\n");
    printf("    //         //     //          //   //     //\n");
    printf("    //         //     //          //   //     //\n");
    printf("    ////////   /////////          //   /////////\n\n");
}

void menuPrincipal();
void menuJugador();


void menuEstadisticas(){
    bool seguir = true;
    char opcion;
    do{
        /*#ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif*/
        printf("Menu de estadisticas\n");
        printf("\tVer todos los jugadores_______________1\n");
        printf("\tver todas las partidas________________2\n");
        printf("\tVer todas las partidas de un jugador__3\n");
        printf("\tVer mejores partidas__________________4\n");
        printf("\tvolver al menu principal______________5\n");
        printf("\tSalir_________________________________6\n");
      
        scanf(" %c", &opcion);
        switch (opcion){
        case '1':
            printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n",
             10, "Alias", 8, "Cedula", 20, "Nombre", 30, "Apellido",
             30, "Localidad", 10, "Fecha", 6, "Estado");
            for(int i = 0; i < 142; i++){
                putchar('-');
            }
            putchar('\n');
            ordenarJugadores();
            for(int i = 0; i < topeJugadores; i++){
                if(listaJugadores[i].estado) verJugador(i);
            }
            for(int i = 0; i < 142; i++){
                putchar('-');
            }
            putchar('\n');
            break;
        case '2':
            ///muestra las partidas ordenas por fecha
            printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n",
             10, "Alias", 9, "Resultado", 10, "Puntaje", 11, "Movimientos",
             20, "Fecha");
            for(int i = 0; i < 100; i++){
                putchar('-');
            }
            putchar('\n');
            ordenarFechas(); 
            for(int i = 0; i < topeJugadores; i++){
                verPartida(i);
            }
            for(int i = 0; i < 100; i++){
                putchar('-');
            }
            putchar('\n');
            break;
        case '3':
            //muestra las partidas de cierto jugador
           { 
            bool activo = false;
            do{
                printf("Ingresa el alias buscado\n");
                char entradaAlias[10];
                scanf("%s", entradaAlias);
                int indiceJugador = chequearAlias(entradaAlias);
                if(indiceJugador != -1) activo = chequearEstado(indiceJugador);
                else activo = false;
                if(indiceJugador != -1 && activo){
                    printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n",
                    10, "Alias", 9, "Resultado", 10, "Puntaje", 11, "Movimientos",
                    20, "Fecha");
                    for(int i = 0; i < 83; i++){
                        putchar('-');
                    }
                    putchar('\n');
                    ordenarFechas(); 
                    for(int i = 0; i < topeJugadores; i++){
                        int comp = compararAlias(entradaAlias, listaPartidas[i].alias);
                        if(comp != 1 && comp != -1) verPartida(i);
                    }
                    for(int i = 0; i < 83; i++){
                        putchar('-');
                    }
                    putchar('\n');
                }
            }while(activo == false);
            }
            break;
        case '4':
            /* muestra las mejores partidas segun puntaje en orden descendente y si hay empate
            segun los movimientos en oreden ascendente.
             */  
            printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n",
             10, "Alias", 9, "Resultado", 10, "Puntaje", 11, "Movimientos",
             20, "Fecha");
            for(int i = 0; i < 83; i++){
                putchar('-');
            }
            putchar('\n');
            ordenarPuntajeMov(); 
            for(int i = 0; i < topePartidas; i++){
                verPartida(i);
            }
            for(int i = 0; i < 83; i++){
                putchar('-');
            }
            putchar('\n');
            break;
        case '5':
            menuPrincipal();
            break;
        case '6':
            exit(0);
        default:
            break;
        }
    }while(seguir == true);
}

void menuJugador(){
    bool seguir = true;
    char opcion;
    do{
        /*#ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif*/
        
        printf("Menu de jugadora/or: %s\n", jugadorLog.alias);
        printf("\tJugar-->\t\t\t1\n");
        printf("\tVer estadisticas-->\t\t2\n");
        printf("\tModificar jugador-->\t\t3\n");
        printf("\tVolver al menu principal-->\t4\n");
        printf("\tSalir-->\t\t\t5\n");
        scanf(" %c", &opcion);
        switch (opcion){
        case '1':
            jugar();
            break;
        case '2': //Ver estadisticas
            printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n",
            10, "Alias", 9, "Resultado", 10, "Puntaje", 11, "Movimientos",
            20, "Fecha");
            for(int i = 0; i < 83; i++){
                putchar('-');
            }
            putchar('\n');
            ordenarFechas(); 
            for(int i = 0; i < topeJugadores; i++){
                    int comp = compararAlias(jugadorLog.alias, listaPartidas[i].alias);
                    if(comp != 1 && comp != -1) verPartida(i);
                }
            for(int i = 0; i < 83; i++){
                putchar('-');
            }
            putchar('\n');
            break;
        case '3':{
            int indice = chequearAlias(jugadorLog.alias);
            modificarJugador(indice);
            }
            break;
        case '4':
            menuPrincipal();
            break;
        case '5':
            exit(0);
        default:

            break;
        }
    }while(seguir);
}

void menuPrincipal(){
    bool seguir = true;
    char opcion;
    do{
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        printf("Menu principal\n");
        printf("\tIngresar o registrarse-->\t1\n");
        printf("\tEstadisticas-->\t\t\t2\n");
        printf("\tSalir-->\t\t\t3\n");
        scanf(" %c", &opcion);
        switch (opcion){
        case '1':/** @brief Verifica el alias, si esta activo ingresa al menu de jugador,
                            si esta desactivo pregunta si quiere recuperarlo,
                            si no esta registrado ofrece registrarlo*/
            {bool preguntar;                            
            do{
                printf("Ingresa tu alias\n");
                char entradaAlias[10];
                scanf("%10s", entradaAlias);
                int indiceJugador = chequearAlias(entradaAlias);
                bool activo;
                if(indiceJugador != -1) activo = chequearEstado(indiceJugador);
                else activo = false;
                if((indiceJugador != -1) && activo){
                    jugadorLog = listaJugadores[indiceJugador];
                    printf("Bienvenida/o %s\n", jugadorLog.alias);
                    menuJugador();
                    preguntar = false;
                }else if(indiceJugador != -1 && !activo){
                    printf("Deseas recuperar el jugador o cancelar s/n/c\n");
                    char eleccion;
                    do{
                        scanf(" %c", &eleccion);
                        if(eleccion == 's'){
                            listaJugadores[indiceJugador].estado = true;
                            jugadorLog = listaJugadores[indiceJugador];
                    printf("Bienvenida/o %s\n", jugadorLog.alias);
                            menuJugador();
                            preguntar = false;
                        }else if(eleccion == 'n'){
                            printf("Debes ingresar otro alias\n");
                        }else{
                            menuPrincipal();
                            preguntar = false;
                        }
                    }while (eleccion != 's' && eleccion != 'n' && eleccion != 'c');
                }else{
                    printf("Este jugador no existe, deseas crearlo? s/n\n");
                    char eleccion;
                    scanf(" %c", &eleccion);
                    if(eleccion == 's'){
                        crearJugador(entradaAlias);
                        jugadorLog = listaJugadores[indiceJugador];
                        printf("Bienvenida/o %s\n", jugadorLog.alias);
                        menuJugador();
                        preguntar = false;
                    }else if(eleccion == 'n'){
                        menuPrincipal();
                    }
                    preguntar = false;
                }
            }while(preguntar == true);
            }break;
        case '2':
            menuEstadisticas();
            break;
        case '3':
            exit(0);
            break;
        default:
            break;
        }
    }while(seguir);
}

/**
 * @brief establece datos iniciales con los cuales hacer test de funcionalidades
*/
void datosIniciales(){
    char entrada01[10] = {'P','e','d','r','o','1','2','3','4','5'};
    char entrada02[8] = {'1','2','3','4','5','6','0','1'};
    char entrada03[20] = "Juan";
    char entrada04[30] = "Gutierrez";
    char entrada05[30] = "Montevideo";
    int anio0 = 2000;
    int mes0 = 06;
    int dia0 = 01;
    crearJugador(entrada01, entrada02, entrada03, entrada04, entrada05, anio0, mes0, dia0, true);
    
    char entrada11[10] = "Maria";
    char entrada12[8] = {'1','2','3','4','5','6','0','2'};
    char entrada13[20] = "Mariana";
    char entrada14[30] = "Rodriguez";
    char entrada15[30] = "Ciudad de la Costa";
    int anio1 = 2001;
    int mes1 = 11;
    int dia1 = 23;
    crearJugador(entrada11, entrada12, entrada13, entrada14, entrada15, anio1, mes1, dia1, false);

    char entrada21[10] = "Laura";
    char entrada22[8] = {'1','2','3','4','5','6','0','3'};
    char entrada23[20] = "Laura";
    char entrada24[30] = "Perez";
    char entrada25[30] = "Ciudad de la Costa";
    int anio2 = 2002;
    int mes2 = 10;
    int dia2 = 2;
    crearJugador(entrada21, entrada22, entrada23, entrada24, entrada25, anio2, mes2, dia2, true);

    char entrada31[10] = "Diego";
    char entrada32[8] = {'1','2','3','4','5','6','0','4'};
    char entrada33[20] = "Diego";
    char entrada34[30] = "Suarez";
    char entrada35[30] = "Ciudad de la Costa";
    int anio3 = 2000;
    int mes3 = 6;
    int dia3 = 12;
    crearJugador(entrada31, entrada32, entrada33, entrada34, entrada35, anio3, mes3, dia3, true);
    
    char resultado0 = 'P';
    int puntaje0 = 4500;
    int movimientos0 = 150;
    char fechaHora0[20] ="2023-05-10 12:05:20";
    crearPartida(entrada01, resultado0, puntaje0, movimientos0, fechaHora0);

    char resultado1 = 'G';
    int puntaje1 = 7800;
    int movimientos1 = 289;
    char fechaHora1[20] ="2023-05-11 00:00:00";
    crearPartida(entrada11, resultado1, puntaje1, movimientos1, fechaHora1);

    char resultado2 = 'P';
    int puntaje2 = 4857;
    int movimientos2 = 256;
    char fechaHora2[20] ="2023-05-12 00:00:00";
    crearPartida(entrada21, resultado2, puntaje2, movimientos2, fechaHora2);

    char resultado3 = 'G';
    int puntaje3 = 7500;
    int movimientos3 = 140;
    char fechaHora3[20] ="2023-05-13 00:00:00";
    crearPartida(entrada31, resultado3, puntaje3, movimientos3, fechaHora3);

    char resultado4 = 'G';
    int puntaje4 = 7800;
    int movimientos4 = 250;
    char fechaHora4[20] ="2023-05-15 00:00:00";
    crearPartida(entrada11, resultado4, puntaje4, movimientos4, fechaHora4);
}

int main(){
    datosIniciales();
    menuPrincipal();
    //menuEstadisticas();
    
    return 0;
}
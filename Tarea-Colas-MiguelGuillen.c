#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Televisor{
    char marca[50];
    char sonido[50];
    int calidadPantalla;
    double pantalla;
}TELEVISOR;

typedef struct nodo{
    TELEVISOR data;
    struct nodo* sig;
}NODO;

typedef struct cola{
    struct nodo *primero, *ultimo;
}COLA;

NODO *crearNodo(TELEVISOR data){
    NODO *nuevo = (NODO*)malloc(sizeof(NODO));
    nuevo->data = data;
    nuevo->sig = NULL;
    return nuevo;
}

COLA *crearCola(){
    COLA *cola = (COLA*)malloc(sizeof(COLA));
    cola->primero = cola->ultimo = NULL;
    return cola;
}

TELEVISOR *crearTelevisor(char marca[50], char sonido[50], int calidadPantalla, double pantalla){
    TELEVISOR *aux = (TELEVISOR*)malloc(sizeof(TELEVISOR));
    strcpy(aux->marca, marca);
    strcpy(aux->sonido, sonido);
    aux->calidadPantalla = calidadPantalla;
    aux->pantalla = pantalla;
    return aux;
}


void agregarCola(TELEVISOR data, COLA** cola){
    NODO* nuevo = crearNodo(data);
    if((*cola)->primero == NULL){
        (*cola)->primero = (*cola)->ultimo = nuevo;
        return;
    }

    // Ahora si la cola no esta vacia
    (*cola)->ultimo->sig = nuevo;
    (*cola)->ultimo = nuevo;
}

TELEVISOR eliminarCola(COLA** cola){
    if((*cola)->primero == NULL){
        return;
    }

    // SI NO ESTA VACIA
    NODO *eliminado = (*cola)->primero;
    TELEVISOR data = eliminado->data;

    // ELIMINAMOS EL NODO DE LA COLA
    (*cola)->primero = eliminado->sig; 


    if((*cola)->primero == NULL){
        (*cola)->ultimo = NULL;
    }

    free(eliminado);

    return data;
}

void mostrar(COLA** cola){

    if((*cola)->primero == NULL){
        printf("vacio");
        return;
    }

    // DE LO CONTRARIO
    printf("Marca Primero: %s\nMarca Ultimo: %s\n", (*cola)->primero->data.marca, (*cola)->ultimo->data.marca);

    NODO* actual = (*cola)->primero;
    while(actual){
        printf("\n---------\n");
        printf("%s\n", actual->data.marca);
        printf("%s\n", actual->data.sonido);
        printf("%dp\n", actual->data.calidadPantalla);
        printf("%.1f' Pulgadas\n", actual->data.pantalla);
        actual = actual->sig;
        printf("---------\n");
    }
}

int main(){

    COLA *cola = crearCola();

    TELEVISOR *televisor1 = crearTelevisor("LG", "Stereo", 1080, 30);
    TELEVISOR *televisor2 = crearTelevisor("Sony", "Mono",1080, 24);
    TELEVISOR *televisor3 = crearTelevisor("Samsung", "Sonido 3D",1440, 27);
    TELEVISOR *televisor4 = crearTelevisor("Panasonic", "Stereo",2160, 50);
    TELEVISOR *televisor5 = crearTelevisor("Philips", "Cine",4320, 55);
    
    agregarCola(*televisor1, &cola);
    agregarCola(*televisor2, &cola);
    agregarCola(*televisor3, &cola);
    agregarCola(*televisor4, &cola);
    agregarCola(*televisor5, &cola);

    mostrar(&cola);
    eliminarCola(&cola);
    eliminarCola(&cola);
    eliminarCola(&cola);

    printf("---------------------------\n");
    mostrar(&cola);

return 0;
}
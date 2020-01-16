#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Map.h"
#include "lista.h"
#include "funciones.h"
#include "lectura.h"

struct Coordenadas{
    int x;
    int y;
    int z;
};

struct Farmacia{//estructura de la farmacia y cada una de sus categorias
    char* nombre;
    int estado;
    char* tipo_farmacia;
    Coordenadas* coordenadas;
    Map* products_map;
};


struct Producto{
    char* nombre;
    int stock;
    char* tipo_producto;
    int precio;
};

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

Farmacia * crearFarmacia(char * linea){
    Farmacia* farmasita =(Farmacia*)malloc(sizeof(Farmacia));
    farmasita->nombre = (char*)get_csv_field(linea,1);
    farmasita->estado =   (char*)get_csv_field(linea, 2);
    farmasita->tipo_farmacia = (char*)get_csv_field(linea, 3);
    farmasita->coordenadas->x = (char*)get_csv_field(linea, 4);
    farmasita->coordenadas->y = (char*)get_csv_field(linea, 5);
    farmasita->coordenadas->z = (char*)get_csv_field(linea, 6);
    return farmasita;
}

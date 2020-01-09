#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}


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
typedef struct Farmacia{//estructura de la farmacia y cada una de sus categorias
    char nombre[50];
    int estado;
    char tipo_farmacia;
    coordenadas *coordenadas;
    products_map;
}Farmacia;

typedef struct coordenadas{
    int &x;
    int &y;
    int &z;
}coordenadas;

typedef struct Producto{
    char nombre[50];
    int &stock;
    char tipo_producto,
    int &precio;
}Producto;

Farmacia * crearFarmacia(char * linea){
   Farmacia* farmasita =(Cancion*)malloc(sizeof(Cancion));
     farmasita->nombre = (char*)get_csv_field(linea,1);
     farmasita->estado =   (char*)get_csv_field(linea, 2);
     farmasita->tipo_farmacia = (char*)get_csv_field(linea, 3);
     farmasita->coordenadas->x = (char*)get_csv_field(linea, 4);
     farmasita->coordenadas->y = (char*)get_csv_field(linea, 5);
     farmasita->coordenadas->z = (char*)get_csv_field(linea, 6);
     return farmasita;
}

int main() {
//se crea los mapas que vamos a utilizar
    Map * farmacia_map = createMap(stringHash, stringEqual); //buscar farmacia
    Map * products_map = createMap(stringHash,stringEqual); // buscar productos
    Map * tipoF_map = createMap(stringHash,stringEqual); //buscar farmacia por tipo
    Map * tipoProd_map = createMap(stringHash, stringEqual); //buscar prod por tipo
    list *farmacias_genericas=list_create_empty();
    list *farmacias_eco=list_create_empty();
    list *farmacias_natu=list_create_empty();
    list *coordenadas=list_create_empty();
int opcion =0;
int continuar=0;
FILE * fp=NULL;
char linea[100]; //representa una linea a leer para ser utilizada
Farmacia* farmatsia;
int desea;
char nombre_farmacia[50];
do{
// se imprime el menú con cada una de sus opciones
    opcion =0;
    printf("|________________________________________________|\n");
    printf("|INGRESE UNA DE LAS SIGUIENTES OPCIONES          |\n");
    printf("|1.- Ingrese sus coordenadas                     |\n");
    printf("|2.- Buscar Producto (Nombre o Tipo)             |\n");
    printf("|   2.1.- Entregar mejor precio de un producto   |\n");
    printf("|   2.2.- Actualizar precio o stock de Producto  |\n");
    printf("|3.- Buscar farmacias (Tipo o Cercanía)          |\n");
    printf("|   3.1.- Actualizar estado de Farmacia          |\n");
    printf("|4.- Agregar local inexistente a aplicación      |\n");
    printf("|0.- SALIR                                       |\n");
    printf("|________________________________________________|\n");
    scanf("%d",&opcion);
    if (opcion == 1 ){
         printf("Ingrese sus coordenadas de tipo X Y Z");
         scanf("%d %d %d",coordenadas->x,coordenadas->y,coordenadas->z)
         printf("\n Se han cargado sus coordenadas \n");
    }

    if (opcion == 2){//si se selecciona la opción de exportar  musica
        printf("Ingresar el nombre de producto a buscar \n");
        getchar();
        scanf("%90[^\n]s", linea);
        if(searchMap(products_map,linea)!= NULL){//si el producto existe se imprime sus farmacias
            producto = searchMap(products_map,linea);
            printf(" Producto :%s \n Stock(1 Sí | 0 No) : %d \n Tipo : %s \n Precio : %d \n", Producto->nombre, Producto->Stock, Producto->tipo_producto, Producto->precio);
        }else{
            printf("El producto no se encuentra disponible \n");
             }
        printf("Ingresar el tipo de producto a buscar \n");
        getchar();
        scanf("%90[^\n]s", linea);
        if(searchMap(tipoProd_map,linea)!= NULL){//si el producto existe se imprime sus farmacias
            producto = searchMap(tipoProd_map,linea);
            printf(" Producto :%s \n Stock(1 Sí | 0 No) : %d \n Tipo : %s \n Precio : %d \n", Producto->nombre, Producto->Stock, Producto->tipo_producto, Producto->precio);
        }else{
            printf("El producto no se encuentra disponible \n");
             }
        printf("¿Desea entregar el mejor precio de un Producto? |Ingrese 1| ");
        printf("¿Desea actualizar el precio o stock de un Producto? |Ingrese 2|");
        if(continuar==2)
        {
             printf("Indique el precio actualizado del Producto");
             scanf("%d",Producto->precio);
        }
        if(continuar==1)
        {
            if (searchMap(products_map, nombre_producto)== NULL){// si no se encuentra se imprimirán que no esta disponible
                printf("No se encuentra disponible\n");
            }else{
                aux_map = searchMap(products_map,nombre_producto);
                productito = firstMap(aux_map);
                printf("Productos encontrados %s : \n ", nombre_producto);
                while (productito != NULL){//imprimir mientras exista un producto
                    printf("Producto num%d -> %s \n", num,producto->nombre);
                    num++;
                    productito = nextMap(aux_map);
                }
            }
        }
    }

    if (opcion == 3){
    {

    }
}while (opcion != 0);
    return 0;
}

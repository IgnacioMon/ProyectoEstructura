#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "Map.h"
#include "lista.h"
#include "funciones.h"
#include "lectura.h"
#define LINEA 1024
#define DATO 256

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
    char* linea_coordenadas;
    Map* todos_productos;
    Map* productos_tipo;
};


struct Producto{
    char* nombre;
    char* stock;
    char* tipo_producto;
    char* precio;
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

void mostrar(){

    printf("|________________________________________________|\n");
    printf("|INGRESE UNA DE LAS SIGUIENTES OPCIONES          |\n");
    printf("|1.- Ingrese sus coordenadas                     |\n");
    printf("|2.- Buscar farmacias (Nombre o Tipo)            |\n");
    printf("|   2.1.- Actualizar estado de Farmacia          |\n");
    printf("|3.- Buscar Producto (Nombre o Tipo)             |\n");
    printf("|   3.1.- Entregar mejor precio de un producto   |\n");
    printf("|   3.2.- Actualizar precio o stock de Producto  |\n");
    printf("|4.- Agregar local inexistente a aplicación      |\n");
    printf("|0.- SALIR                                       |\n");
    printf("|________________________________________________|\n");
}

Coordenadas* crear_coordenadas(char* linea){
    Coordenadas* coordenadas=malloc(sizeof(Coordenadas));
    coordenadas->x = atoi(get_csv_field(linea,1));
    coordenadas->y = atoi(get_csv_field(linea,2));
    coordenadas->z = atoi(get_csv_field(linea,3));
    return coordenadas;
}

Producto* crear_producto(char*linea){
    Producto* nuevo_producto=calloc(1,sizeof(Producto));
    nuevo_producto->nombre=calloc(100,sizeof(char));
    nuevo_producto->stock=calloc(1,sizeof(int));
    nuevo_producto->tipo_producto=calloc(100,sizeof(char));
    nuevo_producto->precio=calloc(100,sizeof(int));
    const char* nombre=get_csv_field (linea,1);
    const char* stock=get_csv_field (linea,2);
    const char* tipo_producto=get_csv_field (linea,3);
    const char* precio=get_csv_field (linea,4);
    strcpy(nuevo_producto->nombre,nombre);
    strcpy(nuevo_producto->stock,stock);
    strcpy(nuevo_producto->tipo_producto,tipo_producto);
    strcpy(nuevo_producto->precio,precio);
    return nuevo_producto;
}

Farmacia * crearFarmacia(char * linea){
    char dato[DATO];
    list* anticonceptivo=list_create_empty();
    list* antiinflamatorio=list_create_empty();
    list* analgesico=list_create_empty();
    list* antibiotico=list_create_empty();
    list* antialergico=list_create_empty();
    list* preservativo=list_create_empty();
    list* primeros_aux=list_create_empty();
    list* antiviral=list_create_empty();
    Farmacia* nueva =malloc(sizeof(Farmacia));
    nueva->nombre = (char*)get_csv_field(linea,1);
    nueva->estado = atoi(get_csv_field(linea, 2));
    nueva->tipo_farmacia = (char*)get_csv_field(linea, 3);
    strcpy(dato, get_csv_field(linea, 4));
    strcat(dato,",");
    strcat(dato, get_csv_field(linea, 5));
    strcat(dato,",");
    strcat(dato, get_csv_field(linea, 6));
    nueva->coordenadas=crear_coordenadas(dato);
    nueva->linea_coordenadas=calloc(100,sizeof(char));
    strcpy(nueva->linea_coordenadas,dato);
    nueva->todos_productos=createMap(stringHash, stringEqual);
    nueva->productos_tipo=createMap(stringHash, stringEqual);
    insertMap(nueva->productos_tipo,"Anticonceptivo",anticonceptivo);
    insertMap(nueva->productos_tipo,"Antiinflamatorio",antiinflamatorio);
    insertMap(nueva->productos_tipo,"Analgesico",analgesico);
    insertMap(nueva->productos_tipo,"Antibiotico",antibiotico);
    insertMap(nueva->productos_tipo,"Antialergico",antialergico);
    insertMap(nueva->productos_tipo,"Preservativo",preservativo);
    insertMap(nueva->productos_tipo,"Primeros auxilios",primeros_aux);
    insertMap(nueva->productos_tipo,"Antiviral",antiviral);
    return nueva;
}

void cargar_datos_csv(Map* todas_farmacias,Map* farmacias_tipo)
{
    FILE* fp=fopen("farmacias.csv","r+");
    char linea[LINEA];
    Farmacia* nueva_farmacia;
    Producto* producto_agregar;
    list* lista;
    fgets(linea,1023,fp);

    while(fgets(linea,1023,fp)!=NULL)
    {
        nueva_farmacia=crearFarmacia(linea);
        if(searchMap(todas_farmacias,nueva_farmacia->nombre)==NULL)
        {
            insertMap(todas_farmacias,nueva_farmacia->nombre,nueva_farmacia);
            lista=searchMap(farmacias_tipo,nueva_farmacia->tipo_farmacia);
            list_push_front(lista,nueva_farmacia->nombre);
        }

        while(strcmp(fgets(linea,1023,fp),"STOP\n")!=0)
        {
            producto_agregar=crear_producto(linea);
            insertMap(nueva_farmacia->todos_productos,producto_agregar->nombre,producto_agregar);
            lista=searchMap(nueva_farmacia->productos_tipo,producto_agregar->tipo_producto);
            list_push_front(lista,producto_agregar);
        }
    }
    fclose(fp);
}

void buscar_farmacia(Map* todas_farmacias,Map * farmacias_tipo){
    int estado;
    int tipo_busqueda;
    int busqueda=1;
    int continuar;
    char* nombre_farm;
    char dato_farmacia[DATO];
    list* lista_buscada;
    Farmacia* farmacia_buscada;

    while(busqueda==1){
        printf("Seleccione metodo de busqueda: (0) Por nombre / (1) Por tipo\n");
        fflush(stdin);
        scanf("%d",&tipo_busqueda);
        if(tipo_busqueda==0){

            printf("Ingresar el nombre de Farmacia a buscar \n");
            fflush(stdin);
            scanf("%[^\n]s", dato_farmacia);
            if(searchMap(todas_farmacias,dato_farmacia)!= NULL)
            {//si el producto existe se imprime
                farmacia_buscada = searchMap(todas_farmacias,dato_farmacia);

                printf("Farmacia   :%s \nEstado(1 Abierta | 0 Saqueada)  : %d \nTipo    : %s \n",
                farmacia_buscada->nombre, farmacia_buscada->estado, farmacia_buscada->tipo_farmacia);

            }
            else{
                printf("La farmacia no existe.\n");
            }
        }
        else{
            printf("Ingresar el tipo de farmacia a buscar:\n");
            fflush(stdin);
            scanf("%[^\n]s", dato_farmacia);
            if(searchMap(farmacias_tipo,dato_farmacia)!= NULL){
            //si el producto existe se imprime sus farmacias
                lista_buscada = searchMap(farmacias_tipo,dato_farmacia);
                //strcpy(nombre_farm,list_first(lista_buscada));
                nombre_farm=list_first(lista_buscada);
                while(nombre_farm){
                    printf("Farmacia   :%s\n",nombre_farm);
                    nombre_farm=list_next(lista_buscada);
                }
            }
            else{
                printf("Este tipo de farmacia no esta disponible. \n");
            }
        }
        printf("Desea realizar otra busqueda? (1)Si/(0)No\n");
        scanf("%d",&busqueda);
    }
    printf("Para salir ingrese (0) /");
    printf(" Para actualizar el Estado de una farmacia ingrese (1)\n");
    scanf("%d",&continuar);

    while(continuar==1){
        printf("Ingrese el nombre de la farmacia a Actualizar:\n");
        fflush(stdin);
        scanf("%[^\n]s", dato_farmacia);
        if (searchMap(todas_farmacias, dato_farmacia)== NULL){// si no se encuentra se imprimirán que no esta disponible
            printf("La farmacia no existe.\n");
        }
        else{
            farmacia_buscada = searchMap(todas_farmacias,dato_farmacia);
            printf("Se encuentra funcionando o saqueada? |(1) Funcionando - (0) Saqueada|\n");
            scanf("%d",&estado);
            if (estado==1){
                farmacia_buscada->estado=1;
            }
            if (estado==0){
                farmacia_buscada->estado=0;
            }
            printf("Se ha actualizado el estado de la Farmacia.\n");
        }
        printf("Desea actualizar el estado de otra farmacia? (1)Si/(0)No\n");
        scanf("%d",&continuar);
    }
}

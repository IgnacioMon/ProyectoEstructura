#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "lista.h"
#include "funciones.h"


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
    Coordenadas* coordenadas_usuario;
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
             scanf("%d %d %d",&coordenadas_usuario->x,&coordenadas_usuario->y,&coordenadas_usuario->z);
             printf("\n Se han cargado sus coordenadas \n");
        }

        if (opcion == 2){//si se selecciona la opción de exportar  musica
            printf("Ingresar el nombre de producto a buscar \n");
            getchar();
            scanf("%90[^\n]s", linea);
            if(searchMap(products_map,linea)!= NULL){//si el producto existe se imprime sus farmacias
                Producto = searchMap(products_map,linea);
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

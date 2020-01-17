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


int main() {
    //se crea los mapas que vamos a utilizar

    Map * todas_farmacias = createMap(stringHash, stringEqual); //mapa de listas de farmacias por nombre ej:ahumada,cruz verde
    Map * farmacias_tipo = createMap(stringHash,stringEqual); //buscar farmacia por tipo
    list *farmacias_genericas=list_create_empty();
    list *farmacias_eco=list_create_empty();
    list *farmacias_natu=list_create_empty();
    insertMap(farmacias_tipo,"Generica",farmacias_genericas);
    insertMap(farmacias_tipo,"Economica",farmacias_eco);
    insertMap(farmacias_tipo,"Naturista",farmacias_natu);

    //list* lista_buscada;
    //Farmacia* farmacia_buscada;
    Coordenadas* coordenadas_usuario;
    //Producto* producto_buscado;

    //char nombre_farm[DATO];
    char coordenadas_user[LINEA];
    //char dato_farmacia[DATO];
    //char producto[DATO];


    int opcion;


    char X_user[DATO];
    char Y_user[DATO];
    char Z_user[DATO];

    cargar_datos_csv(todas_farmacias,farmacias_tipo);
    mostrar();// se imprime el menú con cada una de sus opciones
    scanf("%d", &opcion);

    while(opcion!=0){
        if (opcion == 1 ){
            printf("Ingrese sus coordenadas de tipo X Y Z\n");
            fflush(stdin);
            printf("Ingrese coordenada X:\n");
            scanf("%s",X_user);
            strcpy(coordenadas_user,X_user);
            strcat(coordenadas_user,",");
            fflush(stdin);
            printf("Ingrese coordenada Y:\n");
            scanf("%s",Y_user);
            strcat(coordenadas_user,Y_user);
            strcat(coordenadas_user,",");
            fflush(stdin);
            printf("Ingrese coordenada Z:\n");
            scanf("%s",Z_user);
            strcat(coordenadas_user,Z_user);
            coordenadas_usuario=crear_coordenadas(coordenadas_user);
            printf("Se han cargado sus coordenadas \n");
            mostrar();
            scanf("%d", &opcion);
        }

        if (opcion == 2){//si se selecciona la opción de buscar producto
            buscar_farmacia(todas_farmacias,farmacias_tipo);
            mostrar();
            scanf("%d", &opcion);
        }


        /*if (opcion == 3){
            printf("Ingrese tipo de busqueda: (0) Por nombre / (1) Por tipo\n");
            scanf("%d",&tipo_busqueda);
            if(tipo_busqueda==0){
                printf("Ingresar el nombre de producto a buscar \n");
                fflush(stdin);
                scanf("%[^\n]s", producto);
                if(searchMap(products_map,producto)!= NULL){//si el producto existe se imprime sus farmacias
                    producto_buscado = searchMap(products_map,linea);
                    printf(" Producto :%s \n Stock(1 Sí | 0 No) : %d \n Tipo : %s \n Precio : %d \n", producto_buscado->nombre, producto_buscado->Stock, producto_buscado->tipo_producto, producto_buscado->precio);
                }else{
                    printf("El producto no se encuentra disponible \n");
                }
            }
            else{
                printf("Ingresar el tipo de producto a buscar \n");
                fflush(stdin);
                scanf("%[^\n]s", producto);
                if(searchMap(tipoProd_map,linea)!= NULL){//si el producto existe se imprime sus farmacias
                    producto_buscado = searchMap(tipoProd_map,linea);
                    printf(" Producto :%s \n Stock(1 Sí | 0 No) : %d \n Tipo : %s \n Precio : %d \n", producto_buscado->nombre, producto_buscado->Stock, producto_buscado->tipo_producto, producto_buscado->precio);
                }else{
                    printf("El producto no se encuentra disponible \n");
                }
            }

            printf("¿Desea entregar el mejor precio de un Producto? |Ingrese 1| ");
            printf("¿Desea actualizar el precio o stock de un Producto? |Ingrese 2|");
            scanf("%d", &continuar);
            if(continuar==2){
                printf("Indique el precio actualizado del Producto");
                scanf("%d",producto_buscado->precio);
            }
            if(continuar==1){
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
            mostrar();
            scanf("%d", &opcion);
        }*/

        /*if (opcion == 4){
            printf("Porfavor ingresar los datos de la Farmacia \n");
            printf("Separando los valores con una coma. \n");
            printf("Ejemplo: Nombre,estado,tipo_farmacia,coordenadas,x,y,z \n");
            scanf("%s", linea);
            farmacia = crearFarmacia(linea);
            if (searchMap(farmacia_map,Farmacia->nombre) ==NULL){
                 insertMap(farmacia_map,Farmacia->nombre,farmacia);
                if(searchMap(products_map, Producto->nombre)==NULL){  // Se busca en el mapa productos si no esta se agrega.
                    insertMap(products_map,Producto->nombre,farmacia);
                    insertMap(tipoProd_map,Producto->tipo_producto, farmacia);
                }
            }
            mostrar();
            scanf("%d", &opcion);
        }*/
    }
    return 0;
    }

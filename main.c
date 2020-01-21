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

    Map* todas_farmacias = createMap(stringHash, stringEqual); //mapa de listas de farmacias por nombre ej:ahumada,cruz verde
    Map* farmacias_tipo = createMap(stringHash,stringEqual);//buscar farmacia por tipo
    Map* todos_productos = createMap(stringHash,stringEqual);
    Map* productos_tipo = createMap(stringHash,stringEqual);
    list* farmacias_coordenadas=list_create_empty();
    list* farmacias_genericas=list_create_empty();
    list* farmacias_eco=list_create_empty();
    list* farmacias_natu=list_create_empty();
    insertMap(farmacias_tipo,"Generica",farmacias_genericas);
    insertMap(farmacias_tipo,"Economica",farmacias_eco);
    insertMap(farmacias_tipo,"Naturista",farmacias_natu);
    list* anticonceptivo=list_create_empty();
    list* antiinflamatorio=list_create_empty();
    list* analgesico=list_create_empty();
    list* antibiotico=list_create_empty();
    list* antialergico=list_create_empty();
    list* preservativo=list_create_empty();
    list* primeros_aux=list_create_empty();
    list* antiviral=list_create_empty();
    insertMap(productos_tipo,"Anticonceptivo",anticonceptivo);
    insertMap(productos_tipo,"Antiinflamatorio",antiinflamatorio);
    insertMap(productos_tipo,"Analgesico",analgesico);
    insertMap(productos_tipo,"Antibiotico",antibiotico);
    insertMap(productos_tipo,"Antialergico",antialergico);
    insertMap(productos_tipo,"Preservativo",preservativo);
    insertMap(productos_tipo,"Primeros auxilios",primeros_aux);
    insertMap(productos_tipo,"Antiviral",antiviral);

    char coordenadas_user[LINEA];
    int opcion=0;
    char X_user[DATO];
    char Y_user[DATO];
    char Z_user[DATO];
    /*
        Se cargan las coordenadas del usuario para el correcto uso de la aplicación
    */
    printf("Ingrese sus coordenadas de tipo X Y Z:\n");
    fflush(stdin);
    printf("Ingrese coordenada X:\n");
    scanf("%s",X_user);
    strcpy(coordenadas_user,X_user);
    strcat(coordenadas_user,",");
    fflush(stdin);
    printf("\nIngrese coordenada Y:\n");
    scanf("%s",Y_user);
    strcat(coordenadas_user,Y_user);
    strcat(coordenadas_user,",");
    fflush(stdin);
    printf("\nIngrese coordenada Z:\n");
    scanf("%s",Z_user);
    strcat(coordenadas_user,Z_user);
    Coordenadas* coordenadas_usuario=crear_coordenadas(coordenadas_user);
    printf("Se han cargado sus coordenadas \n");
    cargar_datos_csv(todas_farmacias,farmacias_tipo,todos_productos,productos_tipo,farmacias_coordenadas);
    mostrar();// se imprime el menú con cada una de sus opciones
    scanf("%d", &opcion);

    while(opcion<0 || opcion>3)
    {
        printf("Ingrese una opcion valida:\n");
        fflush(stdin);
        scanf("%d",&opcion);
    }
    while(opcion!=0)
    {
        if (opcion == 1)
        {//si se selecciona la opción de buscar farmacia
            buscar_farmacia(todas_farmacias,farmacias_tipo,farmacias_coordenadas,coordenadas_usuario);
            mostrar();
            scanf("%d", &opcion);
        }

        if (opcion == 2)
        {//si se busca el producto
            buscar_producto(todas_farmacias,todos_productos, productos_tipo);
            mostrar();
            scanf("%d", &opcion);
        }

        if (opcion == 3)
        { //si se desea agregar una nueva farmacia
            agregar_farmacia(todas_farmacias,farmacias_tipo);
            mostrar();
            scanf("%d", &opcion);
        }
    }

    exportar_datos_csv(todas_farmacias);
    return 0;

}

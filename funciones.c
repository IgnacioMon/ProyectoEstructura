#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include "Map.h"
#include "lista.h"
#include "funciones.h"
#include "lectura.h"
#define LINEA 1024
#define DATO 256
/*
    Estructuras de Datos a ser Utilizadas
*/
struct Coordenadas
{
    int x;
    int y;
    int z;
};

struct Farmacia
{//estructura de la farmacia y cada una de sus categorias
    char* nombre;
    int estado;
    char* tipo_farmacia;
    Coordenadas* coordenadas;
    Map* todos_productos;
    Map* productos_tipo;
};


struct Producto
{
    char* nombre;
    int stock;
    char* tipo_producto;
    int precio;
};

long long stringHash(const void * key)
{
    long long hash = 5381;
    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2)
{
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

/*
    MENÚ utilizado para decidir que necesita hacer el usuario con la aplicación.
*/

void mostrar()
{
    printf("|________________________________________________|                     _____                                 \n");
    printf("|INGRESE UNA DE LAS SIGUIENTES OPCIONES          |                     |    |                                \n");
    printf("|                                                |                IN   |    |  FOR                           \n");
    printf("|1.- Buscar farmacias. (Nombre, tipo o cercania) |                _____|    |_____                           \n");
    printf("|   1.1.- Actualizar estado de Farmacia.         |                |              |                           \n");
    printf("|2.- Buscar Producto. (Nombre o Tipo)            |                |____      ____|                           \n");
    printf("|   2.1.- Actualizar precio o stock de Producto. |                     |    |                                \n");
    printf("|3.- Agregar local inexistente a aplicación.     |                MA   |    |  CIA                           \n");
    printf("|0.- SALIR.                                      |                     |____|                                \n");
    printf("|________________________________________________|                                                         \n\n");
}


/*
    Se crean las coordenadas guardando su memoria y asignandole los valores recibidos del csv
*/
Coordenadas* crear_coordenadas(char* linea)
{
    Coordenadas* coordenadas=malloc(sizeof(Coordenadas));
    coordenadas->x = atoi(get_csv_field(linea,1));
    coordenadas->y = atoi(get_csv_field(linea,2));
    coordenadas->z = atoi(get_csv_field(linea,3));

    return coordenadas;
}

/*
    Funcion que crea un producto, asignandole la memoria necesaria y sus respectivas variables.
*/
Producto* crear_producto(char*linea)
{
    Producto* nuevo_producto=calloc(1,sizeof(Producto));
    nuevo_producto->nombre=calloc(100,sizeof(char));
    nuevo_producto->tipo_producto=calloc(100,sizeof(char));
    const char* nombre=get_csv_field (linea,1);
    nuevo_producto->stock=atoi(get_csv_field (linea,2));
    const char* tipo_producto=get_csv_field (linea,3);
    nuevo_producto->precio=atoi(get_csv_field (linea,4));
    strcpy(nuevo_producto->nombre,nombre);
    strcpy(nuevo_producto->tipo_producto,tipo_producto);

    return nuevo_producto;
}
/*
    Funcion que me crea una farmacia, se crean las listas correspondientes para ser utilizadas
    "nueva" es mi tipo de Dato Farmacia al que se le asignaran las variables para ser retornadas.
*/
Farmacia * crearFarmacia(char * linea)
{
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
/*
  Funcion que carga los datos recibidos del archivo farmacias.csv
  Se crean las variables temporales a utilizar y se va recorriendo las farmacias con sus respectivos productos
  Con estos datos se va llenando cada mapa y lista respectiva.
*/
void cargar_datos_csv(Map* todas_farmacias,Map* farmacias_tipo,Map* all_productos, Map* productos_type,list* farmacias_coordenadas)
{
    FILE* fp=fopen("farmacias.csv","r");
    char linea[LINEA];
    Farmacia* nueva_farmacia;
    Producto* producto_agregar;
    list* lista;
    fgets(linea,1023,fp);
    //Se recorre el archivo hasta que no haya mas lineas
    while(fgets(linea,1023,fp)!=NULL)
    {
        nueva_farmacia=crearFarmacia(linea);

        if(searchMap(todas_farmacias,nueva_farmacia->nombre)==NULL) //Si no esta se agregan
        {
            insertMap(todas_farmacias,nueva_farmacia->nombre,nueva_farmacia);
            lista=searchMap(farmacias_tipo,nueva_farmacia->tipo_farmacia);
            list_push_front(lista,nueva_farmacia->nombre);
            list_push_front(farmacias_coordenadas,nueva_farmacia);
        }

        while(strcmp(fgets(linea,1023,fp),"STOP\n")!=0) //while que distingue el fin de una farmacia para dejar de agregar productos.
        {
            producto_agregar=crear_producto(linea);

            if(searchMap(all_productos,producto_agregar->nombre)==NULL) //si no está entonces se agregan en su respectivo tipo de Dato
            {
                lista=list_create_empty();
                list_push_front(lista,nueva_farmacia->nombre);
                insertMap(all_productos,producto_agregar->nombre,lista);
                lista=searchMap(productos_type,producto_agregar->tipo_producto);
                list_push_front(lista,producto_agregar->nombre);
            }

            else
            {
                lista=searchMap(all_productos,producto_agregar->nombre);
                list_push_front(lista,nueva_farmacia->nombre);
            }

            insertMap(nueva_farmacia->todos_productos,producto_agregar->nombre,producto_agregar);
            lista=searchMap(nueva_farmacia->productos_tipo,producto_agregar->tipo_producto);
            list_push_front(lista,producto_agregar);
        }
    }
    fclose(fp);
}
/*
        Funcion que muestra todos los productos de una farmacia en especifico
        Se recibe la farmacia y mientras hayan productos se muestran.
*/
void mostrar_todos_productos_farmacia(Farmacia* farmacia)
{
    Producto* producto_mostrar;
    producto_mostrar=firstMap(farmacia->todos_productos);

    while(producto_mostrar!=NULL)
    {
        printf("\nProducto    :%s\nStock (1)Si/(0)No :%d\nTipo de producto:  %s\nPrecio  :%d\n",producto_mostrar->nombre,producto_mostrar->stock,
        producto_mostrar->tipo_producto,producto_mostrar->precio);
        producto_mostrar=nextMap(farmacia->todos_productos);
    }
}
/*
    Funcion que muestra los productos por tipo de una farmacia en especifico
    Se recorre y se muestran.
*/
void mostrar_tipo_productos_farmacia(Farmacia* farmacia,char* tipo)
{
    list* lista;
    lista=searchMap(farmacia->productos_tipo,tipo);
    Producto* producto_mostrar;
    producto_mostrar=list_first(lista);

    while(producto_mostrar!=NULL)
    {
        printf("\nProducto    :%s\nStock (1)Si/(0)No :%d\nTipo de producto:  %s\nPrecio  :%d\n",producto_mostrar->nombre,producto_mostrar->stock,
        producto_mostrar->tipo_producto,producto_mostrar->precio);
        producto_mostrar=list_next(lista);
    }
}
/*
    Se busca farmacia a raíz de las coordenadas del usuario
    Se crea el rango que sera considerado cercano y luego si hay farmacias en ese rango se muestran.
*/
void buscar_farmacia_coordenadas(list* lista_farmacias,Coordenadas* coordenadas_usuario)
{
    Farmacia* farmacia;
    int rango_cercania;
    int rangoXU;
    int rangoYU;
    int rangoZU;
    printf("Ingrese el rango de distancia para ser considerado cercano:\n");
    fflush(stdin);
    scanf("%d",&rango_cercania);
    farmacia=list_first(lista_farmacias); //colocamos farmacia en el primer valor de la lista
    int contador=0;
    if(farmacia==NULL)
    {
        printf("No hay farmacias en la Lista.\n");
    }

    else
    {
        while(farmacia!=NULL) //recorremos hasta que lleguemos al final de la lista
        {
            rangoXU=((farmacia->coordenadas->x)-(coordenadas_usuario->x));
            rangoYU=((farmacia->coordenadas->y)-(coordenadas_usuario->y));
            rangoZU=((farmacia->coordenadas->z)-(coordenadas_usuario->z));

            if((fabs(rangoXU)<=rango_cercania)&&(fabs(rangoYU)<=rango_cercania)&&(fabs(rangoZU)<=rango_cercania))
            {
                printf("\nFarmacia   :%s \nEstado(1 Abierta | 0 Saqueada)  : %d \nTipo    : %s \nCoordenadas: X:%d Y:%d Z:%d\n",
                farmacia->nombre, farmacia->estado, farmacia->tipo_farmacia,farmacia->coordenadas->x,
                farmacia->coordenadas->y,farmacia->coordenadas->z);
                contador++;
            }

            farmacia= list_next(lista_farmacias);
        }

        if(contador==0)
        {
            printf("No hay farmacias cercanas a su ubicacion.\n");
        }
    }
}
/*
    Funcion utilizada para la opcion 2 del menú, donde se buscaran las farmacias segun los requerimientos que tenga el
    usuario.
    Se podrán buscar las farmacias por nombre,tipo o cercanía.
        Actualizar el estado de una farmacia
        Mostrar los productos de una farmacia buscada por tipo o mostrarlos todos.
*/
void buscar_farmacia(Map* todas_farmacias,Map * farmacias_tipo, list* lista_farmacias,Coordenadas* coordenadas_usuario)
{
    int estado;
    int tipo_busqueda;
    int busqueda=1;
    int continuar;
    char* nombre_farm;
    char dato_farmacia[DATO];
    list* lista_buscada;
    Farmacia* farmacia_buscada;
    int ver_productos;
    char tipo_productos[DATO];

    while(busqueda==1)
    {
        printf("Seleccione metodo de busqueda: (0) Por nombre / (1) Por tipo / (2) Por cercania\n");
        fflush(stdin);
        scanf("%d",&tipo_busqueda);

        while(tipo_busqueda<0 || tipo_busqueda>2)
        {
            printf("Ingrese una opcion valida:\n");
            fflush(stdin);
            scanf("%d",&tipo_busqueda);
        }

        if(tipo_busqueda==0)
        {
            printf("Ingresar el nombre de Farmacia a buscar:\n");
            fflush(stdin);
            scanf("%[^\n]s", dato_farmacia);

            if(searchMap(todas_farmacias,dato_farmacia)!= NULL)
            {
                farmacia_buscada = searchMap(todas_farmacias,dato_farmacia);
                printf("\nFarmacia   :%s \nEstado(1 Abierta | 0 Saqueada)  : %d \nTipo    : %s \n",
                farmacia_buscada->nombre, farmacia_buscada->estado, farmacia_buscada->tipo_farmacia);
                printf("Desea ver los productos de esta farmacia? (1)Si/(0)No\n");
                fflush(stdin);
                scanf("%d",&continuar);

                while(continuar<0 || continuar>1)
                {
                    printf("Ingrese una opcion valida:\n");
                    fflush(stdin);
                    scanf("%d",&continuar);
                }

                if(continuar==1)
                {
                    printf("Seleccione el metodo de visualizacion.\n(1)Todos los productos.\n(2)Solo un tipo de producto.\n");
                    fflush(stdin);
                    scanf("%d",&ver_productos);

                    while(ver_productos<1 || ver_productos>2)
                    {
                        printf("Ingrese una opcion valida:\n");
                        fflush(stdin);
                        scanf("%d",&ver_productos);
                    }

                    if(ver_productos==1)
                    {
                        mostrar_todos_productos_farmacia(farmacia_buscada);
                    }

                    else
                    {
                        printf("Ingrese el tipo de producto que desea ver:\n");
                        fflush(stdin);
                        scanf("%s",tipo_productos);
                        mostrar_tipo_productos_farmacia(farmacia_buscada,tipo_productos);
                    }
                }
            }

            else
            {
                printf("La farmacia no existe.\n");
            }
        }

        else if(tipo_busqueda==1)
        {
            printf("Ingresar el tipo de farmacia a buscar:\n");
            fflush(stdin);
            scanf("%[^\n]s", dato_farmacia);

            if(searchMap(farmacias_tipo,dato_farmacia)!= NULL)
            {
            //si el producto existe se imprime sus farmacias
                lista_buscada = searchMap(farmacias_tipo,dato_farmacia);
                nombre_farm=list_first(lista_buscada);

                while(nombre_farm)
                {
                    printf("Farmacia   :%s\n",nombre_farm);
                    nombre_farm=list_next(lista_buscada);
                }
            }

            else
            {
                printf("Este tipo de farmacia no esta disponible.\n");
            }
        }

        else
        {
            buscar_farmacia_coordenadas(lista_farmacias,coordenadas_usuario);
        }

        printf("Desea realizar otra busqueda? (1)Si/(0)No\n");
        scanf("%d",&busqueda);
    }

    continuar=0;
    printf("Para salir ingrese (0) / ");
    printf("Para actualizar el Estado de una farmacia ingrese (1).\n");
    scanf("%d",&continuar);

    while(continuar<0 || continuar>1)
    {
        printf("Ingrese una opcion valida:\n");
        fflush(stdin);
        scanf("%d",&continuar);
    }

    while(continuar==1)
    {
        printf("Ingrese el nombre de la farmacia a Actualizar:\n");
        fflush(stdin);
        scanf("%[^\n]s", dato_farmacia);

        if (searchMap(todas_farmacias, dato_farmacia)== NULL)
        {// si no se encuentra se imprimirán que no esta disponible
            printf("La farmacia no existe.\n");
        }

        else
        {
            farmacia_buscada = searchMap(todas_farmacias,dato_farmacia);
            printf("Se encuentra funcionando o saqueada? |(1) Funcionando - (0) Saqueada|\n");
            scanf("%d",&estado);

            while(estado<0 || estado>1)
            {
                printf("Ingrese una opcion valida:\n");
                fflush(stdin);
                scanf("%d",&estado);
            }

            if (estado==1)
            {
                farmacia_buscada->estado=1;
            }

            if (estado==0)
            {
                farmacia_buscada->estado=0;
            }

            printf("Se ha actualizado el estado de la Farmacia.\n");
        }

        printf("Desea actualizar el estado de otra farmacia? (1)Si/(0)No\n");
        scanf("%d",&continuar);
    }
}
/*
    Funcion utilizada para agregar una farmacia a nuestra base de datos
    Se reciben los datos de la farmacia, y se van llenando con sus respectivos datos
*/
void agregar_farmacia(Map* todas_farmacias,Map * farmacias_tipo)
{
    Farmacia* nueva;
    list* lista;
    int continuar=1;
    char datos_farmacias_nueva[LINEA];
    char estado[DATO];
    char tipo[DATO];
    char X[DATO];
    char Y[DATO];
    char Z[DATO];

    while(continuar==1)
    {
        printf("Ingrese los datos de la farmacia.\n");
        printf("Ingrese el nombre de la farmacia:\n");
        fflush(stdin);
        scanf("%[^\n]s",datos_farmacias_nueva);

        if (searchMap(todas_farmacias,datos_farmacias_nueva) ==NULL)
        {
            printf("Ingrese el estado de la farmacia |(1) Funcionando - (0) Saqueada|:\n");
            fflush(stdin);
            scanf("%s",estado);
            strcat(datos_farmacias_nueva,",");
            strcat(datos_farmacias_nueva,estado);
            printf("\nIngrese el tipo de farmacia:\n");
            fflush(stdin);
            scanf("%s",tipo);
            strcat(datos_farmacias_nueva,",");
            strcat(datos_farmacias_nueva,tipo);
            printf("\nIngrese la coordenada X farmacia:\n");
            fflush(stdin);
            scanf("%s",X);
            strcat(datos_farmacias_nueva,",");
            strcat(datos_farmacias_nueva,X);
            printf("\nIngrese la coordenada Y farmacia:\n");
            fflush(stdin);
            scanf("%s",Y);
            strcat(datos_farmacias_nueva,",");
            strcat(datos_farmacias_nueva,Y);
            printf("\nIngrese la coordenada Z farmacia:\n");
            fflush(stdin);
            scanf("%s",Z);
            strcat(datos_farmacias_nueva,",");
            strcat(datos_farmacias_nueva,Z);
            nueva=crearFarmacia(datos_farmacias_nueva);
            insertMap(todas_farmacias,nueva->nombre,nueva);
            lista=searchMap(farmacias_tipo,nueva->tipo_farmacia);
            list_push_front(lista,nueva->nombre);

            printf("\nDesea agregar otra farmacia? (1)Si/No(0)\n");
            scanf("%d",&continuar);

            while(continuar<0 || continuar>1)
            {
                printf("Ingrese una opcion valida:\n");
                fflush(stdin);
                scanf("%d",&continuar);
            }
        }

        else
        {
            printf("Ya existe una farmacia con ese nombre.\n");
            printf("\nDesea agregar otra farmacia? (1)Si/No(0)\n");
            scanf("%d",&continuar);

            while(continuar<0 || continuar>1)
            {
                printf("Ingrese una opcion valida:\n");
                fflush(stdin);
                scanf("%d",&continuar);
            }
        }
    }
}
/*
    Funcion utilizada para buscar productos de las farmacias.
    Se puede hacer busqueda por nombre o tipo, y se avisa del estado del producto segun requerimientos.
    Se pueden actualizar los datos de un producto, como su stock o precio.
*/
void buscar_producto(Map* todas_farmacias,Map* all_productos, Map* productos_type)
{
    Farmacia* farmacia_buscada;
    Producto* producto_actualizado;
    int busqueda;
    int continuar=1;
    char producto_buscado[DATO];
    char local_buscado[DATO];
    char nombre_producto[DATO];
    int nuevo_valor;
    int actualizacion;
    char* nombre_dato;
    list* lista_buscada;

    while(continuar==1)
    {
        printf("Ingrese tipo de busqueda: (0) Por nombre / (1) Por tipo\n");
        scanf("%d",&busqueda);

        while(busqueda<0 || busqueda>1)
        {
            printf("Ingrese una opcion valida:\n");
            fflush(stdin);
            scanf("%d",&busqueda);
        }

        if(busqueda==0)
        {
            printf("\nIngresar el nombre de producto a buscar:\n");
            fflush(stdin);
            scanf("%[^\n]s",producto_buscado);

            if(searchMap(all_productos,producto_buscado)== NULL)
            {//si el producto no existe
                printf("El producto buscado no existe o no se encuentra disponible.\n");
            }
            else
            {
                lista_buscada=searchMap(all_productos,producto_buscado);
                nombre_dato=list_first(lista_buscada);
                printf("Lista de farmacias que trabajan el producto:\n");

                while(nombre_dato!=NULL)
                {
                    printf("\n%s\n",nombre_dato);
                    nombre_dato=list_next(lista_buscada);
                }
            }
        }

        else
        {
            printf("Ingresar el tipo de producto a buscar:\n");
            fflush(stdin);
            scanf("%[^\n]s", producto_buscado);

            if(searchMap(productos_type,producto_buscado)== NULL)
            {//si el producto existe se imprime sus farmacias
                printf("Este tipo de producto no existe o no se encuentra disponible.\n");
            }
            else
            {
                lista_buscada=searchMap(productos_type,producto_buscado);
                nombre_dato=list_first(lista_buscada);

                while(nombre_dato!=NULL)
                {
                    printf("Lista de productos de este tipo:\n");
                    printf("\n%s\n",nombre_dato);
                    nombre_dato=list_next(lista_buscada);
                }
            }
        }

        printf("Desea realizar otra busqueda de producto? Si(1)/(0)No\n");
        scanf("%d",&continuar);

        while(continuar<0 || continuar>1)
        {
            printf("Ingrese una opcion valida:\n");
            fflush(stdin);
            scanf("%d",&continuar);
        }
    }

    continuar=1;

    while(continuar==1)
    {
        printf("Desea actualizar el precio o stock de un Producto? Si(1)/(0)No\n");
        scanf("%d", &continuar);

        while(continuar<0 || continuar>1)
        {
            printf("Ingrese una opcion valida:\n");
            fflush(stdin);
            scanf("%d",&continuar);
        }

        if(continuar==1)
        {
            printf("Para actualizar el precio de un producto ingrese (1) / \n");
            printf("Para actualizar el stock de un producto ingrese (2).\n");
            fflush(stdin);
            scanf("%d",&actualizacion);

            while(actualizacion<1 || actualizacion>2)
            {
                printf("Ingrese una opcion valida:\n");
                fflush(stdin);
                scanf("%d",&actualizacion);
            }
            printf("Indique el nombre del local en el cual actualizara el precio del producto:\n");
            fflush(stdin);
            scanf("%s",local_buscado);
            farmacia_buscada=searchMap(todas_farmacias,local_buscado);
            printf("\nIndique el nombre del producto a actualizar:\n");
            fflush(stdin);
            scanf("%s",nombre_producto);
            producto_actualizado=searchMap(farmacia_buscada->todos_productos,nombre_producto);

            if(actualizacion==1)
            {
                printf("\nIndique el nuevo precio del producto:\n");
                fflush(stdin);
                scanf("%d",&nuevo_valor);
                producto_actualizado->precio=nuevo_valor;
                printf("Producto actualizado.\n");
            }

            else
            {
                printf("\nIndique el stock del producto:\n");
                fflush(stdin);
                scanf("%d",&nuevo_valor);
                producto_actualizado->stock=nuevo_valor;
                printf("Producto actualizado.\n");
            }
        }

        printf("\nDesea realizar otra actualizacion? Si(1)/(0)No\n");
        scanf("%d", &continuar);

        while(continuar<0 || continuar>1)
        {
            printf("Ingrese una opcion valida:\n");
            fflush(stdin);
            scanf("%d",&continuar);
        }
    }
}
/*
    Funcion que exporta todos los cambios hechos una vez que la aplicacion es abierta y ejecutada.
    Se guardaran en farmacias.csv
    Poniendole sus respectivas "," para su correcta utilización.
*/
void exportar_datos_csv(Map* todas_farmacias)
{
    printf("Se va a exportar la informacion a nuestra base de datos.\n");
    printf("Por favor espere...\n");
    FILE* fp = fopen("farmacias.csv", "w");
    Farmacia* exportar = firstMap(todas_farmacias);
    Producto* producto_exportar;
    fputs("Datos",fp);
    fputc('\n',fp);

    while(exportar!=NULL)
    {
        fputs(exportar->nombre,fp);
        fputc(',',fp);
        fprintf(fp,"%d",exportar->estado);
        fputc(',',fp);
        fputs(exportar->tipo_farmacia,fp);
        fputc(',',fp);
        fprintf(fp,"%d",exportar->coordenadas->x);
        fputc(',',fp);
        fprintf(fp,"%d",exportar->coordenadas->y);
        fputc(',',fp);
        fprintf(fp,"%d",exportar->coordenadas->z);
        fputc('\n',fp);
        producto_exportar = firstMap(exportar->todos_productos);

        while(producto_exportar!=NULL)
        {
            fputs(producto_exportar->nombre,fp);
            fputc(',',fp);
            fprintf(fp,"%d",producto_exportar->stock);
            fputc(',',fp);
            fputs(producto_exportar->tipo_producto,fp);
            fputc(',',fp);
            fprintf(fp,"%d",producto_exportar->precio);
            fputc('\n',fp);
            producto_exportar = nextMap(exportar->todos_productos);
        }

        exportar = nextMap(todas_farmacias);
        fputs("STOP",fp);
        fputc('\n',fp);
    }

    fclose(fp);
    printf("\nSe ha exportado correctamente!\nAdios!!");
}

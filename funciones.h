#ifndef funciones_h
#define funciones_h

typedef struct Coordenadas Coordenadas;

typedef struct Farmacia Farmacia;

typedef struct Producto Producto;

char * _strdup (const char *s);

const char *get_csv_field (char * tmp, int i);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

void mostrar();

Coordenadas* crear_coordenadas(char* linea);

Producto* crear_producto(char*linea);

Farmacia * crearFarmacia(char * linea);

void cargar_datos_csv(Map* todas_farmacias,Map* farmacias_tipo);

void buscar_farmacia(Map* todas_farmacias,Map * farmacias_tipo);


#endif // funciones_h

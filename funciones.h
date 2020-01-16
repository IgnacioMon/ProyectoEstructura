#ifndef funciones_h
#define funciones_h

typedef struct Coordenadas Coordenadas;

typedef struct Farmacia Farmacia;

typedef struct Producto Producto;

char * _strdup (const char *s);

const char *get_csv_field (char * tmp, int i);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

Farmacia * crearFarmacia(char * linea);

#endif // funciones_h

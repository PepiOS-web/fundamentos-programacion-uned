#pragma once

const int NUM_EDIFICIOS = 20;
const int NUM_PLANTAS = 5;
const int MAX_NOMBRE = 20;
const int MAX_DIRECCION = 40;

typedef enum TipoCategoria {Superior, Media, Basica};

typedef char Cadena[MAX_NOMBRE + 2];
typedef char CadenaDireccion[MAX_DIRECCION + 2];
typedef int ConfiguracionPlantas[NUM_PLANTAS];

/* Datos que conserva cada edificio. */
typedef struct TipoEdificio {
  bool existe;
  Cadena nombre;
  CadenaDireccion direccion;
  TipoCategoria categoria;
  ConfiguracionPlantas habitaciones;
};

/* Espacio para los veinte edificios. */
typedef TipoEdificio ListaEdificios[NUM_EDIFICIOS];

TipoEdificio ConsultarEdificio(int posicion);

void EditarEdificio();

void InicializarDatosPrueba();

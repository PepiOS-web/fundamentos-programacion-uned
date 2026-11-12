#pragma once
#include "Edificios.h"

const int NUM_CATEGORIAS = 3;
const int TIPOS_APARTAMENTO = 4;

typedef float TablaPrecios[NUM_CATEGORIAS][TIPOS_APARTAMENTO];
typedef float PreciosCategoria[TIPOS_APARTAMENTO];

void EditarPrecios();
float ConsultarPrecio(TipoCategoria categoria, int habitaciones);

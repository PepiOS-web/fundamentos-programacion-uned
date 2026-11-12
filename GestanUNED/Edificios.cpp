#include <stdio.h>
#include <string.h>
#include "Edificios.h"
#include "Reservas.h"

ListaEdificios edificios;

void InicializarDatosPrueba() {
  /* Inicialmente, ninguna posicion contiene un edificio. */
  for (int i = 0; i < NUM_EDIFICIOS; i++) {
    edificios[i].existe = false;
  }

  /* Edificio 1: Norte. */
  edificios[0].existe = true;
  strcpy(edificios[0].nombre, "Norte");
  strcpy(edificios[0].direccion, "Calle Ejemplo 1");
  edificios[0].categoria = Superior;

  edificios[0].habitaciones[0] = 1;
  edificios[0].habitaciones[1] = 2;
  edificios[0].habitaciones[2] = 3;
  edificios[0].habitaciones[3] = 4;
  edificios[0].habitaciones[4] = 1;

  /* Edificio 2: Sur. */
  edificios[1].existe = true;
  strcpy(edificios[1].nombre, "Sur");
  strcpy(edificios[1].direccion, "Calle Ejemplo 2");
  edificios[1].categoria = Media;

  edificios[1].habitaciones[0] = 2;
  edificios[1].habitaciones[1] = 2;
  edificios[1].habitaciones[2] = 3;
  edificios[1].habitaciones[3] = 4;
  edificios[1].habitaciones[4] = 3;
}

TipoEdificio ConsultarEdificio(int posicion){
  return edificios[posicion];
  }

void EditarEdificio(){
  int longitud;
  int id;
  int caracter;
  bool categoriaValida;
  char confirmacion;
  int apartamentos;


  TipoCategoria categoria;
  Cadena txtCategoria;
  Cadena nombre;
  CadenaDireccion direccion;
  ConfiguracionPlantas habitaciones;

  printf("Editar edificio:\n");

  /* Identificador. */
  do {
    printf("    Identificador (n\Numero entre 1 y 20)? ");
    id = 0;

    if (scanf("%d", &id) == EOF) {
      return;
    }

    do {
      caracter = getchar();
    } while (caracter != '\n' && caracter != EOF);

    if (id < 1 || id > 20) {
      printf("    Numero no valido.\n");
    }
  } while (id < 1 || id > 20);

  /* Nombre. */
  do {
    printf("    Nombre (entre 1 y 20 caracteres)? ");

    if (fgets(nombre, MAX_NOMBRE + 2, stdin) == NULL) {
      return;
    }

    longitud = strlen(nombre);

    if (longitud > 0) {
      if (nombre[longitud - 1] == '\n') {
        nombre[longitud - 1] = '\0';
        longitud--;
      }
    }

    if (longitud > MAX_NOMBRE) {
      do {
        caracter = getchar();
      } while (caracter != '\n' && caracter != EOF);
    }

    if (longitud < 1 || longitud > MAX_NOMBRE) {
      printf("    Nombre no valido.\n");
    }
  } while (longitud < 1 || longitud > MAX_NOMBRE);

  /* Configuracion de las cinco plantas. */
  for (int planta = 0; planta < NUM_PLANTAS; planta++) {
    do {
      printf("    Configuracion de planta %d? ", planta + 1);
      habitaciones[planta] = 0;

      if (scanf("%d", &habitaciones[planta]) == EOF) {
        return;
      }

      do {
        caracter = getchar();
      } while (caracter != '\n' && caracter != EOF);

      if (habitaciones[planta] < 1 || habitaciones[planta] > 4) {
        printf("    Configuracion no valida. Introduce de 1 a 4.\n");
      }
    } while (habitaciones[planta] < 1 || habitaciones[planta] > 4);
  }

  /* Categoria. */
  do {
    categoriaValida = true;

    printf("    Categoria apartamentos del edificio (Superior, Media, Basica)? ");

    if (scanf(" %20[^\n]", txtCategoria) == EOF) {
      return;
    }

    do {
      caracter = getchar();
    } while (caracter != '\n' && caracter != EOF);

    if (strcmp(txtCategoria, "Superior") == 0) {
      categoria = Superior;
    }
    else if (strcmp(txtCategoria, "Media") == 0) {
      categoria = Media;
    }
    else if (strcmp(txtCategoria, "Basica") == 0 ||
             strcmp(txtCategoria, "B\240sica") == 0) {
      categoria = Basica;
    }
    else {
      categoriaValida = false;
      printf("    Categoria no valida.\n");
    }
  } while (!categoriaValida);

  /* Direccion. */
  do {
    printf("    Direccion (entre 1 y 40 caracteres)? ");

    if (fgets(direccion, MAX_DIRECCION + 2, stdin) == NULL) {
      return;
    }

    longitud = strlen(direccion);

    if (longitud > 0) {
      if (direccion[longitud - 1] == '\n') {
        direccion[longitud - 1] = '\0';
        longitud--;
      }
    }

    if (longitud > MAX_DIRECCION) {
      do {
        caracter = getchar();
      } while (caracter != '\n' && caracter != EOF);
    }

    if (longitud < 1 || longitud > MAX_DIRECCION) {
      printf("    Direccion no valida.\n");
    }
  } while (longitud < 1 || longitud > MAX_DIRECCION);


  //Datos Instroduciodos//
  printf("\nLos datos introducidos son:\n");
  printf("    Edificio %d. %s - Categoria: ",id , nombre);

  switch(categoria){
    case Superior:
      printf("Superior\n\n");
      break;
    case Media:
      printf("Media\n\n");
      break;
    case Basica:
      printf("B\240sica\n\n");
      break;
    }
  for (int planta = 0; planta < NUM_PLANTAS; planta++) {
    apartamentos = 0;

    switch (habitaciones[planta]) {
      case 1:
        apartamentos = 8;
        break;
      case 2:
        apartamentos = 4;
        break;
      case 3:
        apartamentos = 3;
        break;
      case 4:
        apartamentos = 2;
        break;
    }

    if (habitaciones[planta] == 1) {
      printf("    Planta %d. 1 habitacion por apartamento. %d apartamentos\n",
             planta + 1, apartamentos);
    }
    else {
      printf("    Planta %d. %d habitaciones por apartamento. %d apartamentos\n",
             planta + 1, habitaciones[planta], apartamentos);
    }
  }

    printf("\nIMPORTANTE: Esta opcion borra los datos anteriores.\n");

    do {
      printf("Son correctos los nuevos datos (S/N)? ");


      if (scanf(" %c", &confirmacion) == EOF) {
        return;
      }

      do {
        caracter = getchar();
      } while (caracter != '\n' && caracter != EOF);

      if (confirmacion != 'S' && confirmacion != 's' &&
          confirmacion != 'N' && confirmacion != 'n') {
        printf("Introduce S o N.\n");
      }
    } while (confirmacion != 'S' && confirmacion != 's' &&
             confirmacion != 'N' && confirmacion != 'n');

    if (confirmacion == 'N' || confirmacion == 'n') {
      return;
    }

    BorrarReservasEdificio(id - 1);

    strcpy(edificios[id - 1].nombre, nombre);
    strcpy(edificios[id - 1].direccion, direccion);

    edificios[id - 1].categoria = categoria;

    for (int planta = 0; planta < NUM_PLANTAS; planta++) {
      edificios[id - 1].habitaciones[planta] = habitaciones[planta];
    }

    edificios[id - 1].existe = true;
}

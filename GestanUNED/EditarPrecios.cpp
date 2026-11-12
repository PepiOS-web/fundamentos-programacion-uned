#include <stdio.h>
#include "Precios.h"
#include "Edificios.h"
#include <string.h>

TablaPrecios precios = {
  {200, 400, 600, 800},  /* Superior */
  {150, 300, 450, 600},  /* Media */
  {75, 150, 225, 300}    /* Basica */
};

void EditarPrecios(){
  PreciosCategoria nuevosPrecios;
  TipoCategoria categoria;
  Cadena txtCategoria;
  bool categoriaValida;
  bool preciosCoherentes;
  int caracter;
  int leidos;
  char confirmacion;

  printf("Editar precios:\n\n");

  /* Elegir la categoria. */
  do {
    categoriaValida = true;

    printf("    Categoria a modificar (Superior, Media, Basica)? ");

    if (scanf(" %20[^\n]", txtCategoria) != 1) {
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
      strcpy(txtCategoria, "B\240sica");
    }
    else {
      categoriaValida = false;
      printf("    Categoria no valida.\n");
    }
  } while (!categoriaValida);

  /* Mostrar los precios actuales. */
  for (int habitacion = 0; habitacion < TIPOS_APARTAMENTO; habitacion++) {
    printf("    El precio actual de la categoria %s es: %g euros para %d hab.\n",
           txtCategoria, precios[categoria][habitacion], habitacion + 1);
  }

  /* Leer los nuevos precios sin modificar los anteriores. */
  printf("\nIntroduzca los nuevos precios:\n");

  for (int habitacion = 0; habitacion < TIPOS_APARTAMENTO; habitacion++) {
    do {
      printf("    %s %d hab. : ", txtCategoria, habitacion + 1);
      leidos = scanf("%f", &nuevosPrecios[habitacion]);

      if (leidos == EOF) {
        return;
      }

      do {
        caracter = getchar();
      } while (caracter != '\n' && caracter != EOF);

      if (leidos != 1) {
        printf("    Precio no valido. Introduce un numero.\n");
      }
    } while (leidos != 1);
  }

  /* Comprobar Superior > Media > Basica en cada columna. */
  preciosCoherentes = true;

  for (int habitacion = 0; habitacion < TIPOS_APARTAMENTO; habitacion++) {
    switch (categoria) {
      case Superior:
        if (!(nuevosPrecios[habitacion] > precios[Media][habitacion])) {
          preciosCoherentes = false;
        }
        break;

      case Media:
        if (!(nuevosPrecios[habitacion] < precios[Superior][habitacion] &&
              nuevosPrecios[habitacion] > precios[Basica][habitacion])) {
          preciosCoherentes = false;
        }
        break;

      case Basica:
        if (!(nuevosPrecios[habitacion] < precios[Media][habitacion])) {
          preciosCoherentes = false;
        }
        break;
    }
  }

  if (!preciosCoherentes) {
    printf("\nPrecios incoherentes entre categorias. No se modifican los precios.\n");
    return;
  }

  /* Resumen de los nuevos precios. */
  printf("\nLos nuevos valores de precios para la categoria %s:\n",
         txtCategoria);

  for (int habitacion = 0; habitacion < TIPOS_APARTAMENTO; habitacion++) {
    if (habitacion == 0) {
      printf("    Apartamento 1 habitacion: %g euros/d\241a\n",
             nuevosPrecios[habitacion]);
    }
    else {
      printf("    Apartamento %d habitaciones: %g euros/d\241a\n",
             habitacion + 1, nuevosPrecios[habitacion]);
    }
  }

  /* Confirmar antes de guardar. */
  do {
    printf("Son correctos los nuevos datos (S/N)? ");

    if (scanf(" %c", &confirmacion) != 1) {
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

  /* Guardar solamente la categoria confirmada. */
  for (int habitacion = 0; habitacion < TIPOS_APARTAMENTO; habitacion++) {
    precios[categoria][habitacion] = nuevosPrecios[habitacion];
  }
}

float ConsultarPrecio(TipoCategoria categoria, int habitaciones) {
  if (habitaciones < 1 || habitaciones > TIPOS_APARTAMENTO) {
    return 0;
  }

  return precios[categoria][habitaciones - 1];
}

#include <stdio.h>
#include "CalendarioMes.h"

void CalendarioMes::Iniciar(int nuevoMes, int nuevoAnio) {
  mes = nuevoMes;
  anio = nuevoAnio;
}

int CalendarioMes::DiasMes() {
  int dias = 31;

  if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    dias = 30;
  }

  if (mes == 2) {
    dias = 28;
    if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) {
      dias = 29;
    }
  }

  return dias;
}

/* Lunes = 0, ..., domingo = 6.
   Se adapta la formula de la practica 3.
   El calendario gregoriano repite su distribucion cada 400 anios. */
int CalendarioMes::PrimerDiaSemana() {
  CalendarioMes temporal;
  int anterior;
  int inicio;

  anterior = (anio - 1) % 400;
  inicio = anterior + anterior / 4 - anterior / 100 + anterior / 400;

  for (int m = 1; m < mes; m++) {
    temporal.Iniciar(m, anio);
    inicio = inicio + temporal.DiasMes();
  }

  return inicio % 7;
}

void CalendarioMes::MostrarOcupacion(OcupacionMes ocupacion) {
  int inicio;
  int dias;

  inicio = PrimerDiaSemana();
  dias = DiasMes();

  printf("         ");

  switch (mes) {
    case 1:
      printf("Enero");
      break;
    case 2:
      printf("Febrero");
      break;
    case 3:
      printf("Marzo");
      break;
    case 4:
      printf("Abril");
      break;
    case 5:
      printf("Mayo");
      break;
    case 6:
      printf("Junio");
      break;
    case 7:
      printf("Julio");
      break;
    case 8:
      printf("Agosto");
      break;
    case 9:
      printf("Septiembre");
      break;
    case 10:
      printf("Octubre");
      break;
    case 11:
      printf("Noviembre");
      break;
    case 12:
      printf("Diciembre");
      break;
  }

  printf("         %d\n", anio);
  printf(" L  M  X  J  V  S  D\n");

  for (int columna = 0; columna < inicio; columna++) {
    printf("   ");
  }

  for (int dia = 1; dia <= dias; dia++) {
    printf("%02d ", ocupacion[dia - 1]);

    if ((inicio + dia) % 7 == 0) {
      printf("\n");
    }
  }

  if ((inicio + dias) % 7 != 0) {
    printf("\n");
  }
}

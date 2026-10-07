/** Conversion a Horas Minutos y Segundos
*   Introducidos como Valor **/

#include <stdio.h>

int Conversion(){
  int total,horas,min,seg;

  printf("Segundos Totales: ");
  scanf("%d", &total);

  seg = total % 60;
  min = (total%3600)/60;
  horas = total/3600;

  printf("\nHoras %d, Minutos %d, Segundos %d\n", horas,min,seg);

  return 0;
  }


int main(){
  Conversion();
  }

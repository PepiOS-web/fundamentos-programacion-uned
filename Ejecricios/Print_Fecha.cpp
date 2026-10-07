#include <stdio.h>

typedef char Cadena[21];

int main(){
  int dia;
  Cadena mes;
  int anio;

  printf("Introduce un Dia: ");
  scanf("%d",&dia);

  printf("Introduce un Mes: ");
  scanf("%s", &mes);

  printf("Introduce un Anio: ");
  scanf("%d", &anio);

  printf("\nDia %d de %s de %d\n",dia, mes,anio);
  }

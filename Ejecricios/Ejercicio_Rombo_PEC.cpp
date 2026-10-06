#include <stdio.h>

int main() {
  int lado, filas, ancho, numero;
  printf("�Lado del Rombo?");
  scanf("%d", &lado);
  printf("\n");

  if (lado < 1 || lado > 20) {return 0;}
  filas = 2 * lado;
  if (lado == 1) {filas = 1;}

  for (int fila = 1; fila <= filas; fila++) {
    ancho = fila;
    if (fila > lado) {ancho = 2 * lado - fila;}

    for (int col = ancho; col < lado; col++) {printf(" ");}

    for (int col = 1; col < 2 * ancho; col++) {
      numero = col;
      if (col > ancho) {numero = 2 * ancho - col;}
      if (numero % 2 == 0) {printf(".");}
      else if (numero % 4 == 1) {printf("@");}
      else {printf("o");}
    }
    printf("\n");
  }
  return 0;
}

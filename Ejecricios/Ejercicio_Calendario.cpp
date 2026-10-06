#include <stdio.h>

int DiasMes(int mes, int anno) {
  int dias;
  dias = 31;
  if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { dias = 30; }
  if (mes == 2) {
    dias = 28;
    if (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0)) {
      dias = 29;
    }
  }
  return dias;
}

int main() {
  int mes, anno, anterior, inicio, dias, filas, dia;

  printf("�Mes (1..12)?");
  scanf("%d", &mes);
  printf("�Anio (1601..3000)?");
  scanf("%d", &anno);

  if (mes >= 1 && mes <= 12 && anno >= 1601 && anno <= 3000) {
    anterior = anno - 1;
    inicio = anterior + anterior / 4 - anterior / 100 + anterior / 400;
    for (int m = 1; m < mes; m++) { inicio = inicio + DiasMes(m, anno); }
    inicio = inicio % 7;
    dias = DiasMes(mes, anno);
    filas = (inicio + dias + 6) / 7;

    printf("\n");
    switch (mes) {
      case 1:  printf("%-23s", "ENERO"); break;
      case 2:  printf("%-23s", "FEBRERO"); break;
      case 3:  printf("%-23s", "MARZO"); break;
      case 4:  printf("%-23s", "ABRIL"); break;
      case 5:  printf("%-23s", "MAYO"); break;
      case 6:  printf("%-23s", "JUNIO"); break;
      case 7:  printf("%-23s", "JULIO"); break;
      case 8:  printf("%-23s", "AGOSTO"); break;
      case 9:  printf("%-23s", "SEPTIEMBRE"); break;
      case 10: printf("%-23s", "OCTUBRE"); break;
      case 11: printf("%-23s", "NOVIEMBRE"); break;
      case 12: printf("%-23s", "DICIEMBRE"); break;
    }
    printf("%4d\n===========================\n", anno);
    printf("LU  MA  MI  JU  VI | SA  DO\n===========================\n");

    for (int fila = 0; fila < filas; fila++) {
      for (int col = 0; col < 7; col++) {
        dia = fila * 7 + col - inicio + 1;
        if (col == 5) { printf(" | "); }
        else if (col > 0) { printf("  "); }
        if (dia >= 1 && dia <= dias) { printf("%2d", dia); }
        else { printf(" ."); }
      }
      printf("\n");
    }
  }
  return 0;
}

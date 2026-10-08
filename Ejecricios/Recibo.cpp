/**El objetivo es hacer un programa que nos genere un Recibo
   a traves de la seleccion de unos productos**/

#include <stdio.h>

int main(){
  int cantidad, IVA;
  char codigo;
  float precio, totalIVA, subtotal,total;

  printf("Codigo del Producto: ");
  scanf("%c", &codigo);

  printf("Cantidad: ");
  scanf("%d", &cantidad);

  printf("Precio Unitario: ");
  scanf("%f", &precio);

  printf("IVA aplicable: ");
  scanf("%d", &IVA);

  subtotal = float(cantidad) * precio;
  totalIVA = subtotal + float(IVA)/100.0;
  total = subtotal + totalIVA;

  printf("\n RECIBO DE COMPRA \n");
  printf(" Cantidad   Concepto    Euros/Unidad    Total\n");
  printf(" %d   Producto: %c    %12.2f%12.2f\n\n",
          cantidad,codigo,precio,subtotal);
  printf("%28d%% IVA    %12.2f\n\n", IVA,totalIVA);

  printf("            TOTAL%14.2f\n", total);
  }

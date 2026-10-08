/**Este programa calcula el Area y Volumen de un Cilindro**/
#include <stdio.h>

const float PI = 3.1415926535897932384;

float Volumen(float radio, float altura){
  float res;

  res = PI*radio*radio*altura;

  return res;
  }

float Area(float radio, float altura){
  float res;

  res = (2*PI*radio*altura) + (2*PI*radio*radio);

  return res;
  }

int main(){
  float altura, radio, volumen, area;

  printf("Dame el RADIO: ");
  scanf("%f",&radio);

  printf("\nDame la ALTURA: ");
  scanf("%f",&altura);

  area = Area(radio,altura);
  volumen = Volumen(radio, altura);

  printf("El Area es: %.3f\n", area);
  printf("El Volumen es: %.3f\n", volumen);
  }

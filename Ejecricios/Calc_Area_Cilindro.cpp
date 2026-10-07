/**Calcular el Area de un Cilindro **/
#include <stdio.h>

  int Formula(){
    int altura;
    int radio;
    int res;
    printf("Para calcular el area de un cilindro, necesitamos el RADIO y ALTURA\n\n");
    printf("Dame el RADIO: ");
    scanf("%d", &radio);
    printf("Dame la ALTURA: ");
    scanf("%d", &altura);

    if(altura <= 0 || radio <= 0){
      return -1;
      }
    else{
      res = 2*3.1415*radio*(radio+altura);
      return res;
      }
    }

int main(){

  int resultado;
  resultado = Formula();

  printf("El area del cilindro es: %d\n",resultado);

  }

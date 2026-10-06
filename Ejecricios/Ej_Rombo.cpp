#include <stdio.h>

int main(){
  int lado;
  printf("Lado?");
  scanf("%d",&lado);
  printf("\n");

  for(int linea = 1; linea <= lado; linea ++){

    for(int pos = 1; pos <= lado-linea; pos++){
        printf(" ");
      }
      printf("*");
    for(int pos = 1; pos < linea; pos ++){
        printf(" *");
      }
      printf("\n");
    }


  for(int linea =lado - 1; linea >= 1; linea --){

    for(int pos = 1; pos <= lado-linea; pos++){
        printf(" ");
      }
      printf("*");
    for(int pos = 1; pos < linea; pos ++){
        printf(" *");
      }
      printf("\n");
    }
    return 0;
  }

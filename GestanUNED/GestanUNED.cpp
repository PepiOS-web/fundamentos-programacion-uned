#include <stdio.h>
#include "Edificios.h"
#include "Precios.h"
#include "Reservas.h"

void MostrarMenu(){
      /**Menu INICIO, Procedimiento de Inicio**/
      printf("\nGestanUNED: Gesti\242n de alojamientos\n");
      printf("\n    Editar edificio                         (Pulsar E)\n");
      printf("    Editar precios                          (Pulsar P)\n");
      printf("    Reservar apartamento                    (Pulsar R)\n");
      printf("    Listar reservas de edificio             (Pulsar L)\n");
      printf("    Listar calendario mensual de planta     (Pulsar M)\n");
      printf("    Salir                                   (Pulsar S)\n\n");
      printf("Teclear una opci\242n v\240lida (E|P|R|L|M|S)?");
  }
int main(){
  char opcion; /**Variable para capturar la opcion en el menu**/
  InicializarDatosPrueba();
  do{
      MostrarMenu();
      if (scanf(" %c", &opcion) != 1) {
        return 0;
      }
      /**Selector de opciones**/
      switch(opcion){
        case 'e':
        case 'E':
              EditarEdificio();
              break;
        case 'p':
        case 'P':
              EditarPrecios();
              break;
        case 'r':
        case 'R':
              ReservarApartamento();
              break;
        case 'l':
        case 'L':
              ListarReservasEdificio();
              break;
        case 'm':
        case 'M':
              ListarCalendarioPlanta();
              break;
        /**Salida del Programa**/
        case 'S':
        case 's':
          printf("Hasta luego\n");
          break;
        /**Salida No VALIDA**/
        default:
              printf("Opcion no valida\n");
        }
  }while(opcion != 'S' && opcion != 's');
  }

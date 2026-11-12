#include <stdio.h>
#include <string.h>
#include "Reservas.h"
#include "Edificios.h"
#include "Precios.h"
#include "CalendarioMes.h"

const int MAX_OPCIONES = NUM_EDIFICIOS * NUM_PLANTAS * 8;

typedef struct TipoOpcion {
  int edificio;
  int planta;
  int apartamento;
};

typedef TipoOpcion ListaOpciones[MAX_OPCIONES];

ListaReservas reservas;
int numReservas = 0;


/* Comparar dos fechas completas. */
bool FechaAnterior(TipoFecha primera, TipoFecha segunda) {
  if (primera.anio != segunda.anio) {
    return primera.anio < segunda.anio;
  }

  if (primera.mes != segunda.mes) {
    return primera.mes < segunda.mes;
  }

  return primera.dia < segunda.dia;
}


/* Descartar el resto de la linea introducida. */
void LimpiarEntradaReserva() {
  int caracter;

  do {
    caracter = getchar();
  } while (caracter != '\n' && caracter != EOF);
}


/* Leer un entero y repetir si no se introduce un numero. */
bool LeerEnteroReserva(int &numero) {
  int leidos;

  do {
    leidos = scanf("%d", &numero);

    if (leidos == EOF) {
      return false;
    }

    LimpiarEntradaReserva();

    if (leidos != 1) {
      printf("Introduce un numero entero: ");
    }
  } while (leidos != 1);

  return true;
}


/* Leer una respuesta S/N. */
char LeerConfirmacionReserva() {
  char respuesta;

  do {
    if (scanf(" %c", &respuesta) != 1) {
      return 'N';
    }

    LimpiarEntradaReserva();

    if (respuesta != 'S' && respuesta != 's' &&
        respuesta != 'N' && respuesta != 'n') {
      printf("Introduce S o N: ");
    }
  } while (respuesta != 'S' && respuesta != 's' &&
           respuesta != 'N' && respuesta != 'n');

  return respuesta;
}


/* Leer y validar una fecha utilizando el TAD CalendarioMes. */
bool LeerFechaReserva(TipoFecha &fecha, bool entrada) {
  CalendarioMes calendario;
  Cadena texto;
  bool valida;

  if (entrada) {
    strcpy(texto, "entrada");
  }
  else {
    strcpy(texto, "salida");
  }

  do {
    printf("Datos reserva: Dia %s? ", texto);

    if (!LeerEnteroReserva(fecha.dia)) {
      return false;
    }

    printf("Datos reserva: Mes %s? ", texto);

    if (!LeerEnteroReserva(fecha.mes)) {
      return false;
    }

    printf("Datos reserva: Anio %s? ", texto);

    if (!LeerEnteroReserva(fecha.anio)) {
      return false;
    }

    valida = fecha.anio >= 1 &&
             fecha.mes >= 1 &&
             fecha.mes <= 12;

    if (valida) {
      calendario.Iniciar(fecha.mes, fecha.anio);
      valida = fecha.dia >= 1 &&
               fecha.dia <= calendario.DiasMes();
    }

    if (!valida) {
      printf("Fecha no valida. Introduce de nuevo la fecha completa.\n");
    }
  } while (!valida);

  return true;
}


/* Dias transcurridos desde el 1 de enero del mismo anio. */
int DiasDentroAnio(TipoFecha fecha) {
  CalendarioMes calendario;
  int dias;

  dias = fecha.dia - 1;

  for (int mes = 1; mes < fecha.mes; mes++) {
    calendario.Iniciar(mes, fecha.anio);
    dias = dias + calendario.DiasMes();
  }

  return dias;
}


/* Calcular la duracion sin incluir el dia de salida.
   -1 indica que el intervalo no cabe en un int. */
int DiasReserva(TipoFecha entrada, TipoFecha salida) {
  int anios;
  int bisiestosEntrada;
  int bisiestosSalida;
  int dias;

  anios = salida.anio - entrada.anio;

  if (anios > 2147483647 / 366) {
    return -1;
  }

  bisiestosEntrada = (entrada.anio - 1) / 4 -
                     (entrada.anio - 1) / 100 +
                     (entrada.anio - 1) / 400;

  bisiestosSalida = (salida.anio - 1) / 4 -
                    (salida.anio - 1) / 100 +
                    (salida.anio - 1) / 400;

  dias = anios * 365 + (bisiestosSalida - bisiestosEntrada);
  dias = dias + DiasDentroAnio(salida) - DiasDentroAnio(entrada);

  return dias;
}


/* Comprobar si alguna reserva del mismo apartamento
   coincide con el intervalo solicitado. */
bool ApartamentoDisponible(int edificio, int planta, int apartamento,
                           TipoFecha entrada, TipoFecha salida) {
  for (int i = 0; i < numReservas; i++) {
    if (reservas[i].edificio == edificio &&
        reservas[i].planta == planta &&
        reservas[i].apartamento == apartamento) {

      if (FechaAnterior(entrada, reservas[i].fechaSal) &&
          FechaAnterior(reservas[i].fechaEnt, salida)) {
        return false;
      }
    }
  }

  return true;
}


/* Borrar las reservas de un edificio y conservar las demas. */
void BorrarReservasEdificio(int edificio) {
  int destino;

  destino = 0;

  for (int i = 0; i < numReservas; i++) {
    if (reservas[i].edificio != edificio) {
      reservas[destino] = reservas[i];
      destino++;
    }
  }

  numReservas = destino;
}


/* Opcion R. */
void ReservarApartamento() {
  TipoEdificio edificio;
  TipoFecha fechaEnt;
  TipoFecha fechaSal;
  TipoCategoria categoria;
  TipoReserva nueva;

  ListaOpciones opciones;
  TipoOpcion elegida;
  Cadena txtCategoria;

  bool categoriaValida;
  int habitaciones;
  int apartamentos;
  int numOpciones;
  int seleccion;
  int dias;

  float precioDia;
  float precioTotal;
  char confirmacion;

  seleccion = 0;

  do {
    printf("Reservar apartamento:\n");

    /* Elegir categoria. */
    do {
      categoriaValida = true;

      printf("Elija la categoria a reservar (Superior/Media/Basica): ");

      if (scanf(" %20[^\n]", txtCategoria) != 1) {
        return;
      }

      LimpiarEntradaReserva();

      if (strcmp(txtCategoria, "Superior") == 0) {
        categoria = Superior;
      }
      else if (strcmp(txtCategoria, "Media") == 0) {
        categoria = Media;
      }
      else if (strcmp(txtCategoria, "Basica") == 0 ||
               strcmp(txtCategoria, "B\240sica") == 0) {
        categoria = Basica;
        strcpy(txtCategoria, "Basica");
      }
      else {
        categoriaValida = false;
        printf("Categoria no valida.\n");
      }
    } while (!categoriaValida);

    /* Elegir numero de habitaciones. */
    do {
      printf("Elija el tipo de apartamento (1hab./2hab./3hab./4hab.): ");

      if (!LeerEnteroReserva(habitaciones)) {
        return;
      }

      if (habitaciones < 1 || habitaciones > 4) {
        printf("El tipo debe ser un numero entre 1 y 4.\n");
      }
    } while (habitaciones < 1 || habitaciones > 4);

    /* Leer las dos fechas. */
    if (!LeerFechaReserva(fechaEnt, true)) {
      return;
    }

    if (!LeerFechaReserva(fechaSal, false)) {
      return;
    }

    if (!FechaAnterior(fechaEnt, fechaSal)) {
      printf("El orden de las fechas no es correcto.\n");
      return;
    }

    dias = DiasReserva(fechaEnt, fechaSal);

    if (dias < 1) {
      printf("El intervalo es demasiado largo para calcularlo.\n");
      return;
    }

    /* Confirmar los criterios de busqueda. */
    printf("\nDatos de la Reserva buscada:\n");
    printf("Apartamento de %d ", habitaciones);

    if (habitaciones == 1) {
      printf("habitacion");
    }
    else {
      printf("habitaciones");
    }

    printf(" de categoria %s del %d/%d/%d al %d/%d/%d\n",
           txtCategoria,
           fechaEnt.dia, fechaEnt.mes, fechaEnt.anio,
           fechaSal.dia, fechaSal.mes, fechaSal.anio);

    printf("Son correctos los datos de la reserva (S/N)? ");
    confirmacion = LeerConfirmacionReserva();

    if (confirmacion == 'N' || confirmacion == 'n') {
      return;
    }

    /* Guardar las opciones disponibles. */
    numOpciones = 0;

    for (int i = 0; i < NUM_EDIFICIOS; i++) {
      edificio = ConsultarEdificio(i);

      if (edificio.existe && edificio.categoria == categoria) {
        for (int planta = 0; planta < NUM_PLANTAS; planta++) {
          if (edificio.habitaciones[planta] == habitaciones) {
            apartamentos = 0;

            switch (habitaciones) {
              case 1:
                apartamentos = 8;
                break;

              case 2:
                apartamentos = 4;
                break;

              case 3:
                apartamentos = 3;
                break;

              case 4:
                apartamentos = 2;
                break;
            }

            for (int apartamento = 0; apartamento < apartamentos; apartamento++) {
              if (ApartamentoDisponible(i, planta, apartamento,
                                        fechaEnt, fechaSal)) {
                opciones[numOpciones].edificio = i;
                opciones[numOpciones].planta = planta;
                opciones[numOpciones].apartamento = apartamento;
                numOpciones++;
              }
            }
          }
        }
      }
    }

    if (numOpciones == 0) {
      printf("\nNo hay alojamiento disponible para las fechas, categoria y tipo elegidos.\n");
      return;
    }

    /* Mostrar las opciones numeradas. */
    printf("\nLos apartamentos disponibles son:\n");

    for (int i = 0; i < numOpciones; i++) {
      edificio = ConsultarEdificio(opciones[i].edificio);

      printf("    Opcion %d- Apartamento %c - Planta %d - Edificio %s\n",
             i + 1,
             'A' + opciones[i].apartamento,
             opciones[i].planta + 1,
             edificio.nombre);
    }

    /* Calcular el importe con el precio vigente. */
    precioDia = ConsultarPrecio(categoria, habitaciones);
    precioTotal = precioDia * dias;

    printf("Y el precio total es:\n");

    if (dias == 1) {
      printf("    1 d\241a a %g euros/d\241a - %g euros\n",
             precioDia, precioTotal);
    }
    else {
      printf("    %d d\241as a %g euros/d\241a - %g euros\n",
             dias, precioDia, precioTotal);
    }

    /* Seleccionar una opcion o reiniciar con 0. */
    do {
      printf("Seleccione una opcion entre las disponibles o 0 si desea volver a iniciar la reserva: ");

      if (!LeerEnteroReserva(seleccion)) {
        return;
      }

      if (seleccion < 0 || seleccion > numOpciones) {
        printf("Selecciona un numero entre 0 y %d.\n", numOpciones);
      }
    } while (seleccion < 0 || seleccion > numOpciones);

    if (seleccion != 0) {
      elegida = opciones[seleccion - 1];
      edificio = ConsultarEdificio(elegida.edificio);

      /* Mostrar la reserva elegida. */
      printf("\nReserva seleccionada:\n");

      printf("    Edif. %s. Planta %d - Apartamento %c - %d ",
             edificio.nombre,
             elegida.planta + 1,
             'A' + elegida.apartamento,
             habitaciones);

      if (habitaciones == 1) {
        printf("habitacion\n");
      }
      else {
        printf("habitaciones\n");
      }

      printf("    Fecha entrada: %d/%d/%d\n",
             fechaEnt.dia, fechaEnt.mes, fechaEnt.anio);

      printf("    Fecha salida: %d/%d/%d\n",
             fechaSal.dia, fechaSal.mes, fechaSal.anio);

      printf("    Precio Reserva: %g euros\n", precioTotal);

      /* Confirmacion definitiva. */
      printf("Confirma la reserva (S/N)? ");
      confirmacion = LeerConfirmacionReserva();

      if (confirmacion == 'N' || confirmacion == 'n') {
        return;
      }

      if (numReservas >= MAX_RESERVAS) {
        printf("No se puede guardar: se ha alcanzado la capacidad de reservas.\n");
        return;
      }

      /* Guardar solamente despues de confirmar. */
      nueva.edificio = elegida.edificio;
      nueva.planta = elegida.planta;
      nueva.apartamento = elegida.apartamento;
      nueva.fechaEnt = fechaEnt;
      nueva.fechaSal = fechaSal;
      nueva.precioTotal = precioTotal;

      reservas[numReservas] = nueva;
      numReservas++;

      printf("Reserva confirmada.\n");
      return;
    }
  } while (seleccion == 0);
}

/* Operaciones L y M: reutilizan las reservas y las lecturas del mismo modulo. */

int ApartamentosPorHabitaciones(int habitaciones) {
  int apartamentos = 0;

  switch (habitaciones) {
    case 1:
      apartamentos = 8;
      break;
    case 2:
      apartamentos = 4;
      break;
    case 3:
      apartamentos = 3;
      break;
    case 4:
      apartamentos = 2;
      break;
  }

  return apartamentos;
}

bool LeerEdificioListado(int &id, TipoEdificio &edificio) {
  bool valido;

  do {
    printf("Identificador del edificio? ");
    if (!LeerEnteroReserva(id)) {
      return false;
    }

    valido = id >= 1 && id <= NUM_EDIFICIOS;

    if (valido) {
      edificio = ConsultarEdificio(id - 1);
      valido = edificio.existe;
    }

    if (!valido) {
      printf("El identificador debe corresponder a un edificio creado.\n");
    }
  } while (!valido);

  return true;
}

bool LeerMesAnioListado(int &mes, int &anio, bool calendario) {
  do {
    if (calendario) {
      printf("Seleccion Mes? ");
    }
    else {
      printf("Mes Reservas? ");
    }

    if (!LeerEnteroReserva(mes)) {
      return false;
    }

    if (calendario) {
      printf("Seleccion A\244o? ");
    }
    else {
      printf("A\244o Reservas? ");
    }

    if (!LeerEnteroReserva(anio)) {
      return false;
    }

    if (mes < 1 || mes > 12 || anio < 1) {
      printf("Introduce un mes entre 1 y 12 y un anio positivo.\n");
    }
  } while (mes < 1 || mes > 12 || anio < 1);

  return true;
}

void ListarReservasEdificio() {
  TipoEdificio edificio;
  Cadena categoria;
  int id;
  int mes;
  int anio;
  int apartamentos;
  bool hayReservas;

  printf("Listar reservas de edificio:\n");

  if (!LeerEdificioListado(id, edificio)) {
    return;
  }

  if (!LeerMesAnioListado(mes, anio, false)) {
    return;
  }

  switch (edificio.categoria) {
    case Superior:
      strcpy(categoria, "Superior");
      break;
    case Media:
      strcpy(categoria, "Media");
      break;
    case Basica:
      strcpy(categoria, "B\240sica");
      break;
  }

  printf("\nEl edificio \"%s\" - categoria \"%s\" tiene las siguientes reservas para el mes %d del anio %d:\n",
         edificio.nombre, categoria, mes, anio);

  for (int planta = 0; planta < NUM_PLANTAS; planta++) {
    apartamentos = ApartamentosPorHabitaciones(edificio.habitaciones[planta]);
    hayReservas = false;

    printf("\nPlanta %d. Apartamentos %d hab.\n",
           planta + 1, edificio.habitaciones[planta]);

    for (int apartamento = 0; apartamento < apartamentos; apartamento++) {
      for (int i = 0; i < numReservas; i++) {
        if (reservas[i].edificio == id - 1 &&
            reservas[i].planta == planta &&
            reservas[i].apartamento == apartamento &&
            reservas[i].fechaEnt.mes == mes &&
            reservas[i].fechaEnt.anio == anio) {

          printf("    Apartamento %c - Entrada %d/%d/%d al %d/%d/%d\n",
                 'A' + apartamento,
                 reservas[i].fechaEnt.dia,
                 reservas[i].fechaEnt.mes,
                 reservas[i].fechaEnt.anio,
                 reservas[i].fechaSal.dia,
                 reservas[i].fechaSal.mes,
                 reservas[i].fechaSal.anio);

          hayReservas = true;
        }
      }
    }

    if (!hayReservas) {
      printf("    Sin reservas\n");
    }
  }
}

void ListarCalendarioPlanta() {
  TipoEdificio edificio;
  TipoFecha fechaDia;
  CalendarioMes calendario;
  OcupacionMes ocupacion;

  int id;
  int numeroPlanta;
  int mes;
  int anio;
  int dias;
  int apartamentos;

  bool ocupado;
  char respuesta;

  printf("Listar calendario mensual de planta:\n");

  if (!LeerEdificioListado(id, edificio)) {
    return;
  }

  do {
    printf("Planta numero? ");

    if (!LeerEnteroReserva(numeroPlanta)) {
      return;
    }

    if (numeroPlanta < 1 || numeroPlanta > NUM_PLANTAS) {
      printf("La planta debe estar entre 1 y %d.\n", NUM_PLANTAS);
    }
  } while (numeroPlanta < 1 || numeroPlanta > NUM_PLANTAS);

  apartamentos = ApartamentosPorHabitaciones(edificio.habitaciones[numeroPlanta - 1]);

  do {
    if (!LeerMesAnioListado(mes, anio, true)) {
      return;
    }

    calendario.Iniciar(mes, anio);
    dias = calendario.DiasMes();

    for (int i = 0; i < MAX_DIAS_MES; i++) {
      ocupacion[i] = 0;
    }

    fechaDia.mes = mes;
    fechaDia.anio = anio;

    for (int dia = 1; dia <= dias; dia++) {
      fechaDia.dia = dia;

      for (int apartamento = 0; apartamento < apartamentos; apartamento++) {
        ocupado = false;

        for (int i = 0; i < numReservas; i++) {
          if (reservas[i].edificio == id - 1 &&
              reservas[i].planta == numeroPlanta - 1 &&
              reservas[i].apartamento == apartamento) {

            if (!FechaAnterior(fechaDia, reservas[i].fechaEnt) &&
                FechaAnterior(fechaDia, reservas[i].fechaSal)) {
              ocupado = true;
            }
          }
        }

        if (ocupado) {
          ocupacion[dia - 1]++;
        }
      }
    }

    printf("\nOcupacion Planta: %d - Edificio %s\n",
           numeroPlanta, edificio.nombre);

    if (edificio.habitaciones[numeroPlanta - 1] == 1) {
      printf("Apartamentos de 1 habitacion\n");
    }
    else {
      printf("Apartamentos de %d habitaciones\n",
             edificio.habitaciones[numeroPlanta - 1]);
    }

    calendario.MostrarOcupacion(ocupacion);

    printf("Mostrar otro mes (S/N)? ");
    respuesta = LeerConfirmacionReserva();

  } while (respuesta == 'S' || respuesta == 's');
}

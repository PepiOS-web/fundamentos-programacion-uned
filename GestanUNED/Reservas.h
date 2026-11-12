#pragma once

/* Capacidad de implementacion; no es un limite del enunciado. */
const int MAX_RESERVAS = 10000;

typedef struct TipoFecha {
  int dia;
  int mes;
  int anio;
};

typedef struct TipoReserva {
  int edificio;
  int planta;
  int apartamento;
  TipoFecha fechaEnt;
  TipoFecha fechaSal;
  float precioTotal;
};

typedef TipoReserva ListaReservas[MAX_RESERVAS];

bool FechaAnterior(TipoFecha primera, TipoFecha segunda);
void BorrarReservasEdificio(int edificio);
void ReservarApartamento();
void ListarReservasEdificio();
void ListarCalendarioPlanta();

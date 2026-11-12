#pragma once

const int MAX_DIAS_MES = 31;
typedef int OcupacionMes[MAX_DIAS_MES];

typedef struct CalendarioMes {
  void Iniciar(int nuevoMes, int nuevoAnio);
  int DiasMes();
  int PrimerDiaSemana();
  void MostrarOcupacion(OcupacionMes ocupacion);

  private:
    int mes;
    int anio;
};

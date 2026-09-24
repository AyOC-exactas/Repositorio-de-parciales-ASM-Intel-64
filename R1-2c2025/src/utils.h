#ifndef TEST_H
#define TEST_H

#include "../test_utils/test-utils.h"
#include "./ejs.h"


//*************************************
// Declaraciones de funciones auxiliares para recuperatorio
//*************************************

Mapa crearMapaEjemplo(void);
Mapa crearMapaEjemplo2(void);
Mapa crearMapaTesoros(void);
void liberarMapa(Mapa *mapa);
Habitacion crearHabitacion(uint32_t id, const char *nombre, bool es_tesoro);
void conectarHabitaciones(Habitacion *h1, Habitacion *h2, Accion dir);

#endif

#pragma once
#include <assert.h> //provee la macro assert que evalúa una condición, y si no se cumple provee información diagnóstica y aborta la ejecución
#include <ctype.h> //contiene funciones relacionadas a caracteres, isdigit, islower, tolower...
#include <math.h> //define funciones matemáticas como cos, sin, abs, sqrt, log...
#include <stdbool.h> //contiene las definiciones de datos booleanos, true (1), false (0)
#include <stdint.h> //contiene la definición de tipos enteros ligados a tamaños int8_t, int16_t, uint8_t,...
#include <stdio.h> //encabezado de funciones de entrada y salida fopen, fclose, fgetc, printf, fprintf ...
#include <stdlib.h> //biblioteca estándar, atoi, atof, rand, srand, abort, exit, system, NULL, malloc, calloc, realloc...
#include <string.h> //contiene las funciones relacionadas a strings, memcmp, strcat, memset, memmove, strlen,strstr...
#include <unistd.h> //define constantes y tipos standard, NULL, R_OK, F_OK, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO...

//*************************************
// Declaración de estructuras de el mapa
//*************************************



typedef enum {
    ACC_NORTE = 0,
    ACC_SUR,
    ACC_ESTE,
    ACC_OESTE,
    ACC_CANT
} Accion;

typedef struct {
    char nombre[64]; // asmdef_offset:CONT_NOMBRE_OFFSET
    uint32_t valor;  // asmdef_offset:CONT_VALOR_OFFSET
    char color[32];  // asmdef_offset:CONT_COLOR_OFFSET
    bool es_tesoro;  // asmdef_offset:CONT_ES_TESORO_OFFSET
    float peso;      // asmdef_offset:CONT_PESO_OFFSET
} Contenido;         // asmdef_size:CONT_SIZE

typedef struct {
    uint32_t id;                // asmdef_offset:HAB_ID_OFFSET
    uint32_t vecinos[ACC_CANT]; // asmdef_offset:HAB_VECINOS_OFFSET
    Contenido contenido;        // asmdef_offset:HAB_CONTENIDO_OFFSET
    uint32_t visitas;           // asmdef_offset:HAB_VISITAS_OFFSET
} Habitacion;                   // asmdef_size:HAB_SIZE

typedef struct {
    Habitacion *habitaciones; // asmdef_offset:MAP_HABITACIONES_OFFSET
    uint64_t n_habitaciones;    // asmdef_offset:MAP_N_HABITACIONES_OFFSET
    uint32_t id_entrada;      // asmdef_offset:MAP_ID_ENTRADA_OFFSET
} Mapa;                       // asmdef_size:MAP_SIZE

typedef struct {
    Accion *acciones;       // asmdef_offset:REC_ACCIONES_OFFSET
    uint64_t cant_acciones;   // asmdef_offset:REC_CANT_ACCIONES_OFFSET
} Recorrido;                // asmdef_size:REC_SIZE

//*************************************
// Declaración de funciones de los ejercicios
//*************************************

bool encontrarTesoroEnMapa(Mapa *mapa, Recorrido *rec, uint64_t *acciones_ejecutadas) ;

Recorrido *invertirRecorridoConDirecciones(const Recorrido *rec, uint64_t len);

uint32_t sumarTesoros(Mapa *mapa, uint32_t actual, bool *visitado);

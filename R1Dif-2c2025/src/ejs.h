#pragma once

#include <assert.h>   //provee la macro assert que evalúa una condición, y si no se cumple provee información diagnóstica y aborta la ejecución
#include <ctype.h>    //contiene funciones relacionadas a caracteres, isdigit, islower, tolower...
#include <math.h>     //define funciones matemáticas como cos, sin, abs, sqrt, log...
#include <stdbool.h>  //contiene las definiciones de datos booleanos, true (1), false (0)
#include <stdint.h>   //contiene la definición de tipos enteros ligados a tamaños int8_t, int16_t, uint8_t,...
#include <stdio.h>    //encabezado de funciones de entrada y salida fopen, fclose, fgetc, printf, fprintf ...
#include <stdlib.h>   //biblioteca estándar, atoi, atof, rand, srand, abort, exit, system, NULL, malloc, calloc, realloc...
#include <string.h>   //contiene las funciones relacionadas a strings, memcmp, strcat, memset, memmove, strlen, strstr...
#include <unistd.h>   //define constantes y tipos standard, NULL, R_OK, F_OK, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO...

//*************************************
// Declaración de estructuras
//*************************************

// Enumerado item_kind
typedef enum {
  ITEM_KIND_TENT = 0,
  ITEM_KIND_SLEEPING_BAG,
  ITEM_KIND_ROPE,
  ITEM_KIND_CRAMPONS,
  ITEM_KIND_HARNESS,
  ITEM_KIND_OXYGEN,
  ITEM_KIND_ICE_AXE
} item_kind_t;

// Estructura item
typedef struct {
  item_kind_t kind;  // asmdef_offset:ITEM_KIND_OFFSET
  uint8_t weight;    // asmdef_offset:ITEM_WEIGHT_OFFSET
} item_t;            // asmdef_size:ITEM_SIZE

// Estructura backpack
typedef struct {
  item_t *items;        // asmdef_offset:BACKPACK_ITEMS_OFFSET
  uint8_t max_weight;   // asmdef_offset:BACKPACK_MAX_WEIGHT_OFFSET
  uint32_t item_count;  // asmdef_offset:BACKPACK_ITEM_COUNT_OFFSET
} backpack_t;           // asmdef_size:BACKPACK_SIZE

// Estructura destination
typedef struct {
  char name[25];               // asmdef_offset:DESTINATION_NAME_OFFSET
  item_kind_t *requirements;   // asmdef_offset:DESTINATION_REQUIREMENTS_OFFSET
  uint32_t requirements_size;  // asmdef_offset:DESTINATION_REQUIREMENTS_SIZE_OFFSET
} destination_t;               // asmdef_size:DESTINATION_SIZE

// Estructura event
typedef struct event_t {
  struct event_t *next;               // asmdef_offset:EVENT_NEXT_OFFSET
  destination_t *destination;  // asmdef_offset:EVENT_DESTINATION_OFFSET
} event_t;                     // asmdef_size:EVENT_SIZE

// Estructura itinerary
typedef struct {
  event_t *first;  // asmdef_offset:ITINERARY_FIRST_OFFSET
} itinerary_t;     // asmdef_size:ITINERARY_SIZE

//*******************************
// Declaración de funciones
//*******************************

// Ejercicio 1:
bool canItemFitInBackpack(backpack_t *backpack, item_t *item);

// Ejercicio 2:
void filterPossibleDestinations(itinerary_t *itinerary, backpack_t *backpack);

// Ejercicio 3:
backpack_t *prepareBackpack(itinerary_t *itinerary, uint8_t getItemWeight(item_kind_t));

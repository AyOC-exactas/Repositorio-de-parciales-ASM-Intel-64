/* tests.c para el ejercicio 1: encontrarTesoroEnMapa.
 * Tests del Ejercicio 1 usando estructuras en heap (malloc/free)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../ejs.h"
#include "../utils.h"

/* --- Declaraciones de funciones existentes en tu código (extern) --- */


extern Mapa crearMapaEjemplo(void);
extern Mapa crearMapaEjemplo2(void);
extern Mapa crearMapaTesoros(void);
extern void liberarMapa(Mapa *m); 

/* --- Helpers locales: clonación profunda / constructores en heap --- */

/* Clona (deep copy) el array de habitaciones y el struct Mapa en heap.
   uso memcpy porque mi estructura habitaciòn no tiene punteros !
 */

static Mapa *mapa_clone_and_alloc(const Mapa *src) {
    if (!src) return NULL;
    Mapa *dst = malloc(sizeof(Mapa));
    if (!dst) return NULL;
    dst->n_habitaciones = src->n_habitaciones;
    dst->id_entrada = src->id_entrada;

    if (src->n_habitaciones == 0 || src->habitaciones == NULL) {
        dst->habitaciones = NULL;
        return dst;
    }

    dst->habitaciones = malloc(sizeof(Habitacion) * src->n_habitaciones);
    if (!dst->habitaciones) { free(dst); return NULL; }

    /* Copiamos cada Habitacion por memcpy */
    for (uint64_t i = 0; i < src->n_habitaciones; ++i) {
        memcpy(&dst->habitaciones[i], &src->habitaciones[i], sizeof(Habitacion));
    }
    return dst;
}

/* Libera el Mapa creado por mapa_clone_and_alloc */
static void mapa_free_local(Mapa *m) {
    if (!m) return;
    if (m->habitaciones) {
        free(m->habitaciones);
        m->habitaciones = NULL;
    }
    free(m);
}

/* Crea un Recorrido en heap copiando el array de Accion */
static Recorrido *recorrido_new_from_array(const Accion *acciones, uint64_t n) {
    Recorrido *r = malloc(sizeof(Recorrido));
    if (!r) return NULL;
    r->cant_acciones = n;
    if (n == 0) {
        r->acciones = NULL;
        return r;
    }
    r->acciones = malloc(sizeof(Accion) * n);
    if (!r->acciones) { free(r); return NULL; }
    memcpy(r->acciones, acciones, sizeof(Accion) * n);
    return r;
}

static void recorrido_free_local(Recorrido *r) {
    if (!r) return;
    if (r->acciones) {
        free(r->acciones);
        r->acciones = NULL;
    }
    free(r);
}

/* Wrappers que adaptan tus funciones que devuelven Mapa por valor a Mapa* en heap.

 * Lógica:
 *   1) llamamos a crearMapaX() que posiblemente asigna habitaciones y devuelve un Mapa por valor
 *   2) clonamos a heap (mapa_clone_and_alloc)
 *   3) liberamos el Mapa temporal usando la función original liberarMapa(&tmp) para no filtrar memoria
 *   4) retornamos el Mapa* en heap al caller
 */


static Mapa *crearMapaEjemplo_heap(void) {
    Mapa tmp = crearMapaEjemplo();
    Mapa *m = mapa_clone_and_alloc(&tmp);
    liberarMapa(&tmp);
    return m;
}

static Mapa *crearMapaEjemplo2_heap(void) {
    Mapa tmp = crearMapaEjemplo2();
    Mapa *m = mapa_clone_and_alloc(&tmp);
    liberarMapa(&tmp);
    return m;
}

static Mapa *crearMapaTesoros_heap(void) {
    Mapa tmp = crearMapaTesoros();
    Mapa *m = mapa_clone_and_alloc(&tmp);
    liberarMapa(&tmp);
    return m;
}

/* --- Tests pero ahora adaptados a la estructura en heap --- */

TEST(test_ej1_mapa_simple_recorrido_invalido_y_no_encuentra_tesoro) {
  Mapa *mapa = crearMapaEjemplo_heap();
  TEST_ASSERT(mapa != NULL);

  Accion acciones_temp[] = { ACC_OESTE, ACC_SUR };
  Recorrido *rec = recorrido_new_from_array(acciones_temp, 2);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  bool found = TEST_CALL_B(encontrarTesoroEnMapa, mapa, rec, &acciones_ejecutadas);
  TEST_ASSERT(acciones_ejecutadas == 0);
  TEST_ASSERT(!found);

  recorrido_free_local(rec);
  mapa_free_local(mapa);
}

TEST(test_ej1_mapa_simple_recorrido_valido_y_no_encuentra_tesoro) {
  Mapa *mapa = crearMapaEjemplo_heap();
  TEST_ASSERT(mapa != NULL);

  Accion acciones_temp[] = { ACC_ESTE };
  Recorrido *rec = recorrido_new_from_array(acciones_temp, 1);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  bool found = TEST_CALL_B(encontrarTesoroEnMapa, mapa, rec, &acciones_ejecutadas);
  TEST_ASSERT(acciones_ejecutadas == 1);
  TEST_ASSERT(!found);

  recorrido_free_local(rec);
  mapa_free_local(mapa);
}

TEST(test_ej1_mapa_simple_encuentro_tesoro) {
  Mapa *mapa = crearMapaEjemplo_heap();
  TEST_ASSERT(mapa != NULL);

  Accion acciones_temp[] = { ACC_ESTE, ACC_NORTE };
  Recorrido *rec = recorrido_new_from_array(acciones_temp, 2);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  bool found = TEST_CALL_B(encontrarTesoroEnMapa, mapa, rec, &acciones_ejecutadas);
  TEST_ASSERT(acciones_ejecutadas == 2);
  TEST_ASSERT(found);

  recorrido_free_local(rec);
  mapa_free_local(mapa);
}

TEST(test_ej1_mapa_sin_tesoro_no_encuentro_tesoro) {
  Mapa *mapa = crearMapaEjemplo2_heap();
  TEST_ASSERT(mapa != NULL);

  Accion acciones_temp[] = { ACC_ESTE, ACC_NORTE };
  Recorrido *rec = recorrido_new_from_array(acciones_temp, 2);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  bool found = TEST_CALL_B(encontrarTesoroEnMapa, mapa, rec, &acciones_ejecutadas);
  (void)acciones_ejecutadas;
  TEST_ASSERT(!found);

  recorrido_free_local(rec);
  mapa_free_local(mapa);
}

TEST(test_ej1_mapa_muchos_tesoros_encuentro_1_con_recorrido_largo) {
  Mapa *mapa = crearMapaTesoros_heap();
  TEST_ASSERT(mapa != NULL);

  Accion acciones_temp[] = { ACC_ESTE, ACC_NORTE, ACC_OESTE };
  Recorrido *rec = recorrido_new_from_array(acciones_temp, 3);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  bool found = TEST_CALL_B(encontrarTesoroEnMapa, mapa, rec, &acciones_ejecutadas);
  TEST_ASSERT(found);
  TEST_ASSERT(acciones_ejecutadas == 1);

  recorrido_free_local(rec);
  mapa_free_local(mapa);
}

/* --- main --- */
int main(int argc, char *argv[]) {
  (void)argc; (void)argv;
  printf("Corriendo los tests del ejercicio 1 ...\n");

  test_ej1_mapa_simple_recorrido_invalido_y_no_encuentra_tesoro();
  test_ej1_mapa_simple_recorrido_valido_y_no_encuentra_tesoro();
  test_ej1_mapa_simple_encuentro_tesoro();
  test_ej1_mapa_sin_tesoro_no_encuentro_tesoro();
  test_ej1_mapa_muchos_tesoros_encuentro_1_con_recorrido_largo();

  tests_end("Ejercicio 1 ");
  return 0;
}

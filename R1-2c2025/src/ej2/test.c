
 /* Tests del Ejercicio 2 usando Recorrido en heap (malloc/free) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../ejs.h"
#include "../utils.h"


/* Crea en heap un Recorrido copiando el array de acciones (deep copy de acciones) */
static Recorrido *recorrido_new_from_array(const Accion *acciones, uint64_t n) {
    Recorrido *r = malloc(sizeof(Recorrido));
    if (!r) return NULL;
    r->cant_acciones = n;
    if (n == 0 || acciones == NULL) {
        r->acciones = NULL;
        return r;
    }
    r->acciones = malloc(sizeof(Accion) * n);
    if (!r->acciones) { free(r); return NULL; }
    memcpy(r->acciones, acciones, sizeof(Accion) * n);
    return r;
}

/* Libera un Recorrido creado por recorrido_new_from_array */
static void recorrido_free_local(Recorrido *r) {
    if (!r) return;
    if (r->acciones) {
        free(r->acciones);
        r->acciones = NULL;
    }
    free(r);
}

/* --- Tests --- */

TEST(test_ej2_inversion_vacia) {
  /* Entrada: recorrido vacío (acciones == NULL, cant == 0) en heap */
  Recorrido *rec = recorrido_new_from_array(NULL, 0);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 0;
  Recorrido *vuelta = TEST_CALL_S(invertirRecorridoConDirecciones, rec, acciones_ejecutadas);
  TEST_ASSERT(vuelta == NULL);

  recorrido_free_local(rec);
}

TEST(test_ej2_inversion_sin_recorrido) {
  /* Llamada con NULL como recorrido */
  uint64_t acciones_ejecutadas = 0;
  Recorrido *vuelta = TEST_CALL_S(invertirRecorridoConDirecciones, NULL, acciones_ejecutadas);
  TEST_ASSERT(vuelta == NULL);
}

TEST(test_ej2_inversion_valida) {
  Accion acciones[] = { ACC_OESTE, ACC_SUR, ACC_NORTE, ACC_ESTE };
  Recorrido *rec = recorrido_new_from_array(acciones, 4);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 4;
  Recorrido *vuelta = TEST_CALL_S(invertirRecorridoConDirecciones, rec, acciones_ejecutadas);
  TEST_ASSERT(vuelta != NULL);
  TEST_ASSERT(vuelta->cant_acciones == 4);
  TEST_ASSERT(vuelta->acciones[0] == ACC_OESTE);
  TEST_ASSERT(vuelta->acciones[1] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[2] == ACC_NORTE);
  TEST_ASSERT(vuelta->acciones[3] == ACC_ESTE);

  /* liberar tanto la vuelta (devuelta por la función) como el Recorrido de entrada */
  if (vuelta) {
    free(vuelta->acciones);
    free(vuelta);
  }
  recorrido_free_local(rec);
}

TEST(test_ej2_inversion_valida_todos_mismo) {
  Accion acciones[] = { ACC_NORTE, ACC_NORTE, ACC_NORTE, ACC_NORTE };
  Recorrido *rec = recorrido_new_from_array(acciones, 4);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 4;
  Recorrido *vuelta = TEST_CALL_S(invertirRecorridoConDirecciones, rec, acciones_ejecutadas);
  TEST_ASSERT(vuelta != NULL);
  TEST_ASSERT(vuelta->cant_acciones == 4);
  TEST_ASSERT(vuelta->acciones[0] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[1] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[2] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[3] == ACC_SUR);

  if (vuelta) {
    free(vuelta->acciones);
    free(vuelta);
  }
  recorrido_free_local(rec);
}

TEST(test_ej2_inversion_compleja) {
  Accion acciones[] = {
    ACC_ESTE, ACC_NORTE, ACC_OESTE, ACC_SUR,
    ACC_ESTE, ACC_SUR,  ACC_NORTE, ACC_OESTE,
    ACC_SUR,  ACC_ESTE,  ACC_NORTE, ACC_OESTE,
    ACC_ESTE,  ACC_SUR,  ACC_NORTE, ACC_OESTE
  };
  Recorrido *rec = recorrido_new_from_array(acciones, 16);
  TEST_ASSERT(rec != NULL);

  uint64_t acciones_ejecutadas = 16;
  Recorrido *vuelta = TEST_CALL_S(invertirRecorridoConDirecciones, rec, acciones_ejecutadas);
  TEST_ASSERT(vuelta != NULL);
  TEST_ASSERT(vuelta->cant_acciones == 16);

  TEST_ASSERT(vuelta->acciones[0] == ACC_ESTE);
  TEST_ASSERT(vuelta->acciones[1] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[2] == ACC_NORTE);
  TEST_ASSERT(vuelta->acciones[3] == ACC_OESTE);
  TEST_ASSERT(vuelta->acciones[4] == ACC_ESTE);
  TEST_ASSERT(vuelta->acciones[5] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[6] == ACC_OESTE);
  TEST_ASSERT(vuelta->acciones[7] == ACC_NORTE);
  TEST_ASSERT(vuelta->acciones[8] == ACC_ESTE);
  TEST_ASSERT(vuelta->acciones[9] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[10] == ACC_NORTE);
  TEST_ASSERT(vuelta->acciones[11] == ACC_OESTE);
  TEST_ASSERT(vuelta->acciones[12] == ACC_NORTE);
  TEST_ASSERT(vuelta->acciones[13] == ACC_ESTE);
  TEST_ASSERT(vuelta->acciones[14] == ACC_SUR);
  TEST_ASSERT(vuelta->acciones[15] == ACC_OESTE);

  if (vuelta) {
    free(vuelta->acciones);
    free(vuelta);
  }
  recorrido_free_local(rec);
}



int main(int argc, char *argv[]) {
  (void)argc; (void)argv;
  printf("Corriendo los tests del ejercicio 2 ...\n");

  test_ej2_inversion_vacia();
  test_ej2_inversion_sin_recorrido();
  test_ej2_inversion_valida();
  test_ej2_inversion_valida_todos_mismo();
  test_ej2_inversion_compleja();

  tests_end("Ejercicio 2 finish");
  return 0;
}

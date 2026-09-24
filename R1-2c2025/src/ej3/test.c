#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ejs.h"
#include "../utils.h"

/* Test 1: usar mapa de ejemplo con un tesoro alcanzable -> debe devolver 100 */
TEST(test_ej3_ejemplo_un_tesoro) {
    Mapa mapa = crearMapaEjemplo(); /* en utils: habitación 2 es tesoro con valor 100 */
    bool *visitado = calloc(mapa.n_habitaciones, sizeof(bool));
    TEST_ASSERT(visitado != NULL);

    uint32_t total = TEST_CALL_I(sumarTesoros, &mapa, 0u, visitado);
    TEST_ASSERT(total == 100u); /* la "Cámara del Tesoro" en el ejemplo vale 100 */
    free(visitado);
    liberarMapa(&mapa);
}

/* Test 2: mapa sin tesoros -> 0 */
TEST(test_ej3_ejemplo_sin_tesoros) {
    Mapa mapa = crearMapaEjemplo2(); /* en utils: no hay tesoros */
    bool *visitado = calloc(mapa.n_habitaciones, sizeof(bool));
    TEST_ASSERT(visitado != NULL);

    uint32_t total = TEST_CALL_I(sumarTesoros, &mapa, 0u, visitado);
    TEST_ASSERT(total == 0u);

    free(visitado);
    liberarMapa(&mapa);
}

/* Test 3: mapa con varios tesoros (crearMapaTesoros) -> suma de todos los tesoros livianos */
TEST(test_ej3_multiples_tesoros_conectados) {
    Mapa mapa = crearMapaTesoros(); /* en utils: salas 1 y 3 son tesoros (valor por defecto 100 cada una) */
    bool *visitado = calloc(mapa.n_habitaciones, sizeof(bool));
    TEST_ASSERT(visitado != NULL);

    uint32_t total = TEST_CALL_I(sumarTesoros, &mapa, 0u, visitado);
    /* según crearMapaTesoros, hay dos salas con tesoro alcanzables desde 0:
       valor esperado = 100 + 100 = 200 */
    TEST_ASSERT(total == 200u);

    free(visitado);
    liberarMapa(&mapa);
}

/* Test 4: ciclo en el grafo => no debe contarse dos veces (se usan crearHabitacion + conectarHabitaciones) */
TEST(test_ej3_ciclo_no_recuento_duplicado) {
    Mapa mapa;
    mapa.n_habitaciones = 3u;
    mapa.habitaciones = malloc(sizeof(Habitacion) * mapa.n_habitaciones);
    TEST_ASSERT(mapa.habitaciones != NULL);
    mapa.id_entrada = 0u;

    mapa.habitaciones[0] = crearHabitacion(0u, "A", false);
    mapa.habitaciones[1] = crearHabitacion(1u, "B", true);  /* tesoro (valor por defecto 100 en utils) */
    mapa.habitaciones[2] = crearHabitacion(2u, "C", true);  /* tesoro (valor por defecto 100) */

    /* Conexiones que forman ciclo: 0 <-> 1, 1 <-> 2, 2 <-> 0 */
    conectarHabitaciones(&mapa.habitaciones[0], &mapa.habitaciones[1], ACC_ESTE);
    conectarHabitaciones(&mapa.habitaciones[1], &mapa.habitaciones[2], ACC_SUR);
    conectarHabitaciones(&mapa.habitaciones[2], &mapa.habitaciones[0], ACC_OESTE);

    bool *visitado = calloc(mapa.n_habitaciones, sizeof(bool));
    TEST_ASSERT(visitado != NULL);

    uint32_t total = TEST_CALL_I(sumarTesoros, &mapa, 0u, visitado);
    /* Deben contarse ambos tesoros exactamente una vez: 100 + 100 = 200 */
    TEST_ASSERT(total == 200u);

    free(visitado);
    liberarMapa(&mapa);
}

/* Test 5: tesoro existe pero no es alcanzable desde la habitación inicial -> no se cuenta */
TEST(test_ej3_tesoro_desconectado_no_contar) {
    Mapa mapa;
    mapa.n_habitaciones = 3u;
    mapa.habitaciones = malloc(sizeof(Habitacion) * mapa.n_habitaciones);
    TEST_ASSERT(mapa.habitaciones != NULL);
    mapa.id_entrada = 0u;

    mapa.habitaciones[0] = crearHabitacion(0u, "Entrada", false);
    mapa.habitaciones[1] = crearHabitacion(1u, "SalaCon", false);
    mapa.habitaciones[2] = crearHabitacion(2u, "IslaTesoro", true); /* tesoro aislado */

    /* Solo conectamos 0 <-> 1; la habitación 2 queda desconectada */
    conectarHabitaciones(&mapa.habitaciones[0], &mapa.habitaciones[1], ACC_ESTE);

    bool *visitado = calloc(mapa.n_habitaciones, sizeof(bool));
    TEST_ASSERT(visitado != NULL);

    uint32_t total = TEST_CALL_I(sumarTesoros, &mapa, 0u, visitado);
    /* El tesoro en la habitación 2 no es alcanzable desde 0, por lo que no debe sumarse */
    TEST_ASSERT(total == 0u);

    free(visitado);
    liberarMapa(&mapa);
}

/* -------------------- main -------------------- */

int main(int argc, char *argv[]) {
    printf("Corriendo los tests del ejercicio 3...\n");

    test_ej3_ejemplo_un_tesoro();
    test_ej3_ejemplo_sin_tesoros();
    test_ej3_multiples_tesoros_conectados();
    test_ej3_ciclo_no_recuento_duplicado();
    test_ej3_tesoro_desconectado_no_contar();

    tests_end("Ejercicio 3");
    return 0;
}

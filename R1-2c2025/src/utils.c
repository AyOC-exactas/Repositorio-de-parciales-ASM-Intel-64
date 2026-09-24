#include "utils.h"
#include "ejs.h"

// Mapas de ejemplo para los tests:

Mapa crearMapaEjemplo(void) {
    Mapa mapa;
    mapa.n_habitaciones = 3;
    mapa.habitaciones = malloc(sizeof(Habitacion) * mapa.n_habitaciones);
    if (!mapa.habitaciones) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    mapa.id_entrada = 0;

    mapa.habitaciones[0] = crearHabitacion(0, "Entrada", false);
    mapa.habitaciones[1] = crearHabitacion(1, "Pasillo", false);
    mapa.habitaciones[2] = crearHabitacion(2, "Cámara del Tesoro", true);

    conectarHabitaciones(&mapa.habitaciones[0], &mapa.habitaciones[1], ACC_ESTE);
    conectarHabitaciones(&mapa.habitaciones[1], &mapa.habitaciones[2], ACC_NORTE);

    return mapa;
}


Mapa crearMapaEjemplo2(void) {
    Mapa mapa;
    mapa.n_habitaciones = 3;
    mapa.habitaciones = malloc(sizeof(Habitacion) * mapa.n_habitaciones);
    if (!mapa.habitaciones) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    mapa.id_entrada = 0;

    mapa.habitaciones[0] = crearHabitacion(0, "Entrada", false);
    mapa.habitaciones[1] = crearHabitacion(1, "Pasillo", false);
    mapa.habitaciones[2] = crearHabitacion(2, "Cámara del Tesoro", false);

    conectarHabitaciones(&mapa.habitaciones[0], &mapa.habitaciones[1], ACC_ESTE);
    conectarHabitaciones(&mapa.habitaciones[1], &mapa.habitaciones[2], ACC_NORTE);

    return mapa;
}

Mapa crearMapaTesoros(void) {
    Mapa mapa;
    mapa.n_habitaciones = 5;
    mapa.habitaciones = malloc(sizeof(Habitacion) * mapa.n_habitaciones);
    if (!mapa.habitaciones) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    mapa.id_entrada = 0;

    mapa.habitaciones[0] = crearHabitacion(0, "Entrada", false);
    mapa.habitaciones[1] = crearHabitacion(1, "Sala A", true);
    mapa.habitaciones[2] = crearHabitacion(2, "Sala B", false);
    mapa.habitaciones[3] = crearHabitacion(3, "Sala C", true);
    mapa.habitaciones[4] = crearHabitacion(4, "Sala D", false);

    conectarHabitaciones(&mapa.habitaciones[0], &mapa.habitaciones[1], ACC_ESTE);
    conectarHabitaciones(&mapa.habitaciones[1], &mapa.habitaciones[2], ACC_NORTE);
    conectarHabitaciones(&mapa.habitaciones[2], &mapa.habitaciones[3], ACC_OESTE);
    conectarHabitaciones(&mapa.habitaciones[3], &mapa.habitaciones[4], ACC_SUR);

    return mapa;
}



void liberarMapa(Mapa *mapa) {
    free(mapa->habitaciones);
    mapa->habitaciones = NULL;
    mapa->n_habitaciones = 0;
}

Habitacion crearHabitacion(uint32_t id, const char *nombre, bool es_tesoro) {
    Habitacion h;
    h.id = id;
    for (int i = 0; i < ACC_CANT; ++i) h.vecinos[i] = 99;

    snprintf(h.contenido.nombre, sizeof(h.contenido.nombre), "%s", nombre);
    snprintf(h.contenido.color, sizeof(h.contenido.color), "gris");
    if (es_tesoro == true) {
    h.contenido.valor = 100;
    } else {
    h.contenido.valor = 0;
    }
    if (es_tesoro == true) {
    h.contenido.peso = 2.0f;
    } else {
    h.contenido.peso = 0.5f;
    }
    h.contenido.es_tesoro = es_tesoro;
    h.visitas = 0;
    return h;
}

/*Esta funciòn conecta los nodos bidireccionalmente es decir: si conecto h1 con h2 en la direcciòn dir, tambièn conecta h2 con h1 en la direcciòn opuesta*/

void conectarHabitaciones(Habitacion *h1, Habitacion *h2, Accion dir) {
    if (!h1 || !h2) return;
    h1->vecinos[dir] = h2->id;
    switch (dir) {
        case ACC_NORTE: h2->vecinos[ACC_SUR] = h1->id; break;
        case ACC_SUR:   h2->vecinos[ACC_NORTE] = h1->id; break;
        case ACC_ESTE:  h2->vecinos[ACC_OESTE] = h1->id; break;
        case ACC_OESTE: h2->vecinos[ACC_ESTE] = h1->id; break;
        default: break;
    }
}

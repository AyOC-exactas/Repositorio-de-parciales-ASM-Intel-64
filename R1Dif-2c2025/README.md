# Primer parcial - Arquitectura y Organización del Computador - Comision David

### Segundo cuatrimestre 2025

- [Primer parcial - Arquitectura y Organización del Computador - Comision David](#primer-parcial---arquitectura-y-organización-del-computador---comision-david)
    - [Segundo cuatrimestre 2025](#segundo-cuatrimestre-2025)
- [Normas generales y modalidad de entrega](#normas-generales-y-modalidad-de-entrega)
  - [Régimen de Aprobación](#régimen-de-aprobación)
  - [Conocimientos a evaluar](#conocimientos-a-evaluar)
  - [Compilación y Testeo](#compilación-y-testeo)
  - [Verificación de tests](#verificación-de-tests)
- [Enunciado](#enunciado)
  - [Estructuras para el itinerario](#estructuras-para-el-itinerario)
  - [Estructura para los destinos](#estructura-para-los-destinos)
  - [Estructura para las mochilas](#estructura-para-las-mochilas)
  - [Ejercicio 1](#ejercicio-1)
  - [Ejercicio 2](#ejercicio-2)
  - [Ejercicio 3](#ejercicio-3)

# Normas generales y modalidad de entrega

- El parcial es **INDIVIDUAL**.
- Una vez terminada la evaluación se deberá crear un PR al `main` de su repo desde la branch con la resolución como source.

> [!CAUTION]
> Es importante que no modifiquen los archivos de los tester. Si lo hacen, se nos advertirá y tendremos que desaprobar la entrega automáticamente.
>
> **No se deben modificar manualmente:**
>
> - las carpetas test_utils y .github
> - los Makefiles
> - los test.c (salvo para comentar algún test y después dejarlo como estaba originalmente)

## Régimen de Aprobación

- El parcial es en los laboratorios, usando las compus de los labos o sus propias compus.
- Es a libro abierto, pueden tener todo lo que se les ocurra a disposición. Está totalmente prohibido el uso del celular, internet y chatbots.
- Deberán conectarse a un proxy que limitará su acceso a internet para que únicamente se puedan conectar a GitHub.
- Les proveeremos de un script que deberá ejecutarse al comienzo del parcial y no detenerse hasta haber entregado. Con él nos aseguramos que permanezcan conectados al proxy.
- **Sólo se evalúa programación en Assembly**, **C no se corrige** pero recomendamos que primero planteen una solución en C y después pasarla a Assembly cuando tengan en claro cómo estructurar la solución.
- Las funciones auxiliares que implementen también deben estar en Assembly.
- Para aprobar el parcial deben implementar 2 de los 3 puntos del enunciado y que corran con éxito los tests funcionales, de abi y de memoria (valgrind).
- Vamos a usar herramientas de detección de plagio para asegurarnos de que su entrega sea original.

> [!NOTE]
> El comando `./tester.sh` corre los mismos tests que el juez online. Pueden usarlo para revisar que su parcial vaya a pasar los tests en dicho entorno.

> [!NOTE]
> Durante el parcial estaremos disponibles para resolver consultas de enunciado y para destrabarles si están dando vueltas mucho tiempo en algo que no forma parte de lo evaluado. NO responderemos preguntas teóricas.

## Conocimientos a evaluar

- Uso de memoria dinámica.
- Navegación de punteros.
- Representación binaria de los tipos de datos.
- Manejo de pila.
- Manejo de structs.
- Convención C, ABI, uso de registros.
- Uso del debugger GDB.

## Compilación y Testeo

Para compilar y ejecutar los tests en cada ejercicio se dispone de un archivo
`Makefile`, con los siguientes _targets_:

| Comando              | Descripción                                                                                                 |
| -------------------- | ----------------------------------------------------------------------------------------------------------- |
| `make test_c`        | Genera el ejecutable usando la implementación en C del ejercicio.                                           |
| `make test_asm`      | Genera el ejecutable usando la implementación en ASM del ejercicio.                                         |
| `make test_abi`      | Genera el ejecutable usando la implementación en ASM del ejercicio + archivos necesarios para ABI enforcer. |
| `make run_c`         | Corre los tests usando la implementación en C.                                                              |
| `make run_asm`       | Corre los tests usando la implementación en ASM.                                                            |
| `make run_abi`       | Corre los tests usando la implementación en ASM + ABI enforcer.                                             |
| `make valgrind_c`    | Corre los tests en valgrind usando la implementación en C.                                                  |
| `make valgrind_asm`  | Corre los tests en valgrind usando la implementación en ASM.                                                |
| `make valgrind_abi`  | Corre los tests en valgrind usando la implementación en ASM + ABI enforcer.                                 |
| `make check_offsets` | Corre el chequeo de offsets.                                                                                |
| `make run_main_c`    | Corre main usando la implementación en C.                                                                   |
| `make run_main_asm`  | Corre main usando la implementación en ASM (no corre ABI enforcer).                                         |
| `make clean`         | Borra todo archivo generado por el `Makefile`.                                                              |

## Verificación de tests

Para el parcial, contamos con una máquina de la facultad para correr los tests en un entorno limpio y controlado. La idea es que ustedes trabajen en su branch, haciendo los commits y push que necesiten, hasta tener los tests pasando en su computadora local.

> [!CAUTION]
> Para considerar un ejercicio aprobado, debe pasar los tests **con el comando** `make valgrind_abi`.

Una vez que tengan el parcial para entregar, procedan a revisar su aprobación del siguiente modo:

- Crean un PR de `su branch` a `main` con los cambios a entregar.
- **PARA CORRER LOS TESTS, DEBEN AGREGAR la ETIQUETA (label) "tests" AL PR**, verán en su repositorio que aparece una label `tests` a tal fin.
- Cuando se detecte que agregaron la label, denle uno o dos minutos (puede tardar más si hay muchas personas entregando al mismo tiempo) y se comenzarán a correr los tests. El estado de los mismos se informará en la ventana del PR donde figura el botón para hacer el merge.
- Eventualmente terminarán los tests y dirá si pasaron (aprobado) o no. Pueden revisar el progreso si hacen click en el nombre de la corrida en curso.
- **No hacer el merge a main del PR**.

> [!NOTE]
> Si hacen cambios y quieren volver a correr los tests, deben SACAR LA ETIQUETA, guardar el cambio (pueden refrescar la pagina por ejemplo) Y VOLVER A AGREGAR LA ETIQUETA.

# Enunciado

¡Nos vamos de mochileres! Estamos organizando un viaje con varios destinos a los que nos gustaría visitar. Pero, dado que solo llevamos una mochila, tenemos que organizarnos para ver qué necesitamos llevar a cada destino, y si nos entra todo o no en la mochila.

Armamos un itinerario de viaje y cada destino al que queremos ir requiere de cierto equipamiento. Para representar todo esto, contamos con las siguientes estructuras:

## Estructuras para el itinerario

```C
typedef struct {
  event_t *first;
} itinerary_t;

typedef struct {
  event_t *next;
  destination_t *destination;
} event_t;
```

El itinerario es entonces una lista enlazada de eventos, cuyo primer elemento es apuntado por el campo `first`. Cada evento referencia al evento siguiente mediante el campo `next` y tiene asignado un destino (`destination`), que se representa con el siguiente struct:

## Estructura para los destinos

```C
typedef struct {
  char name[25];
  item_kind_t *requirements;
  uint32_t requirements_size;
} destination_t;
```

Donde cada destino tiene un nombre (`name`), una lista de identificadores de objetos requeridos (`requirements`) para poder visitarlo, y un atributo con la cantiadad de objetos requeridos (`requirements_size`).
Los identificadores de objetos requeridos están definidos con el siguiente enum (recuerden que los elementos de un enum no son más que un entero sin signo de 32 bits):

```C
typedef enum {
  ITEM_KIND_TENT = 0,
  ITEM_KIND_SLEEPING_BAG,
  ITEM_KIND_ROPE,
  ITEM_KIND_CRAMPONS,
  ITEM_KIND_HARNESS,
  ITEM_KIND_OXYGEN,
  ITEM_KIND_ICE_AXE,
} item_kind_t;
```

Además, representamos también las mochilas y los objetos contenidos en ellas:

## Estructura para las mochilas

```C
typedef struct {
  item_t *items;
  uint8_t max_weight;
  uint32_t item_count;
} backpack_t;

typedef struct {
  item_kind_t kind;
  uint8_t weight;
} item_t;
```

Una mochila tiene una lista de objetos que lleva dentro (`items`), la cantidad de objetos (`item_count`) y el peso máximo soportado (`max_weight`). Cada objeto contenido tiene asignados un tipo (`kind`) y un peso (`weight`).

Necesitamos implementar las siguientes funciones para ayudarnos a organizar bien nuestro viaje.

---

## Ejercicio 1

Dada una mochila y un objeto, queremos saber si la mochila soportaría el peso agregado por el objeto al meterlo dentro.

```C
bool canItemFitInBackpack(backpack_t *backpack, item_t *item);
```

Entonces, la función debe retornar:

- `false` si agregar el objeto a la mochila superaría el peso máximo soportado.
- `true` en caso contrario.

> [!NOTE]
> Esta función tan solo corrobora si es posible o no añadir el objeto a la mochila, no debe alterar al objeto ni a la mochila y su contenido de ninguna manera.

---

## Ejercicio 2

Teniendo una mochila armada, queremos quitar de nuestro itinerario aquellos eventos cuyos destinos tienen requisitos que nuestra mochila no cumple, ya que no vamos a poder visitarlos.

```C
void filterPossibleDestinations(itinerary_t *itinerary, backpack_t *backpack);
```

La función debe:

- Alterar el itinerario para que ya no contenga los eventos que no podemos visitar.
- Asegurarse de liberar la memoria asociada a los eventos quitados, incluidos los destinos que tienen asignados.

Cuentan con la siguiente función auxiliar ya implementada que pueden utilizar:

```C
bool backpackContainsItem(backpack_t *backpack, item_kind_t kind);
```

Que dada una mochila y un tipo de objeto, devuelve `true` si la mochila contiene el objeto, `false` sino.

> [!NOTE]
> Recomendamos implementar las siguientes funciones auxiliares:
> - `meetsRequirements(backpack_t *backpack, destination_t *dest)` que, dada una mochila y un destino, devuelva `true` si la mochila cumple con los requisitos del destino, y `false` en caso contrario.
> - `free_event(event_t *event)` que, dado un evento, libere toda la memoria asociada con dicho evento.
>
> Les recordamos que los chequeos de ABI aplican sin hacer distinción entre las funciones pedidas por el enunciado y funciones auxiliares que no interactúen por C. En el contexto del parcial, esperamos que respeten convenciones de ABI en todo momento.

---

## Ejercicio 3

Nos cansamos de hacer tetris con nuestras mochilas y tener que renunciar a algunos destinos. Compramos la mochila más grande de todas (**es decir, con capacidad 255**), con lo que podemos meter todo lo que se nos ocurra. Ahora solo queremos armar una mochila que contenga todo lo necesario. Para eso necesitamos implementar la siguiente función:

```C
backpack_t *prepareBackpack(itinerary_t *itinerary, uint8_t getItemWeight(item_kind_t));
```

Que dado un itinerario y una función para obtener el peso de un tipo de objeto, devuelva una mochila que cumpla con todos los requisitos de los destinos del itinerario. Es decir, contenga todos los objetos requeridos para visitar todos los destinos. Eso sí, no queremos llevar cosas de más, recuerden que, después de todo, la mochila la cargamos al hombro.

La mochila devuelta debe:

- Contener todos los objetos para cumplir con los requisitos.
- No debe contener objetos repetidos.
- No debe contener objetos de más, sólo los necesarios.
- Puede sobrarle espacio.

Cuentan con la siguiente función auxiliar ya implementada (la misma que en el ejercicio 2):

```C
bool backpackContainsItem(backpack_t *, item_kind_t);
```

Que dada una mochila y un tipo de objeto, devuelve `true` si la mochila contiene el objeto y `false` sino.

> [!CAUTION]
> Notar que hay una cantidad finita de objetos distintos posibles. Revisar el enum `item_kind_t`.

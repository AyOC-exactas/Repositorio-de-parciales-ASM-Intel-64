; ------------------------
; Offsets para los structs
; Plataforma: x86_64 (LP64)
; ------------------------

section .data

section .text

; COMPLETAR las definiciones (serán revisadas por ABI enforcer):
; ------------------------
; Contenido
; ------------------------
CONT_NOMBRE_OFFSET      EQU 0        ; char nombre[64]
CONT_VALOR_OFFSET       EQU 0       ; uint32_t valor
CONT_COLOR_OFFSET       EQU 0       ; char color[32]
CONT_ES_TESORO_OFFSET   EQU 0      ; bool es_tesoro
CONT_PESO_OFFSET        EQU 0      ; float peso
CONT_SIZE               EQU 0      ; sizeof(Contenido) (rounded)

; ------------------------
; Habitacion
; ------------------------
HAB_ID_OFFSET          EQU 0         ; uint32_t id
HAB_VECINOS_OFFSET     EQU 0        ; uint32_t vecinos[ACC_CANT]
HAB_CONTENIDO_OFFSET   EQU 0        ; Contenido contenido
HAB_VISITAS_OFFSET     EQU 0       ; uint32_t visitas
HAB_SIZE               EQU 0       ; sizeof(Habitacion)

; ------------------------
; Mapa
; ------------------------
MAP_HABITACIONES_OFFSET    EQU 0     ; Habitacion *habitaciones
MAP_N_HABITACIONES_OFFSET  EQU 0     ; uint64_t n_habitaciones
MAP_ID_ENTRADA_OFFSET      EQU 0    ; uint32_t id_entrada
MAP_SIZE                   EQU 0    ; sizeof(Mapa)

; ------------------------
; Recorrido
; ------------------------
REC_ACCIONES_OFFSET        EQU 0     ; Accion *acciones
REC_CANT_ACCIONES_OFFSET   EQU 0     ; uint64_t cant_acciones
REC_SIZE                  EQU 0     ; sizeof(Recorrido)

; Notar que el enum aparece como puntero, entonces no afecta los offsets

global  sumarTesoros
sumarTesoros
    ret
    

#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

void destruir_int(void* dato) {
    free(dato);
}

void imprimir_int(void* dato) {
  printf("%d ", *((int *)dato));
}

int main() {
    GList lista = glist_crear();
    int* uno = malloc(sizeof(int));
    *uno = 1;
    int* dos = malloc(sizeof(int));
    *dos = 2;
    int* zero = malloc(sizeof(int));
    *zero = 0;
    lista = glist_insertar_inicio(lista, uno);
    lista = glist_insertar_final(lista, dos);
    lista = glist_insertar_inicio(lista, zero);
    glist_recorrer(lista, imprimir_int);
    glist_destruir(lista, destruir_int);
    return 0;
}

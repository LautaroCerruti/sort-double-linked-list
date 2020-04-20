#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

void destruir_int(int dato) {
    free(dato);
}

int main() {
    GList lista = gList_crear();
    lista = gList_insertar_inicio(lista, 1);
    lista = gList_insertar_final(lista, 2);
    lista = gList_insertar_inicio(lista, 0);
    gList_destruir(lista, destruir_int);
    return 0;
}

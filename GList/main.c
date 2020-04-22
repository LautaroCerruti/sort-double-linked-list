#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

void destruir_int(void* dato) {
    free(dato);
}

void imprimir_int(void* dato) {
  printf("%d ", *((int *)dato));
}

int menor_int(void* dato1, void* dato2) {
  int resultado;
  int *numero1 = (int *)dato1, *numero2 = (int *)dato2;
  if (*numero1 < *numero2)
    resultado = -1;
  if (*numero1 == *numero2)
    resultado = 0;
  if (*numero1 > *numero2)
    resultado = 1;
  return resultado;
}

int main() {
    GList lista = glist_crear();
    int* uno = malloc(sizeof(int));
    *uno = 1;
    int* dos = malloc(sizeof(int));
    *dos = 2;
    int* zero = malloc(sizeof(int));
    *zero = 0;
    int* tres = malloc(sizeof(int));
    *tres = 3;
    int* cuatro = malloc(sizeof(int));
    *cuatro = 4;
    int* cinco = malloc(sizeof(int));
    *cinco = 5;
    lista = glist_insertar_final(lista, dos);
    lista = glist_insertar_final(lista, cuatro);
    lista = glist_insertar_final(lista, tres);
    lista = glist_insertar_inicio(lista, zero);
    lista = glist_insertar_inicio(lista, uno);
    lista = glist_insertar_final(lista, cinco);
    glist_recorrer(lista, imprimir_int);
    printf("\n");
    lista = glist_merge_sort(lista, menor_int);
    glist_recorrer(lista, imprimir_int);
    GNodo* nodo = glist_pop(&lista, 0);
    printf("\nnodo: %d\n", *((int *)nodo->dato));
    glist_recorrer(lista, imprimir_int);
    free(nodo);
    glist_destruir(lista, destruir_int);
    return 0;
}

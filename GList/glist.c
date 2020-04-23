#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

GList glist_crear() {
    return NULL;
}

void glist_destruir(GList lista, Destruir function) {
  GNodo* nodoAux;
  GNodo* anterior = lista->ant;
  for (; lista != anterior; lista = nodoAux) {
    nodoAux = lista->sig;
    function(lista->dato);
    free(lista);
  }
  function(lista->dato);
  free(lista);
}

void glist_destroy_copy(GList lista) {
  GNodo* nodoAux;
  GNodo* anterior = lista->ant;
  for (; lista != anterior; lista = nodoAux) {
    nodoAux = lista->sig;
    free(lista);
  }
  free(lista);
}

GNodo* glist_pop(GList* lista, int pos) {
  GNodo* nodo = glist_crear();
  if (lista) {
    if ((*lista)->sig == *lista) {
      nodo = *lista;
      lista = NULL;
    } else {
      nodo = *lista;
      for (; nodo->sig != (*lista) && pos != 0; nodo = nodo->sig, --pos);
      if (pos == 0) {
        *lista = nodo->sig;
        nodo->ant->sig = nodo->sig;
        nodo->sig->ant = nodo->ant;
        nodo->sig = nodo;
        nodo->ant = nodo;
      }
    }
  }
  return nodo;
}

GList glist_concat(GList lista1, GList lista2) {
  if (!lista1)
    return lista2;
  if (!lista2)
    return lista1;
  lista1->ant->sig = lista2;
  lista2->ant->sig = lista1;
  GList temp = lista1->ant;
  lista1->ant = lista2->ant;
  lista2->ant = temp;
  return lista1;
}

GList glist_insertar_final(GList lista, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;
  nodo->ant = nodo;
  nodo->sig = nodo;

  return glist_concat(lista, nodo);
}

GList glist_copy(GList lista) {
  GList newList = glist_crear();
  GNodo* node = lista;
  if (lista) {
    for (;node->sig != lista; node = node->sig)
      newList = glist_insertar_final(newList, node->dato);
    newList = glist_insertar_final(newList, node->dato);
  }
  return newList;
}

void glist_imprimir_archivo(FILE* salida, GList lista, FuncionVisitante function) {
  if (lista) {
    function(salida, lista->dato);
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; nodoAux = nodoAux->sig)
      function(salida, nodoAux->dato);
  }
}

void glist_swap(GNodo* nodo1, GNodo* nodo2) {
  void* dato = nodo2->dato;
  nodo2->dato = nodo1->dato;
  nodo1->dato = dato;
}

GList glist_selection_sort(GList lista, Compara function) {
  if (lista) {
    GNodo* nodoAux = lista;
    for (; nodoAux != lista->ant; nodoAux = nodoAux->sig) {
      GNodo* nodoASwapear = nodoAux;
      GNodo* nodo = nodoAux->sig;
      for (; nodo != lista; nodo = nodo->sig) 
        if (function(nodo->dato, nodoASwapear->dato) < 0)
          nodoASwapear = nodo;
      if (nodoAux != nodoASwapear) {
        glist_swap(nodoAux, nodoASwapear);
      }
    }
  }
  return lista;
}

GList glist_insertion_sort(GList lista, Compara function) {
  if (lista) {
    GNodo* nodoAux = lista->sig;
    do {
      GNodo* nodo = nodoAux->ant;
      GNodo* nodoHastaSwapear = glist_crear();
      for (; function(nodo->dato, nodoAux->dato) > 0 && nodo != lista->ant;
          nodo = nodo->ant);
      if (function(nodo->dato, nodoAux->dato) != 1) {
        nodoHastaSwapear = nodo->sig;
      } else {
        nodoHastaSwapear = nodo;
      }
      GNodo* nuevaUltimaPos = nodoAux->sig;
      for (; nodoAux != nodoHastaSwapear; nodoAux = nodoAux->ant)
        glist_swap(nodoAux, nodoAux->ant);
      nodoAux = nuevaUltimaPos;
    } while (nodoAux != lista);
  }
  return lista;
}

GList glist_merge(GList lista1, GList lista2, Compara function) {
  if (!lista1)
    return lista2;
  if (!lista2)
    return lista1;
  if (function(lista1->dato, lista2->dato) < 0) {
    if (lista1 == lista1->sig) {
      lista1 = glist_concat(lista1, lista2);
    } else {
      GNodo* nodoAux = glist_pop(&lista1, 0);
      lista1 = glist_merge(lista1, lista2, function);
      lista1 = glist_concat(nodoAux, lista1);
    }
    return lista1;
  } else {
    if (lista2 == lista2->sig) {
      lista2 = glist_concat(lista2, lista1);
    } else {
      GNodo* nodoAux = glist_pop(&lista2, 0);
      lista2 = glist_merge(lista1, lista2, function);
      lista2 = glist_concat(nodoAux, lista2);
    }
    return lista2;
  }
}

GList glist_split(GList lista) {
  GNodo* nodo1 = lista;
  GNodo* nodo2 = lista;
  for (; nodo1->sig != lista && nodo1->sig->sig != lista;
      nodo1 = nodo1->sig->sig, nodo2 = nodo2->sig);
  GList listaNueva = nodo2->sig;
  lista->ant->sig = listaNueva;
  listaNueva->ant = lista->ant;
  lista->ant = nodo2;
  nodo2->sig = lista;
  return listaNueva;
}

GList glist_merge_sort(GList lista, Compara function) {
  if (!lista || lista->sig == lista)
    return lista;
  GList lista2 = glist_split(lista);

  lista = glist_merge_sort(lista, function);
  lista2 = glist_merge_sort(lista2, function);

  return glist_merge(lista, lista2, function);
}

void glist_test_sort_algorithm(char* nombreArchivo, GList lista, SortAlgorithm sort,
  Compara functionCompare, FuncionVisitante functionVisit) {
  GList copiaLista = glist_copy(lista);
  clock_t t = clock();
  copiaLista = sort(copiaLista, functionCompare);
  t = clock() - t;
  double tiempoSegundos = ((double)t)/CLOCKS_PER_SEC;
  FILE* salida = fopen(nombreArchivo, "w");
  fprintf(salida, "Tiempo: %lf\n\n", tiempoSegundos);
  glist_imprimir_archivo(salida, copiaLista, functionVisit);
  fclose(salida);
  glist_destroy_copy(copiaLista);
}

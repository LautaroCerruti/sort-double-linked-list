#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

GList glist_crear() {
    return NULL;
}

void glist_destruir(GList lista, Destruir function) {
  GNodo* nodoAux;
  GNodo* anterior = lista->ant;
  while (lista != anterior) {
    nodoAux = lista->sig;
    function(lista->dato);
    free(lista);
    lista = nodoAux;
  }
  function(lista->dato);
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
  lista1->ant = lista2->ant;
  GList temp = lista1->ant;
  lista1->ant = lista2->ant;
  lista2->ant = temp;
  return lista1;
}

GList glist_insertar_inicio(GList lista, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;
  nodo->sig = nodo;
  nodo->ant = nodo;

  return glist_concat(nodo, lista);
}

GList glist_insertar_final(GList lista, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;
  nodo->ant = nodo;
  nodo->sig = nodo;

  return glist_concat(lista, nodo);
}

GList glist_list_deep_copy(GList lista) {
  GList newList = glist_crear();
  GNodo* node = lista->ant;
  for (;node->ant != lista->ant; node = node->ant)
    newList = glist_insertar_inicio(newList, node->dato);
  newList = glist_insertar_inicio(newList, node->dato);
}

void glist_recorrer(GList lista, FuncionVisitante function) {
  if (lista) {
    function(lista->dato);
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; nodoAux = nodoAux->sig) {
        function(nodoAux->dato);
    }
  }
}


int glist_longitud(GList lista) {
  int longitud = 0;
  if (lista) {
    longitud = 1;
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; nodoAux = nodoAux->sig,
      longitud++);
  }
  return longitud;
}

void glist_insertar(GList* lista, int pos, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;

  if (!(*lista) && pos == 0) {
    nodo->ant = nodo;
    nodo->sig = nodo;
    *lista = nodo;
  } else {
    if (*lista) {
      GNodo* nodoAux = (*lista)->sig;
      for (int i = 1;
          nodoAux != *lista && i < pos;
          ++i, nodoAux = nodoAux->sig);
      nodoAux->sig->ant = nodo;
      nodo->sig = nodoAux->sig;
      nodoAux->sig = nodo;
      nodo->ant = nodoAux;
    }
  }
}

void glist_eliminar(GList* lista, int pos, Destruir function) {
  GNodo* nodo = glist_pop(lista, pos);
  if (nodo) {
    function(nodo->dato);
    free(nodo);
  }
}

void glist_swap(GNodo** nodo1, GNodo** nodo2) {
  void* dato = (*nodo2)->dato;
  (*nodo2)->dato = (*nodo1)->dato;
  (*nodo1)->dato = dato;
  GNodo* nodoAux = *nodo1;
  *nodo1 = *nodo2;
  *nodo2 = nodoAux;
}

GList glist_selection_sort(GList lista, Compara function) {
  if (lista) {
    GNodo* nodoAux = lista;
    for (; nodoAux != lista->ant; nodoAux = nodoAux->sig) {
      GNodo* nodoASwapear = nodoAux;
      GNodo* nodo = nodoAux->sig;
      for (; nodo != lista; nodo = nodo->sig) {
        if (function(nodo->dato, nodoASwapear->dato) == -1)
          nodoASwapear = nodo;
      }
      if (nodoAux != nodoASwapear) {
        glist_swap(&nodoAux, &nodoASwapear);
        nodoAux = nodoASwapear;
      }
    }
  }
  return lista;
}

GList glist_insertion_sort(GList lista, Compara function) {
  if (lista) {
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; ) {
      GNodo* nodo = nodoAux->ant;
      GNodo* nodoHastaSwapear = glist_crear();
      for (; function(nodo->dato, nodoAux->dato) == 1 && nodo != lista;
          nodo = nodo->ant);
      if (function(nodo->dato, nodoAux->dato) != 1) {
        nodoHastaSwapear = nodo->sig;
      } else {
        nodoHastaSwapear = nodo;
      }
      GNodo* nuevaUltimaPos = nodoAux->sig;
      for (; nodoAux != nodoHastaSwapear; ) {
        glist_swap(&nodoAux, &nodoAux->ant);
      }
      nodoAux = nuevaUltimaPos;
    }
  }
  return lista;
}

GList glist_merge(GList lista1, GList lista2, Compara function) {
  if (!lista1)
    return lista2;
  if (!lista2)
    return lista1;
  if (function(lista1->dato, lista2->dato) == -1) {
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

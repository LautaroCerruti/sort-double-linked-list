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

GList glist_insertar_inicio(GList lista, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;

  if (lista == NULL) {
    nodo->ant = nodo;
    nodo->sig = nodo;
  } else {
    nodo->sig = lista;
    lista->ant->sig = nodo;
    nodo->ant = lista->ant;
    lista->ant = nodo;
  }

  return nodo;
}

GList glist_insertar_final(GList lista, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;

  if (lista == NULL) {
    nodo->ant = nodo;
    nodo->sig = nodo;
    lista = nodo;
  } else {
    nodo->sig = lista;
    lista->ant->sig = nodo;
    nodo->ant = lista->ant;
    lista->ant = nodo;
  }
  return lista;
}

void glist_recorrer(GList lista, FuncionVisitante function) {
  if (lista != NULL) {
    function(lista->dato);
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; nodoAux = nodoAux->sig) {
        function(nodoAux->dato);
    }
  }
}


int glist_longitud(GList lista) {
  int longitud = 0;
  if (lista != NULL) {
    longitud = 1;
    GNodo* nodoAux = lista->sig;
    for (; nodoAux != lista; nodoAux = nodoAux->sig, longitud++);
  }
  return longitud;
}

void glist_insertar(GList* lista, int pos, void* dato) {
  GNodo* nodo = malloc(sizeof(GNodo));
  nodo->dato = dato;

  if (*lista == NULL && pos == 0) {
    nodo->ant = nodo;
    nodo->sig = nodo;
    *lista = nodo;
  } else {
    if (*lista != NULL) {
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
  GNodo* nodoAux = (*lista)->sig;
  if (pos == 0 && *lista != NULL) {
    (*lista)->ant->sig = (*lista)->sig;
    (*lista)->sig->ant = (*lista)->ant;
    function((*lista)->dato);
    free((*lista));
    (*lista) = nodoAux;
  } else {
    if (nodoAux != NULL) {
    for (int i = 0; nodoAux != (*lista); nodoAux = nodoAux->sig) {
      if (i == pos) {
        GNodo* nodo = nodoAux->sig;
        nodoAux->ant->sig = nodoAux->sig;
        nodoAux->sig->ant = nodoAux->ant;
        function(nodoAux->dato);
        free(nodoAux);
        nodoAux = nodo;
      }
    }
    }
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
  if (lista != NULL) {
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
  if (lista != NULL) {
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

GList glist_merge_sort(GList lista, Compara function) {
  if (!lista || lista->sig == lista)
    return lista;
  GList lista2 = glist_split(lista);

  lista = glist_merge_sort(lista, function);
  lista2 = glist_merge_sort(lista2, function);

  return glist_merge(lista, lista2, function);
}

GList glist_merge(GList lista1, GList lista2, Compara function) {
  GList listaFinal = glist_crear();
  if (!lista1)
    return lista2;
  if (!lista2)
    return lista1;
  if (function(lista1->dato, lista2->dato) == -1) {
    if (lista1 == lista1->sig) {
      lista1->sig = lista2;
      lista1->ant = lista2->ant;
      lista2->ant->sig = lista1;
      lista2->ant = lista1;
    } else {
      GList listaAux = lista1->sig;
      lista1->ant->sig = listaAux;
      listaAux->ant = lista1->ant;
      lista1->sig = glist_merge(listaAux, lista2, function);
      lista1->ant = lista1->sig->ant;
      lista1->sig->ant->sig = lista1;
      lista1->sig->ant = lista1;
    }
    return lista1;
  } else {
    if (lista2 == lista2->sig) {
      lista2->sig = lista1;
      lista2->ant = lista1->ant;
      lista1->ant->sig = lista2;
      lista1->ant = lista2;
    } else {
      GList listaAux = lista2->sig;
      lista2->ant->sig = listaAux;
      listaAux->ant = lista2->ant;
      lista2->sig = glist_merge(lista1, listaAux, function);
      lista2->ant = lista2->sig->ant;
      lista2->sig->ant->sig = lista2;
      lista2->sig->ant = lista2;
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

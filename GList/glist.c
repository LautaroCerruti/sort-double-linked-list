#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

GList glist_crear() {
    return NULL;
}

void glist_destruir(GList lista, Destruir function) {
  GList listaAux;
  GList anterior = lista->ant;
  while (lista != anterior) {
    listaAux = lista->sig;
    function(lista->dato);
    free(lista);
    lista = listaAux;
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
    GList listaAux = lista->sig;
    for ( ; listaAux != lista ; listaAux = listaAux->sig) {
        function(listaAux->dato);
    }
  }
}


int glist_longitud(GList lista) {
  int longitud = 0;
  if (lista != NULL) {
    longitud = 1;
    GList listaAux = lista->sig;
    for ( ; listaAux != lista ; listaAux = listaAux->sig, longitud++);
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
      GList listaAux = (*lista)->sig;
      for (int i = 1 ; listaAux != *lista && i < pos ; ++i, listaAux = listaAux->sig);
      listaAux->sig->ant = nodo;
      nodo->sig = listaAux->sig;
      listaAux->sig = nodo;
      nodo->ant = listaAux;
    }
  }
}

void glist_eliminar(GList* lista, int pos, Destruir function) {
  GList listaAux = (*lista)->sig;
  if (pos == 0 && *lista != NULL) {
    (*lista)->ant->sig = (*lista)->sig;
    (*lista)->sig->ant = (*lista)->ant;
    function((*lista)->dato);
    free((*lista));
    (*lista) = listaAux;
  } else {
    if (listaAux != NULL) {
    for (int i = 0 ; listaAux != (*lista) ; listaAux = listaAux->sig) {
      if (i == pos) {
        GNodo* nodo = listaAux->sig;
        listaAux->ant->sig = listaAux->sig;
        listaAux->sig->ant = listaAux->ant;
        function(listaAux->dato);
        free(listaAux);
        listaAux = nodo;
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

GList selection_sort(GList lista, Compara function) {
  int longitud = glist_longitud(lista);
  if (lista != NULL) {
    GList listaAux = lista;
    for (int i = 1 ; i < longitud ; ++i, listaAux = listaAux->sig) {
      GNodo* nodoASwapear = listaAux;
      GNodo* nodo = listaAux->sig;
      for (int j = i ; j < longitud ; ++j, nodo = nodo->sig) {
        if (function(nodo->dato, nodoASwapear->dato) == 1)
          nodoASwapear = nodo;
      }
      if (listaAux != nodoASwapear) {
        glist_swap(&listaAux, &nodoASwapear);
        listaAux = nodoASwapear;
      }
    }
  }
  return lista;
}

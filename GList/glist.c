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

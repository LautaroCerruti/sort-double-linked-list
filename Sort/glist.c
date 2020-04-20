#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

GList gList_crear() {
    return NULL;
}

void gList_destruir(GList lista, Destruir function) {
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

GList gList_insertar_inicio(GList lista, void* dato) {
    GNodo* nodo = malloc(sizeof(GNodo));
    nodo->dato = dato;

    if (lista == NULL) {
        nodo->ant = NULL;
        nodo->sig = NULL;
    } else {
        nodo->sig = lista;
        lista->ant->sig = nodo;
        nodo->ant = lista->ant;
        lista->ant = nodo;
    }

    return nodo;
}

GList gList_insertar_final(GList lista, void* dato) {
    GNodo* nodo = malloc(sizeof(GNodo));
    nodo->dato = dato;

    if (lista == NULL) {
        nodo->ant = NULL;
        nodo->sig = NULL;
        lista = nodo;
    } else {
        nodo->sig = lista;
        lista->ant->sig = nodo;
        nodo->ant = lista->ant;
        lista->ant = nodo;
    }

    return lista;
}

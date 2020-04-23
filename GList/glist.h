#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _GNodo{
  void* dato;
  struct _GNodo *ant;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Compara) (void* dato1 ,void* dato2);

typedef void (*Destruir) (void* dato);

typedef void (*FuncionVisitante) (FILE* salida, void* dato);

typedef GList (*SortAlgorithm) (GList lista, Compara function);

GList glist_crear();

void glist_destruir(GList lista, Destruir function);

GNodo* glist_pop(GList* lista, int pos);

GList glist_concat(GList lista1, GList lista2);

GList glist_insertar_inicio(GList lista, void* dato);

GList glist_insertar_final(GList lista, void* dato);

GList glist_deep_copy(GList lista);

void glist_imprimir_archivo(FILE* salida, GList lista, FuncionVisitante function);

int glist_longitud(GList lista);

void glist_insertar(GList* lista, int pos, void* dato);

void glist_eliminar(GList* lista, int pos, Destruir function);

void glist_swap(GNodo* nodo1, GNodo* nodo2);

GList glist_selection_sort(GList lista, Compara function);

GList glist_insertion_sort(GList lista, Compara function);

GList glist_merge(GList lista1, GList lista2, Compara function);

GList glist_split(GList lista);

GList glist_merge_sort(GList lista, Compara function);

void glist_test_sort_algorithm(char* nombreArchivo, GList lista,
  SortAlgorithm sort, Compara functionCompare,FuncionVisitante functionVisit);

#endif /* __GLIST_H__ */

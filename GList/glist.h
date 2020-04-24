#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _GNode{
  void* data;
  struct _GNode *ant;
  struct _GNode *sig;
} GNode;

typedef GNode *GList;

typedef int (*Compare) (void* data1 ,void* data2);

typedef void (*Destroy) (void* data);

typedef void (*VisitorFunction) (FILE* output, void* data);

typedef GList (*SortAlgorithm) (GList list, Compare function);

GList glist_create();

void glist_destroy(GList list, Destroy function);

GNode* glist_pop(GList* list, int pos);

GList glist_concat(GList list1, GList list2);

GList glist_insert_last_position(GList list, void* data);

GList glist_copy(GList list);

void glist_destroy_copy(GList list);

void glist_imprimir_archivo(FILE* output, GList list, VisitorFunction function);

void glist_swap(GNode* nodo1, GNode* nodo2);

GList glist_selection_sort(GList list, Compare function);

GList glist_insertion_sort(GList list, Compare function);

GList glist_merge(GList list1, GList list2, Compare function);

GList glist_split(GList list);

GList glist_merge_sort(GList list, Compare function);

void glist_test_sort_algorithm(char* nombreArchivo, GList list,
  SortAlgorithm sort, Compare functionCompare,VisitorFunction functionVisit);

#endif /* __GLIST_H__ */

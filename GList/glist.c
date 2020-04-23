#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

GList glist_create() {
    return NULL;
}

void glist_destroy(GList list, Destroy function) {
  GNode* auxNode;
  GNode* anterior = list->ant;
  for (; list != anterior; list = auxNode) {
    auxNode = list->sig;
    function(list->data);
    free(list);
  }
  function(list->data);
  free(list);
}

void glist_destroy_copy(GList list) {
  GNode* auxNode;
  GNode* anterior = list->ant;
  for (; list != anterior; list = auxNode) {
    auxNode = list->sig;
    free(list);
  }
  free(list);
}

GNode* glist_pop(GList* list, int pos) {
  GNode* node = glist_crear();
  if (list) {
    if ((*list)->sig == *list) {
      node = *list;
      list = NULL;
    } else {
      node = *list;
      for (; node->sig != (*list) && pos != 0; node = node->sig, --pos);
      if (pos == 0) {
        *list = node->sig;
        node->ant->sig = node->sig;
        node->sig->ant = node->ant;
        node->sig = node;
        node->ant = node;
      }
    }
  }
  return node;
}

GList glist_concat(GList list1, GList list2) {
  if (!list1)
    return list2;
  if (!list2)
    return list1;
  list1->ant->sig = list2;
  list2->ant->sig = list1;
  GList temp = list1->ant;
  list1->ant = list2->ant;
  list2->ant = temp;
  return list1;
}

GList glist_insert_last_position(GList list, void* data) {
  GNode* node = malloc(sizeof(GNode));
  node->data = data;
  node->ant = node;
  node->sig = node;

  return glist_concat(list, node);
}

GList glist_copy(GList list) {
  GList newList = glist_crear();
  GNode* node = list;
  if (list) {
    for (;node->sig != list; node = node->sig)
      newList = glist_insertar_final(newList, node->data);
    newList = glist_insertar_final(newList, node->data);
  }
  return newList;
}

void glist_imprimir_archivo(FILE* output, GList list, VisitorFunction function) {
  if (list) {
    function(output, list->data);
    GNode* auxNode = list->sig;
    for (; auxNode != list; auxNode = auxNode->sig)
      function(output, auxNode->data);
  }
}

void glist_swap(GNode* node1, GNode* node2) {
  void* data = node2->data;
  node2->data = node1->data;
  node1->data = data;
}

GList glist_selection_sort(GList list, Compare function) {
  if (list) {
    GNode* auxNode = list;
    for (; auxNode != list->ant; auxNode = auxNode->sig) {
      GNode* nodeASwapear = auxNode;
      GNode* node = auxNode->sig;
      for (; node != list; node = node->sig) 
        if (function(node->data, nodeASwapear->data) < 0)
          nodeASwapear = node;
      if (auxNode != nodeASwapear) {
        glist_swap(auxNode, nodeASwapear);
      }
    }
  }
  return list;
}

GList glist_insertion_sort(GList list, Compare function) {
  if (list) {
    GNode* auxNode = list->sig;
    do {
      GNode* node = auxNode->ant;
      GNode* nodeHastaSwapear = glist_crear();
      for (; function(node->data, auxNode->data) > 0 && node != list->ant;
          node = node->ant);
      if (function(node->data, auxNode->data) != 1) {
        nodeHastaSwapear = node->sig;
      } else {
        nodeHastaSwapear = node;
      }
      GNode* nuevaUltimaPos = auxNode->sig;
      for (; auxNode != nodeHastaSwapear; auxNode = auxNode->ant)
        glist_swap(auxNode, auxNode->ant);
      auxNode = nuevaUltimaPos;
    } while (auxNode != list);
  }
  return list;
}

GList glist_merge(GList list1, GList list2, Compare function) {
  if (!list1)
    return list2;
  if (!list2)
    return list1;
  if (function(list1->data, list2->data) < 0) {
    if (list1 == list1->sig) {
      list1 = glist_concat(list1, list2);
    } else {
      GNode* auxNode = glist_pop(&list1, 0);
      list1 = glist_merge(list1, list2, function);
      list1 = glist_concat(auxNode, list1);
    }
    return list1;
  } else {
    if (list2 == list2->sig) {
      list2 = glist_concat(list2, list1);
    } else {
      GNode* auxNode = glist_pop(&list2, 0);
      list2 = glist_merge(list1, list2, function);
      list2 = glist_concat(auxNode, list2);
    }
    return list2;
  }
}

GList glist_split(GList list) {
  GNode* node1 = list;
  GNode* node2 = list;
  for (; node1->sig != list && node1->sig->sig != list;
      node1 = node1->sig->sig, node2 = node2->sig);
  GList listNueva = node2->sig;
  list->ant->sig = listNueva;
  listNueva->ant = list->ant;
  list->ant = node2;
  node2->sig = list;
  return listNueva;
}

GList glist_merge_sort(GList list, Compare function) {
  if (!list || list->sig == list)
    return list;
  GList list2 = glist_split(list);

  list = glist_merge_sort(list, function);
  list2 = glist_merge_sort(list2, function);

  return glist_merge(list, list2, function);
}

void glist_test_sort_algorithm(char* nombreArchivo, GList list, SortAlgorithm sort,
  Compare functionCompare, VisitorFunction functionVisit) {
  GList copiaLista = glist_copy(list);
  clock_t t = clock();
  copiaLista = sort(copiaLista, functionCompare);
  t = clock() - t;
  double tiempoSegundos = ((double)t)/CLOCKS_PER_SEC;
  FILE* output = fopen(nombreArchivo, "w");
  fprintf(output, "Tiempo: %lf\n\n", tiempoSegundos);
  glist_imprimir_archivo(output, copiaLista, functionVisit);
  fclose(output);
  glist_destroy_copy(copiaLista);
}

#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode{
  void* data;
  struct _GNode *prev;
  struct _GNode *next;
};

GList glist_create() {
  return NULL;
}

void glist_destroy(GList list, Destroy function) {
  GNode* auxNode;
  GNode* previous = list->prev;
  for (; list != previous; list = auxNode) {
    auxNode = list->next;
    function(list->data);
    free(list);
  }
  function(list->data);
  free(list);
}

GNode* glist_pop(GList* list, int pos) {
  GNode* node = glist_create();
  if (list) {
    if ((*list)->next == *list) {
      node = *list;
      list = NULL;
    } else {
      node = *list;
      for (; node->next != (*list) && pos != 0; node = node->next, --pos);
      if (pos == 0) {
        *list = node->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = node;
        node->prev = node;
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
  list1->prev->next = list2;
  list2->prev->next = list1;
  GList temp = list1->prev;
  list1->prev = list2->prev;
  list2->prev = temp;
  return list1;
}

GList glist_insert_last_position(GList list, void* data) {
  GNode* node = malloc(sizeof(GNode));
  node->data = data;
  node->prev = node;
  node->next = node;

  return glist_concat(list, node);
}

GList glist_copy(GList list) {
  GList newList = glist_create();
  GNode* node = list;
  if (list) {
    for (;node->next != list; node = node->next)
      newList = glist_insert_last_position(newList, node->data);
    newList = glist_insert_last_position(newList, node->data);
  }
  return newList;
}

void glist_destroy_copy(GList list) {
  GNode* auxNode;
  GNode* previous = list->prev;
  for (; list != previous; list = auxNode) {
    auxNode = list->next;
    free(list);
  }
  free(list);
}

void glist_print_file(FILE* output, GList list, VisitorFunction function) {
  if (list) {
    function(output, list->data);
    GNode* auxNode = list->next;
    for (; auxNode != list; auxNode = auxNode->next)
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
    for (; auxNode != list->prev; auxNode = auxNode->next) {
      GNode* nodeToSwap = auxNode;
      GNode* node = auxNode->next;
      for (; node != list; node = node->next) 
        if (function(node->data, nodeToSwap->data) < 0)
          nodeToSwap = node;
      if (auxNode != nodeToSwap) {
        glist_swap(auxNode, nodeToSwap);
      }
    }
  }
  return list;
}

GList glist_insertion_sort(GList list, Compare function) {
  if (list) {
    GNode* auxNode = list->next;
    do {
      GNode* node = auxNode->prev;
      for (; function(node->data, auxNode->data) > 0 && node != list->prev;
          node = node->prev);
      GNode* newLastPosition = auxNode->next;
      if (node != auxNode->prev) {
        node = node->next;
        if (node == list) {
          list = auxNode;
        }
        //Sacando node de su posicion
        auxNode->prev->next = auxNode->next;
        auxNode->next->prev = auxNode->prev;
        //Moviendo node a la izquierda de nodeHastaSwapear
        auxNode->next = node;
        auxNode->prev = node->prev;
        node->prev->next = auxNode;
        node->prev = auxNode;
      }
      auxNode = newLastPosition;
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
    if (list1 == list1->next) {
      list1 = glist_concat(list1, list2);
    } else {
      GNode* auxNode = glist_pop(&list1, 0);
      list1 = glist_merge(list1, list2, function);
      list1 = glist_concat(auxNode, list1);
    }
    return list1;
  } else {
    if (list2 == list2->next) {
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
  for (; node1->next != list && node1->next->next != list;
      node1 = node1->next->next, node2 = node2->next);
  GList newList = node2->next;
  list->prev->next = newList;
  newList->prev = list->prev;
  list->prev = node2;
  node2->next = list;
  return newList;
}

GList glist_merge_sort(GList list, Compare function) {
  if (!list || list->next == list)
    return list;
  GList list2 = glist_split(list);

  list = glist_merge_sort(list, function);
  list2 = glist_merge_sort(list2, function);

  return glist_merge(list, list2, function);
}

void glist_test_sort_algorithm(char* nombreArchivo, GList list, SortAlgorithm sort,
  Compare functionCompare, VisitorFunction functionVisit) {
  GList copyList = glist_copy(list);
  clock_t t = clock();
  copyList = sort(copyList, functionCompare);
  t = clock() - t;
  double seconds = ((double)t)/CLOCKS_PER_SEC;
  FILE* output = fopen(nombreArchivo, "w");
  fprintf(output, "Tiempo: %lf\n\n", seconds);
  glist_print_file(output, copyList, functionVisit);
  fclose(output);
  glist_destroy_copy(copyList);
}

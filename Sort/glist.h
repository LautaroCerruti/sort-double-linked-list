#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef struct _GNodo{
    void* dato;
    struct _GNodo *ant;
    struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Compara) (void* dato1 ,void* dato2);

typedef void (*Destruir) (void* dato);

GList gList_crear();

void gList_destruir(GList lista, Destruir function);

GList gList_insertar_inicio(GList lista, void* dato);

GList gList_insertar_final(GList lista, void* dato);

#endif /* __GLIST_H__ */

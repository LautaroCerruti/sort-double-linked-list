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

typedef void (*FuncionVisitante) (void* dato);

GList glist_crear();

void glist_destruir(GList lista, Destruir function);

GList glist_insertar_inicio(GList lista, void* dato);

GList glist_insertar_final(GList lista, void* dato);

void glist_recorrer(GList lista, FuncionVisitante function);

#endif /* __GLIST_H__ */

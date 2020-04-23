#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#define MAX_NOMBRE 100
#define MAX_LUGAR_NACIMIENTO 50

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; // pais o capital
} Persona;

void persona_destruir(void* dato);

Persona* persona_crear(char* nombre, int edad, char* lugarDeNacimiento);

int persona_compara_edad(void* dato1, void* dato2);

int persona_compara_nombre(void* dato1, void* dato2);

int persona_compara_lugar_nacimiento(void* dato1, void* dato2);

void persona_imprimir_archivo(FILE* archivo, void* dato);

#endif /* __PERSONA_H__ */

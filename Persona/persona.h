#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#define MAX_NOMBRE 100
#define MAX_LUGAR_NACIMIENTO 50

typedef struct Persona_ Persona;

/*
  Dado un nombre, una edad y un lugarDeNacimiento, crea una persona
  y devuelve un puntero que apunta a esta
  persona_crear: char* int char* -> Persona*
*/
Persona* persona_crear(char* nombre, int edad, char* lugarDeNacimiento);

/*
  Dada una persona, la destruye liberando la memoria
*/
void persona_destruir(void* dato);

/*
  Dadas dos personas las compara por edad y devuelve 0 si son iguales,
  menor a 0 si la edad de la segunda es mayor que la de la primera y
  mayor a 0 si la de la primera es mayor a la de la segunda
  persona_compara_edad: void* void* -> int
*/
int persona_compara_edad(void* dato1, void* dato2);

/*
  Dadas dos personas las compara por nombre y devuelve 0 si son iguales,
  menor a 0 si el nombre de la segunda es posterior alfabeticamente que el de
  la primera y mayor a 0 si el de la primera es posterior alfabeticamente que
  el de la segunda.
  persona_compara_nombre: void* void* -> int
*/
int persona_compara_nombre(void* dato1, void* dato2);

/*
  Dadas dos personas las compara por lugarDeNacimiento y devuelve 0 si son 
  iguales, menor a 0 si el lugarDeNacimiento de la segunda es posterior 
  alfabeticamente que el de la primera y mayor a 0 si el de la primera es
  posterior alfabeticamente que el de la segunda.
  persona_compara_nombre: void* void* -> int
*/
int persona_compara_lugar_nacimiento(void* dato1, void* dato2);

/*
  Dado un archivo y una persona, imprime en el archivo la persona,
  con el formato "nombre, edad, lugarDeNacimiento"
*/
void persona_imprimir_archivo(FILE* archivo, void* dato);

#endif /* __PERSONA_H__ */

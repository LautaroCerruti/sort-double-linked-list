#include <stdio.h>
#include <stdlib.h>
#include "./GList/glist.h"
#include "./Persona/persona.h"

int main(int argc, char *argv[]) {
  GList lista = glist_crear();
  Persona* persona;
  int edad;
  char bufferNombre[MAX_NOMBRE], bufferLugarNacimiento[MAX_LUGAR_NACIMIENTO];
  FILE* personasFile = fopen(argv[1], "r");
  while (fscanf(personasFile, "%[^,], %d, %[^\n]", bufferNombre, &edad, bufferLugarNacimiento) != EOF) {
    fgetc(personasFile);
    persona = persona_crear(bufferNombre, edad, bufferLugarNacimiento);
    lista = glist_insertar_final(lista, persona);
  }
  fclose(personasFile);

  glist_test_sort_algorithm("selection_edad", lista, glist_selection_sort, persona_compara_edad, persona_destruir, persona_imprimir_archivo);
  glist_test_sort_algorithm("selection_nombre", lista, glist_selection_sort, persona_compara_nombre, persona_destruir, persona_imprimir_archivo);
  //glist_test_sort_algorithm("selection_lugar_nacimiento", lista, glist_selection_sort, persona_compara_lugar_nacimiento, persona_destruir, persona_imprimir_archivo);
  glist_test_sort_algorithm("insertion_edad", lista, glist_insertion_sort, persona_compara_edad, persona_destruir, persona_imprimir_archivo);
  glist_test_sort_algorithm("insertion_nombre", lista, glist_insertion_sort, persona_compara_nombre, persona_destruir, persona_imprimir_archivo);
  //glist_test_sort_algorithm("insertion_lugar_nacimiento", lista, glist_insertion_sort, persona_compara_lugar_nacimiento, persona_destruir, persona_imprimir_archivo);
  glist_test_sort_algorithm("merge_edad", lista, glist_merge_sort, persona_compara_edad, persona_destruir, persona_imprimir_archivo);
  glist_test_sort_algorithm("merge_nombre", lista, glist_merge_sort, persona_compara_nombre, persona_destruir, persona_imprimir_archivo);
  //glist_test_sort_algorithm("merge_lugar_nacimiento", lista, glist_merge_sort, persona_compara_lugar_nacimiento, persona_destruir, persona_imprimir_archivo);
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LINEA 200

/*
  Toma dos ints a y b, y devuelve un numero mayor a 0 si a es mayor a b
  0 si son iguales, y un numero menor a 0 si b es mayor a a
*/
int compara_int(const void *i, const void *j){
  int *a = (int *) i, *b = (int *)j;
  return *a - *b;
}

/*
  swap_int Toma un array de enteros, una posicion y otra posicion e 
  intercambia de lugar el numero en la primera posicion con el de la segunda
*/
void swap_int(int* numeros,int posicion1,int posicion2){
  numeros[posicion1] += numeros[posicion2];
  numeros[posicion2] = numeros[posicion1] - numeros[posicion2];
  numeros[posicion1] -= numeros[posicion2];
}

/*
  Genera una lista de n numeros randoms no repetidos, siendo n un numero que se
  ingreso como parametro de la funcion 
  Toma el numero maximo que puede generar, la cantidad de numeros randoms 
  a generar, y un puntero a un array de donde se almacenara la lista
*/
void genera_n_randoms(int lineasArchivo, int cantidadPersonas, int* resultado){
  int *randoms = (int*) malloc(sizeof(int)*lineasArchivo), i, aleatorio;

  for( i = 0;i<lineasArchivo;i++){
    randoms[i] = i;
  }
  for(i = 0 ; i < cantidadPersonas; i++){
    aleatorio = rand() % (lineasArchivo  - i) ;
    resultado[i] = randoms[aleatorio];
    swap_int(randoms, aleatorio, (lineasArchivo-i-1));
  }
  free(randoms);                   
}

/*
  Dado un archivo cuenta la cantidad de lineas que tiene el archivo dado
  contador_de_lineas: File -> Int
*/
int contador_de_lineas(FILE* entrada){
  char linea[1024];
  int lineasArchivo = 0;
  while(fgets(linea, 1024, (FILE*) entrada)) {
    lineasArchivo++;
  }
  rewind(entrada);
  return lineasArchivo;
}

void creacion_de_personas (int CantidadPersonas, FILE* nombres,
    char** locaciones, int lineasArchivoNombres, int lineasArchivoLocaciones,
    FILE *salida) {
  int *NumerosDePersonas = (int*) malloc(sizeof(int)*CantidadPersonas),
    iterador, NombreBuscado = 0, iteradorArchivo = -1, locacionesPos;
  char nombre[MAX_LINEA];

  genera_n_randoms(lineasArchivoNombres, CantidadPersonas, NumerosDePersonas);
  qsort(NumerosDePersonas, CantidadPersonas, sizeof(int), compara_int);

  for(iterador = 0; iterador < CantidadPersonas; ++iterador){
    NombreBuscado = NumerosDePersonas[iterador];
    for(; iteradorArchivo != NombreBuscado; iteradorArchivo++){
      fscanf(nombres, "%[^\n]", nombre);
      fgetc(nombres);
    }
    locacionesPos = rand() % lineasArchivoLocaciones;
    fprintf(salida, "%s, %d, %s\n", nombre, (rand()%100+1), locaciones[locacionesPos]);
  }
  free(NumerosDePersonas);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int cantidadAGenerar, cantidadNombresDisponible, 
    cantidadLocacionesDisponibles, iterador;
  char **locaciones, buffer[MAX_LINEA];
  FILE *nombres, *locacionesarchivo, *salida;
  cantidadAGenerar = atoi(argv[1]);
  nombres = fopen(argv[2], "r");
  cantidadNombresDisponible = contador_de_lineas(nombres);
  if (cantidadAGenerar > cantidadNombresDisponible) {
    printf("Fallo la generacion debido a falta de nombres disponibles\n");
  } else {
    locacionesarchivo = fopen(argv[3],"r");
    cantidadLocacionesDisponibles = contador_de_lineas(locacionesarchivo);
    locaciones = (char** ) malloc(sizeof(char*)*cantidadLocacionesDisponibles);
    for(iterador = 0; iterador < cantidadLocacionesDisponibles; ++iterador){
      fscanf(locacionesarchivo,"%[^\n]", buffer);
      fgetc(locacionesarchivo);
      locaciones[iterador] = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
      strcpy(locaciones[iterador], buffer);
    }
    fclose(locacionesarchivo);
    salida = fopen(argv[4], "w");
    creacion_de_personas(cantidadAGenerar, nombres, locaciones, 
      cantidadNombresDisponible, cantidadLocacionesDisponibles, salida);
    fclose(nombres);
    fclose(salida);
    for(iterador = 0; iterador < cantidadLocacionesDisponibles; ++iterador){
      free(locaciones[iterador]);
    }
    free(locaciones);
  }
  return 0;
}

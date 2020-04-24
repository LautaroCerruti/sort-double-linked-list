#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LINE 200

/*
  Toma dos ints a y b, y devuelve un numero mayor a 0 si a es mayor a b
  0 si son iguales, y un numero menor a 0 si b es mayor a a
  compare_int: void* void* -> int
*/
int compare_int(const void *i, const void *j){
  int *a = (int *) i, *b = (int *)j;
  return *a - *b;
}

/*
  swap_int Toma un array de enteros, una posicion y otra posicion e 
  intercambia de lugar el numero en la primera posicion con el de la segunda
*/
void swap_int(int* numbers,int position1,int position2){
  numbers[position1] += numbers[position2];
  numbers[position2] = numbers[position1] - numbers[position2];
  numbers[position1] -= numbers[position2];
}

/*
  Genera una lista de n numeros randoms no repetidos, siendo n un numero que se
  ingreso como parametro de la funcion 
  Toma el numero maximo que puede generar, la cantidad de numeros randoms 
  a generar, y un puntero a un array de donde se almacenara la lista
*/
void generate_n_randoms(int linesFile, int amountPeople, int* result){
  int *randoms = (int*) malloc(sizeof(int)*linesFile), i, random;

  for( i = 0;i<linesFile;i++){
    randoms[i] = i;
  }
  for(i = 0 ; i < amountPeople; i++){
    random = rand() % (linesFile  - i) ;
    result[i] = randoms[random];
    swap_int(randoms, random, (linesFile-i-1));
  }
  free(randoms);                   
}

/*
  Dado un archivo cuenta la cantidad de lineas que tiene el archivo dado
  lines_counter: File -> Int
*/
int lines_counter(FILE* input){
  char line[1024];
  int linesFile = 0;
  while(fgets(line, 1024, (FILE*) input)) {
    linesFile++;
  }
  rewind(input);
  return linesFile;
}

/*
  Toma una cantidad de personas N, un archivo con los nombres, un array 
  bidimensional de locaciones, la cantidad de lineas del archivo de personas,
  la cantidad de locaciones y un archivo de salida. Imprime en el archivo de 
  salida una cantidad N de personas con el formato "nombre, edad, locacion"
*/
void personas_creator (int amountPeople, FILE* names,
    char** locations, int linesFileNames, int linesFileLocations,
    FILE *output) {
  int *numbersOfPeople = (int*) malloc(sizeof(int)*amountPeople),
    iterator, searchedName = 0, fileIterator = -1, locationsPos;
  char name[MAX_LINE];

  generate_n_randoms(linesFileNames, amountPeople, numbersOfPeople);
  qsort(numbersOfPeople, amountPeople, sizeof(int), compare_int);

  for(iterator = 0; iterator < amountPeople; ++iterator){
    searchedName = numbersOfPeople[iterator];
    for(; fileIterator != searchedName; fileIterator++){
      fscanf(names, "%[^\n]", name);
      fgetc(names);
    }
    locationsPos = rand() % linesFileLocations;
    fprintf(output, "%s, %d, %s\n", name, (rand()%100+1), locations[locationsPos]);
  }
  free(numbersOfPeople);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int generationAmount, availableNamesAmount, 
    availableLocationsAmount, iterator;
  char **locations, buffer[MAX_LINE];
  FILE *names, *locationsFile, *output;
  generationAmount = atoi(argv[1]);
  names = fopen(argv[2], "r");
  availableNamesAmount = lines_counter(names);
  if (generationAmount > availableNamesAmount) {
    printf("Fallo la generacion debido a falta de nombres disponibles\n");
  } else {
    locationsFile = fopen(argv[3],"r");
    availableLocationsAmount = lines_counter(locationsFile);
    locations = (char** ) malloc(sizeof(char*)*availableLocationsAmount);
    for(iterator = 0; iterator < availableLocationsAmount; ++iterator){
      fscanf(locationsFile,"%[^\n]", buffer);
      fgetc(locationsFile);
      locations[iterator] = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
      strcpy(locations[iterator], buffer);
    }
    fclose(locationsFile);
    output = fopen(argv[4], "w");
    personas_creator(generationAmount, names, locations, 
      availableNamesAmount, availableLocationsAmount, output);
    fclose(names);
    fclose(output);
    for(iterator = 0; iterator < availableLocationsAmount; ++iterator){
      free(locations[iterator]);
    }
    free(locations);
  }
  return 0;
}

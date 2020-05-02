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
  Genera una lista de n numeros randoms, siendo n un numero que se
  ingreso como parametro de la funcion 
  Toma el numero maximo que puede generar, la cantidad de numeros randoms 
  a generar, y un puntero a un array de donde se almacenara la lista
*/
int* generate_n_randoms(int maxNumber, int n){
  int  i = 0, random, *result = (int*) malloc(sizeof(int)*n);
  for(; i < n; i++){
    random = rand() % maxNumber;
    result[i] = random;
  }
  return result;
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
  int *numbersOfPeople, iterator, searchedNumber = 0, fileIterator = -1;
  char name[MAX_LINE];

  numbersOfPeople = generate_n_randoms(linesFileNames, amountPeople);
  qsort(numbersOfPeople, amountPeople, sizeof(int), compare_int);

  for(iterator = 0; iterator < amountPeople; ++iterator){
    searchedNumber = numbersOfPeople[iterator];
    for(; fileIterator != searchedNumber; fileIterator++){
      fscanf(names, "%[^\n]", name);
      fgetc(names);
    }
    fprintf(output, "%s, %d, %s\n", name, (rand()%100+1), 
      locations[rand() % linesFileLocations]);
  }
  free(numbersOfPeople);
}

char** read_locations(int availableLocationsAmount, FILE* locationsFile){
  int iterator;
  char buffer[MAX_LINE];
  char** locations = (char** ) malloc(sizeof(char*)*availableLocationsAmount);
  for(iterator = 0; iterator < availableLocationsAmount; ++iterator){
    fscanf(locationsFile,"%[^\n]", buffer);
    fgetc(locationsFile);
    locations[iterator] = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(locations[iterator], buffer);
  }
  return buffer;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int generationAmount, availableNamesAmount, 
    availableLocationsAmount, iterator;
  char **locations;
  FILE *names, *locationsFile, *output;

  generationAmount = atoi(argv[1]);
  names = fopen(argv[2], "r");
  availableNamesAmount = lines_counter(names);
  locationsFile = fopen(argv[3],"r");
  availableLocationsAmount = lines_counter(locationsFile);

  locations = read_locations(availableLocationsAmount, locationsFile);
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
  return 0;
}

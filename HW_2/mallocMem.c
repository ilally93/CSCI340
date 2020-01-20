#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  // Checks for correct number of parameters
  if(argc != 2){
    printf("Requires 1 Parameter");
    exit(1);
  }

  int size = atoi(argv[1]);

  // Allocate block of memory the size of parameter.
  char *blockMem = malloc(size);

  memset(blockMem, 0, size);
  printf("%p\n", &blockMem);

  char **point = &blockMem;
  //printf("%p\n", point);

  for(int i = 0; i < size; i++){
    printf("%x", point);
    point++;
  }

  // Free the memory
  free(blockMem);

}

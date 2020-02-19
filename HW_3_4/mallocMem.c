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
  printf("Is it running?");
  // Allocate block of memory the size of parameter.
  char *blockMem = malloc(size);

  memset(blockMem, 0, size);
  printf("The address of the memory block: %p\n", &blockMem);


  char *point = blockMem;

  for(int i = 0; i < size; i++){
    printf("Content %d: %x\n", (i+1), *point);
    point++;
  }

  // Free the memory
  free(blockMem);

}

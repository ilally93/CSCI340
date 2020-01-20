#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argc[]){

  // Checks for correct number of parameters
  if(argc != 2){
    printf("Requires 1 Parameter");
    exit(1);
  }

  char *memSize = malloc(argv[1]);
  free(memSize);

}

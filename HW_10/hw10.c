#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(argc != 2){
    printf("Usage: ./hw10 </path/to/file>\n");
    exit(1);
  }


  char *file = argv[1];
  int fileNum = open(file, O_RDONLY);
  char *numEnt = malloc(sizeof(int));

  if(fileNum < 0){
    printf("Invalid File Path");
    exit(1);
  }

  lseek(fileNum, 4, SEEK_SET);
  read(fileNum, numEnt, 4);
  int numberE = *numEnt;

  int entry = 8;

  char *off = malloc(sizeof(int));
  int offset[numberE];

  for(int i = 0; i < numberE; i++){
    lseek(fileNum, entry, SEEK_SET);
    read(fileNum, off, 4);
    entry = entry + 4;
    offset[i] = *off;
  }

  char *length = malloc(sizeof(int));

  for(int i = 0; i < numberE; i++){
    lseek(fileNum, offset[i], SEEK_SET);
    read(fileNum, length, 4);
    char *line = malloc((*length) - 4);
    read(fileNum, line, ((*length) - 4));
    printf("%s", line);
    free(line);
  }


  free(numEnt);
  free(off);
  free(length);

  if(close(fileNum) < 0){
    printf("File did not close properly.");
    exit(1);
  }
}

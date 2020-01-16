#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

  // checks that there are parameters that would have pointers
  if(argc < 2){
    printf("No Parameters\n");
    exit(1);
  }

  // iterates through parameters and prints parameter and their pointers
  for(int i = 1; i < argc; i++) {
    printf("Pointer of %s <%p>\n", argv[i], &argv[i]);
  }

  return 0;
}

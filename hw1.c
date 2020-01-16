#include <stdio.h>

int main(int argc, char* argv[]){

  for (int i = 1; i < argc; i++) {
    /* code */

    printf("Pointer of %s <%p>\n", argv[i], &argv[i]);
    
  }
}

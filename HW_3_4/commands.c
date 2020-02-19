#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/wait.h>

int main(int argc, char *argv[]){
    int i = 1;
    char command[250] = "";
    while(argv[i] != 0){
        strcat(command, argv[i]);
        strcat(command, " ");
        i++;
    }
    system(command);
}

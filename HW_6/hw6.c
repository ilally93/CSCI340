#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

volatile int counter = 0;

char stringCreate(int length, char *genString){
    if(counter < length){
        genString[counter] = '1';
        counter++;
    }
    return genString;
}


int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Needs Two Arguments: Number of Threads and Length of String");
        return 1;
    }

    int zero = 0;
    int length = atoi(argv[2]) + 1;
    char *genString;
    void *memset(void * genString, int zero, size_t length);
    //printf("Length: %d   String: %s\n", length, genString);

    //free(genString);
    char args = {length, genString};
    pthread_t thread[atoi(argv[1])];

    for(int i = 0; i < stoi(argv[1]); i++){
        pthread_create(thread + i, NULL, stringCreate, args);
    }

    printf("String: %s", genString);

    return 0;

}

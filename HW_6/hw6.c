#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

volatile int counter = 0;
volatile int i;
volatile char tNum;

// A method to change each 0 to correct character
void stringCreate(char *str){
        tNum = i + 64;
        (str[counter]) = tNum;
        counter++;
}


int main(int argc, char *argv[]){

    // Checks that arguments given are correct
    if(argc != 3){
        printf("Needs Two Arguments: Number of Threads and Length of String\n");
        return 1;
    }

    printf("\n  Each character in the string is the ascii value of the number of the thread being used plus 65.\n");
    printf("  This means that the first thread will produce the character 'A'\n");

    int length = atoi(argv[2]); //length of the string
    int numThr = atoi(argv[1]); //Number of threads
    char genString[length];
    memset(genString, '0', length);

    pthread_t thread[(numThr)];

    // While loop until the appropriate length of the string is reached
    while(counter < (length)){
        // For loop to create the correct number of threads
        for(i = 1; i <= (numThr); i++){
            // Checks before each thread that the length of the string has been met
            if(counter == length){
                printf("\n    End String: %s\n\n", genString);
                exit(0);
            }

            // Creates thread that runs stringCreate
            pthread_create(&thread[i], NULL, stringCreate, genString);
            assert(pthread_join(thread[i], NULL) == 0);

        }
    }
    printf("\n    End String: %s\n\n", genString);

    return 0;

}

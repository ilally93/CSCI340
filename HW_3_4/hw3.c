#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    char *dogs[] = {"./commands",0};
    pid_t pid = fork();
    if(pid < 0){
        printf("error");
        exit(-1);
    }

    if(pid == 0){
        if(execvp(dogs[0], argv) < 0){
            printf("errorexec");
        }
    }

    waitpid(pid, 0, 0);
    if(pid > 0){
        printf("\nBack to Parent\n");
    }

    return 0;
}

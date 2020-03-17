#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int sVar1 = 0;
int sVar2 = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void signal(int state){
    assert(pthread_mutex_lock(&mut) == 0);

    state = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mut);
}

void thr_wait(int state) {

    pthread_mutex_lock(&mut);

    while (state == 0)
        pthread_cond_wait(&cond, &mut);

    pthread_mutex_unlock(&mut);

}


int main(int argc, char *argv[]) {

    pthread_t p1;
    pthread_t p2;

    

    return 0;
}

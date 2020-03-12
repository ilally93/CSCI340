// simple processing pipeline
// Pipeline slide: 3 threads and 2 queues

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

// Definition of a Queue
typedef struct{


} QUEUE;

// Thread Data
    // T1 access to
typedef struct{
    int n_items;
    QUEUE* q_out;

} STAGE_1_DATA;


typedef struct{
    QUEUE* q_in;
    QUEUE* q_out;

} STAGE_2_DATA;


typedef struct{
    QUEUE* q_in;

} STAGE_3_DATA;

// Thread Functions
void * stage_1_fn(void * args){

    STAGE_1_DATA* data = (STAGE_1_DATA*)args

    return NULL;
}

void * stage_2_fn(void * args){

    STAGE_2_DATA* data = (STAGE_2_DATA*)args

    return NULL;
}

void * stage_3_fn(void * args){

    STAGE_3_DATA* data = (STAGE_3_DATA*)args

    return NULL;
}

int main(int argc, char** argv){

    if (argc != 3){
        printf("Usage: Pipeline n_items queue_length\n");
        exit(42);
    }

    int n_items = atoi(argv[1]);
    int q_len = atoi(argv[2]);

    // Create the Queues
    QUEUE q1;  // Put on Stack for Easy Cleanup
    QUEUE q2; // If Malloced:  Must Use Free(q1/ q2)

    // Setup the Data to be Passed to the Threads
    STAGE_1_DATA s1d = {n_items, &q1};
    STAGE_2_DATA s2d = {n_items, &q1, &q2};
    STAGE_3_DATA s3d = {n_items, &q2};

    // Start the Threads
    pthread_t stage_1_thread;
    pthread_t stage_2_thread;
    pthread_t stage_3_thread;

    assert(pthread_create(&stage_1_thread, NULL, stage_1_fn, (void*)&s1d) == 0);
    assert(pthread_create(&stage_2_thread, NULL, stage_2_fn, (void*)&s2d) == 0);
    assert(pthread_create(&stage_3_thread, NULL, stage_3_fn, (void*)&s3d) == 0);

    return 0;
}

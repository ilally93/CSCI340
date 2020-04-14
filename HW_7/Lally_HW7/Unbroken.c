
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_cond_t headc = PTHREAD_COND_INITIALIZER;
pthread_cond_t tailc = PTHREAD_COND_INITIALIZER;

typedef struct __node_t {

    int              value;
    struct __node_t * next;

} node_t;

typedef struct {

    node_t *        head;
    node_t *        tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;

} queue_t;

void Queue_Init(queue_t *q) {

    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;

    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);

}

void Queue_Enqueue(queue_t * q,
                   int       value) {

    pthread_mutex_lock(&q->tail_lock);
    // Unlocks and waits to be signaled
    while (value != 0){
        pthread_cond_wait(&tailc, &q->tail_lock);
    }
    node_t *tmp = malloc(sizeof(node_t));             /* Get a new node */
    // Fix: Need to have continual check of while instead of if statement
    if (tmp == NULL) {                            /* Did the allocation fail? */
        perror("malloc");
        return -1;
    }

    assert(tmp != NULL);
    tmp->value = value;                           /* Set the node's contents */
    tmp->next  = NULL;                            /* Show it's the tail */

    q->tail->next = tmp;                          /* Point old tail to new tail */
    q->tail = tmp;                                /* Point tail to new node */

    // Restarts a thread waiting on the conditional
    pthread_cond_signal(&tailc);
    pthread_mutex_unlock(&q->tail_lock);

}

int Queue_Dequeue(queue_t * q,
                  int *     value) {

    // Failure is always an option
    int rc = -1;

    // Fix: Need to have continual check of while instead of if statement
    // Changed q_head to q->head
    while (q->head->next != NULL) {
        *value = q->head->next->value;             /* Return the value */
        pthread_mutex_lock(&q->head_lock);        /* Lock the list */
        // Unlocks and waits to be signaled
        while (value == 0){
            pthread_cond_wait(&headc, &q->head_lock);
        }
        node_t *tmp = q->head;                    /* Save the old head node pointer */
        q->head = q->head->next;                   /* Reset the head */
        // Restarts a thread waiting on the conditional
        pthread_cond_signal(&headc);
        pthread_mutex_unlock(&q->head_lock);      /* Unlock the list */
        free(tmp);                                /* Free the old head node */
        rc = 0;
    }


    return rc;

}

int main(int argc, char *argv[]){
    return 0;
}

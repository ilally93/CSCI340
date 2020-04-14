// CSCI-340 - Homework #7

// Starter file for the double linked list


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int key = 1;

// basic node structure

typedef struct __node_t {

    int key;
    struct __node_t *next;
    struct __node_t *prev;

} node_t;

// basic list structure (one used per list)

typedef struct {

    node_t *head;
    node_t *tail;
    pthread_mutex_t lock;

} list_t;

// Thread Parameters for Testing
struct threadInf{

    list_t *list;
    int thr;

};

// Initialize the list

void List_Init(list_t *L) {

    // Add code here to initialize the list
    L->head = NULL;
    L->tail = NULL;
    L->head->next = L->tail;
    L->head->prev = NULL;
    L->tail->prev = L->head;
    L->tail->next = NULL;
    pthread_mutex_init(&L->lock, NULL);

}

// Insert into the list (At the front)

void List_Insert(list_t *L,
                 int key) {

    // Add code here to safely insert a new node at the beginning of the list
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        exit(-1);
    }

    new->key = key;
    pthread_mutex_lock(&L->lock);
    if(L->head != NULL){
        new->next = L->head;
        L->head->prev = new;
    }
    else{
        new->next = L->tail;
        if(L->tail != NULL){
            L->tail->prev = new;
        }
    }
    new->prev = NULL;
    L->head = new;

    pthread_mutex_unlock(&L->lock);

}

// Insert into the list (At the end)

void List_Append(list_t *L,
                 int key) {
    // Add code here to safely insert a new node at the end of the list
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        exit(-1);
    }

    new->key = key;
    pthread_mutex_lock(&L->lock);
    if(L->tail != NULL){
        new->prev = L->tail;
        L->tail->next = new;
    }
    else{
        new->prev = L->head;
        if(L->head != NULL){
            L->head->next = new;
        }
    }
    new->next = NULL;
    L->tail = new;
    pthread_mutex_unlock(&L->lock);

}


int List_Lookup(list_t *L,
                int key) {

    // Add code here to lookup an item in the list

    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            pthread_mutex_unlock(&L->lock);
            return 0;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);

    return -1;
}


int main(){

    // Add code here to test your list
    list_t *testL = malloc(sizeof(list_t));

    if(List_Lookup(testL, key) == 0){
        printf("Node %d Found\n", key);
        key++;
    }
    else{
        printf("Node %d Not Found\n", key);
        List_Insert(testL, key);
        if(List_Lookup(testL, key) == 0){
            printf("Node %d Found After Insert\n", key);
            key++;
        }
        else{
            printf("Node %d Insert Failed\n", key);
            key++;
        }
    }

    if(List_Lookup(testL, key) == 0){
        printf("Node %d Found\n", key);
        key++;
    }
    else{
        printf("Node %d Not Found\n", key);
        List_Append(testL, key);
        if(List_Lookup(testL, key) == 0){
            printf("Node %d Found After Append\n", key);
            key++;
        }
        else{
            printf("Node %d Append Failed\n", key);
            key++;
        }
    }

    free(testL);

}

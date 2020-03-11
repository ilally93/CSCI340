// CSCI-340 - Homework #7

// Starter file for the double linked list


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


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
    new->next = L->head;
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
    printf("Key during Append: %d\n", key);
    pthread_mutex_lock(&L->lock);
    new->prev = L->tail;
    new->next = NULL;
    L->tail = new;
    pthread_mutex_unlock(&L->lock);

}

int List_Lookup(list_t *L,
                int key) {

    // Add code here to lookup an item in the list

    node_t *curr = L->head;

    while(curr){
        pthread_mutex_lock(&L->lock);
        printf("Curr key: %d\n", curr->key);
        printf("Searching for: %d key\n", key);
        if(curr->key == key){
            pthread_mutex_unlock(&L->lock);
            return 0;
        }
        pthread_mutex_unlock(&L->lock);
        curr = curr->next;
    }

    return -1;
}

int main()
{

    // Add code here to test your list
    list_t *testL = malloc(sizeof(list_t));
    int key = 1;
    if(List_Lookup(testL, key) == 0){
        printf("Node %d Found\n\n", key);
    }
    else{
        printf("Node %d Not Found\n\n", key);
        List_Insert(testL, key);
        if(List_Lookup(testL, key) == 0){
            printf("Node %d Found After Insert\n\n", key);
            key++;
            printf("key After Insert: %d\n", key);
        }
        else{
            printf("Node %d Insert Failed\n\n", key);
        }
    }

    if(List_Lookup(testL, key) == 0){
        printf("Node %d Found\n\n", key);
    }
    else{
        printf("Node %d Not Found\n\n", key);
        List_Append(testL, key);
        if(List_Lookup(testL, key) == 0){
            printf("Node %d Found After Append\n\n", key);
            key++;
            printf("Key After Append: %d", key);
        }
        else{
            printf("Node %d Append Failed\n\n", key);
        }
    }

}

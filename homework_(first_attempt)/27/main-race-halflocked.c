#include <stdio.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t m;

void* worker(void* arg) {

    //pthread_mutex_lock(&m);
        balance++; // unprotected access
    //pthread_mutex_unlock(&m);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_mutex_init(&m, NULL);
    Pthread_create(&p, NULL, worker, NULL);
    
    pthread_mutex_lock(&m);
        balance++; // protected access
    pthread_mutex_unlock(&m);
    
    Pthread_join(p, NULL);
    return 0;
}

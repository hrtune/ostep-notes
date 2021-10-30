#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_THREADS 4

#define LOOP 1200000 / NUM_THREADS

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUM_THREADS];
    pthread_mutex_t llock[NUM_THREADS];
    int threshold;
} counter_t;

typedef struct __args_t{
    int tid;
    counter_t *c;
} args_t;

void init(counter_t *c, int threshold){
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for(i = 0; i < NUM_THREADS; i++){
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int thread_id, int amt){
    int t = thread_id % NUM_THREADS;
    pthread_mutex_lock(&c->llock[t]);
    c->local[t] += amt;
    if(c->local[t] >= c->threshold){
        pthread_mutex_lock(&c->glock);
        c->global += c->local[t];
        pthread_mutex_unlock(&c->glock);
        c->local[t] = 0;
    }
    pthread_mutex_unlock(&c->llock[t]);
}

void increment(counter_t *c, int thread_id){
    update(c, thread_id, 1);
}

void decrement(counter_t *c, int thread_id){
    update(c, thread_id, -1);
}


void *work(void *a){
    int i;
    args_t *args = (args_t *)a;
    counter_t *c = args->c;
    int thread_id = args->tid;
    for(i = 0; i < LOOP; i++){
        increment(c, thread_id);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    struct timeval *start, *end;
    start = malloc(sizeof(start));
    end = malloc(sizeof(end));
    double delay;
    pthread_t thr[NUM_THREADS];
    counter_t *c = (counter_t *)malloc(sizeof(counter_t));
    args_t *args = (args_t *)malloc(sizeof(args_t));
    int j;
    gettimeofday(start, NULL);
    for(j = 0; j < 10; j++){
        init(c, atoi(argv[1]));
        int i;
        for(i = 0; i < NUM_THREADS; i++){
            args->tid = i;
            args->c = c;
            pthread_create(&thr[i], NULL, work, (void *)args);
        }
        for(i = 0; i < NUM_THREADS; i++){
            pthread_join(thr[i], NULL);
        }
    }
    gettimeofday(end, NULL);
    printf("counter value: %d\n", c->global);
    delay = (end->tv_sec - start->tv_sec);
    delay +=  (end->tv_usec - start->tv_usec) / 1000000.0;
    delay = delay / 10;
    printf("delay time is: %lf (s)\n",delay);
    return 0;
}


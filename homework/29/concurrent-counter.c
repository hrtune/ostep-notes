#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>
#define DUTY 10000000
#define LOOP 100

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c){
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c){
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c){
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c){
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

void *work(void *arg){
    int i;
    counter_t *c = (counter_t *)arg;
    for(i = 0; i < LOOP; i++){
        increment(c);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    struct timeval *start, *end;
    start = malloc(sizeof(start));
    end = malloc(sizeof(end));
    double delay;
    const int num_t = atoi(argv[1]);
    const int duty = DUTY / LOOP;
    pthread_t thr[num_t];
    counter_t *c = (counter_t *)malloc(sizeof(counter_t));
    int j;
    gettimeofday(start, NULL);
    for(j = 0; j < duty; j++){
        init(c);
        int i;
        for(i = 0; i < num_t; i++){
            pthread_create(&thr[i], NULL, work, (void *)c);
        }
        for(i = 0; i < num_t; i++){
            pthread_join(thr[i], NULL);
        }
    }
    gettimeofday(end, NULL);
    printf("counter value: %d\n", c->value);
    
    delay = (end->tv_sec - start->tv_sec) * 1000000;
    delay +=  (end->tv_usec - start->tv_usec);
    delay = delay / duty / num_t;
    printf("delay time is: %d (us)\n",(int)delay);
    return 0;
}


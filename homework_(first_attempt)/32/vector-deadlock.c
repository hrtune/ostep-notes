#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

#include "main-header.h"
#include "vector-header.h"

void vector_add(vector_t *v_dst, vector_t *v_src) {
    /* Add two vectors and store the sum to the first vector (*v_dst) */
    Pthread_mutex_lock(&v_dst->lock);
    Pthread_mutex_lock(&v_src->lock);
    int i;
    for (i = 0; i < VECTOR_SIZE; i++) {
	v_dst->values[i] = v_dst->values[i] + v_src->values[i];
    }
    Pthread_mutex_unlock(&v_dst->lock);
    Pthread_mutex_unlock(&v_src->lock);
}

/* 
    Assume #1 (thread 1) has called vector_add(v1,v2) meanwhile #2 called vector_add(v2,v1).
    Firstly, #1 holds the lock 'v1->lock'. After the concurrent switch to #2, #2 holds 'v2->lock',
    which is the first argument of vector_add so it is the 'v_dst->lock' defined in the function.
    #1 holds v1->lock and #2 holds v2->lock on the first line in the function, which causes deadlock.
*/

void fini() {}

#include "main-common.c"

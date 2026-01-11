#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(){

    double delay;

    struct timeval *start, *end;
    start = malloc(sizeof(start));
    end = malloc(sizeof(end));
    long *dummy = (long *)malloc(sizeof(long));

    for(long itr = 10; itr <= 1000000000; itr *= 10){

        *dummy = 0;
        gettimeofday(start, NULL);
        for(long i = 0; i < itr; i++){
            *dummy += 1;
        }
        gettimeofday(end, NULL);

        delay = (end->tv_sec - start->tv_sec) * 1000000 / (double)itr;
        delay +=  (end->tv_usec - start->tv_usec) / (double)itr;
        //printf("delay : %lf\n", delay);

        printf("%10ld times loop: %lf us\n", itr, delay);

    }
    
    return 0;
}
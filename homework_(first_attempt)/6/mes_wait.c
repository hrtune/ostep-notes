#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(){

    double null_delay;
    double wait_delay;

    struct timeval *start, *end;
    start = malloc(sizeof(start));
    end = malloc(sizeof(end));

    gettimeofday(start, NULL);
    for(int i = 0; i < 1000000; i++){
    }
    gettimeofday(end, NULL);

    null_delay = end->tv_sec - start->tv_sec;
    null_delay +=  (end->tv_usec - start->tv_usec) / 1000000.0 ;

    



    gettimeofday(start, NULL);
    for(int i = 0; i < 1000000; i++){
        wait(NULL);
    }
    gettimeofday(end, NULL);

    wait_delay = end->tv_sec - start->tv_sec;
    wait_delay +=  (end->tv_usec - start->tv_usec) / 1000000.0 ;

    //printf("%lf\n", null_delay);
    //printf("%lf\n", wait_delay);

    printf("%lf micro second(s)\n", wait_delay - null_delay);
    
    return 0;
}
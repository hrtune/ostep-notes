#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(){

    struct timeval *tv1, *tv2;

    tv1 = malloc(sizeof(tv1));
    tv2 = malloc(sizeof(tv2));


    gettimeofday(tv1, NULL);
    gettimeofday(tv2, NULL);
    
    printf("%ld %ld\n",tv1->tv_sec, tv1->tv_usec);
    printf("%ld %ld\n",tv2->tv_sec, tv2->tv_usec);

    return 0;
}
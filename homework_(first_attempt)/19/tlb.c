#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

#define PAGESIZE 1024

int main(int argc, char *argv[]){

    int jump = PAGESIZE / sizeof(int);
    

    if(argc != 2){
        printf("Error!\n");
        return 1;
    }

    double delay;
    int num = atoi(argv[1]);
    const long trials = 1000000000 / num;
    struct timeval *start, *end;
    start = malloc(sizeof(start));
    end = malloc(sizeof(end));
    int dummy[num * jump];

    gettimeofday(start, NULL);
    for(long itr = 0; itr < trials; itr++){
        for(int i = 0; i < num * jump; i += jump){
            dummy[i] += 1;
        }
    }
    gettimeofday(end, NULL);

    delay = (end->tv_sec - start->tv_sec) * 1000000 / (double)trials * 1000.0; // nano seconds
    delay +=  (end->tv_usec - start->tv_usec) / (double)trials * 1000.0;
    printf("%d %d\n", num, (int)delay); 

    return 0;
}
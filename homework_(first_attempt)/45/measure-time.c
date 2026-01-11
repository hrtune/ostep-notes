#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>

int xor(const char *file){
    
    FILE *fp;
    unsigned char buff;
    unsigned char result = 0;

    fp = fopen(file, "rb");
    
    while(fread(&buff, 1, 1, fp) == 1){
        result = result ^ buff;
    }
    
    fclose(fp);

    return result;
}

int *fletcher(const char *file){

    FILE *fp;
    unsigned char buff;
    int *s = (int *)malloc(sizeof(int) * 2);

    fp = fopen(file, "rb");
    
    while(fread(&buff, 1, 1, fp) == 1){
        s[0] = (s[0] + (int)buff) % 255;
        s[1] = (s[0] + s[1]) % 255;
    }

    fclose(fp);

    return s;
}

int main(int argc, const char *argv[]){

    FILE *fp;
    unsigned char buff;
    unsigned char bytes[512];
    unsigned char result = 0;
    
    int s1 = 0;
    int s2 = 0;
    int x;
    
    int i, j, len;
    
    const int mlt = 1;
    const int itr = 1000 * 1000 * mlt;
    struct timeval *start, *end;

    int xor_time, flet_time;

    fp = fopen(argv[1], "rb");
    
    i = 0;
    while(fread(&buff, 1, 1, fp) == 1){
        bytes[i] = buff;
        i++;
    }
    len = i;

    start = malloc(sizeof(start));
    end = malloc(sizeof(end));

    gettimeofday(start, NULL);
    for(j = 0; j < itr; j++){
        x = 0;
        for(i = 0; i < len; i++){
            x = x ^ bytes[i];
        }
    }
    gettimeofday(end, NULL);

    xor_time = end->tv_usec - start->tv_usec;
    xor_time = xor_time / mlt;
    
    gettimeofday(start, NULL);
    for(j = 0; j < itr; j++){
        s1 = 0;
        s2 = 0;
        for(i = 0; i < len; i++){
            s1 = (s1 + bytes[i]) % 255;
            s2 = (s1 + s2) % 255;
        }
    }
    gettimeofday(end, NULL);

    flet_time = end->tv_usec - start->tv_usec;
    flet_time = flet_time / mlt;

    printf("%.3f\n", xor_time / 1000.0);
    printf("%.3f\n", flet_time / 1000.0);
    return 0;
}
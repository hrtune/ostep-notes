#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#define PATH "/bin/ls"

int main(int argc, char *argv[]){
    
    /*if(argc < 2){
        printf("error: no argument\n");
        exit(1);
    } */

    int sel = atoi(argv[0]);
    
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("hello!\n");
    } else {
        wait(NULL);
        printf("goodbye!\n");
    }
    return 0;
}
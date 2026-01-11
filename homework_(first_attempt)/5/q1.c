#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello world! (pid: %d) \n", (int) getpid());
    int x = 100;
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("Hello!, I am child (pid: %d)\n", (int) getpid());
        printf("Child: x is %d\n", x);
        x++;
        printf("Child: x++ is %d\n", x);
    } else {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
        printf("Parent: x is %d\n", x);
        x++;
        printf("Parent: x++ is %d\n", x);
    }
    return 0;
}
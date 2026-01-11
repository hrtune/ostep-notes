#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    printf("Hello world! (pid: %d) \n", (int) getpid());
    int filedesc = open("q2_text.txt", O_WRONLY | O_APPEND);
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("Hello!, I am child (pid: %d)\n", (int) getpid());
        if(filedesc < 0){
            printf("The file can't be opened! (child)\n");
            return 1;
        }
        write(filedesc, "I am child.\n", strlen("I am child.\n"));
        

    } else {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
        if(filedesc < 0){
            printf("The file can't be opened! (parent)\n");
            return 1;
        }
        write(filedesc, "I am parent.\n", strlen("I am parent.\n"));
    }
    
    close(filedesc);

    return 0;
}
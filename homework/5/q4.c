#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#define PATH "/bin/ls"

int main(int argc, char *argv[]){
    // create file "q3.txt" contains single character "F"
    
    if(argc < 2){
        printf("error: no argument\n");
        exit(1);
    }

    int sel = atoi(argv[0]);
    
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        char *args[] = {PATH, NULL};
        switch(sel){
            case 0:
                execv(args[0], args);
                break;
            
            case 1:
                execl(PATH, "ls", (char *)NULL);
                break;
            
        }
    } else {
        wait(NULL);
        printf("goodbye!\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    // create file "q3.txt" contains single character "F"
    int fd = open("q3.txt", O_WRONLY | O_CREAT);
    write(fd, "F", 1);
    close(fd);

    int x = 100;
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("hello!\n");
        int fd = open("q3.txt", O_WRONLY);
        write(fd, "T", 1);
        close(fd);
    } else {
        while(1){
            char c;
            int fd = open("q3.txt", O_RDONLY, 1);
            if(fd < 0){
                printf("read error!\n");
                return 1;
            }
            read(fd, &c, 1);
            close(fd);
            if(c == 'T')
                break;

        }
        printf("goodbye!\n");
        

    }
    return 0;
}
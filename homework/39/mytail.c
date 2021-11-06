#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int fd = open(argv[2], O_RDONLY);
    int l = atoi(argv[1]);
    int line_count = 0;
    int count = 0;
    char c;
    lseek(fd, 0 , SEEK_END);

    while(1){
        lseek(fd, -1 , SEEK_CUR);
        read(fd, &c, 1);
        lseek(fd, -1 , SEEK_CUR);
        
        if(c == '\n'){
            line_count += 1;
        }

        if(line_count >= l){
            break;
        }
        count += 1;
    }

    
    //printf("%d\n", count);
    
    char tail[count + 1];
    
    lseek(fd, 1 , SEEK_CUR);

    read(fd, tail, count + 1);

    tail[count] = '\0';

    printf("%s\n", tail);

    close(fd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char *argv[]){
    if(argc != 2){
        printf("Error! , Enter the path or file.\n");
        return 1;
    }
    const char *path = argv[1];
    printf("%s\n", path);
    struct stat buff;
    if(stat(path, &buff) == 0){

        printf("Size: %ld\n", buff.st_size);
        printf("Blocks: %ld\n", buff.st_blocks);
        printf("IO Blocks: %ld\n", buff.st_blksize);
        printf("Inode: %ld\n", buff.st_ino);
        printf("Links: %ld\n", buff.st_nlink);
        printf("Protection: %d\n", buff.st_mode);
        printf("Uid: %d\n", buff.st_uid);
        printf("Gid: %d\n", buff.st_gid);
        
        printf("Access: %ld\n", buff.st_atim.tv_sec);
        printf("Modify: %ld\n", buff.st_mtim.tv_sec);
        printf("Change: %ld\n", buff.st_ctim.tv_sec);
    
    } else{
        printf("Error! , stat() couldn't get the info.\n");
        return 1;
    }

    return 0;
}
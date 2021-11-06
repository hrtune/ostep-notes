#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[]){
    struct stat buf;
    DIR *dirp;
    struct dirent *entry;
    char dir[256];
    if(argc == 1){
        printf("Usage: myls [absolute path] [-l]\n");
    }
    else if(argc >= 2){
        dirp = opendir(argv[1]);
        entry = readdir(dirp);
        if( (argc == 3) && (argv[2][1] == 'l') ){
            while(entry != NULL){
                strcpy(dir, argv[1]);
                strcat(dir, entry->d_name);
                stat(dir, &buf);
                printf("%d %d %d %ld %ld %s\n", buf.st_mode, buf.st_uid, buf.st_gid, buf.st_size, buf.st_mtim.tv_sec, entry->d_name);
                entry = readdir(dirp);
            }
        }else{
            while(entry != NULL){
                printf("%s\n", entry->d_name);
                entry = readdir(dirp);
            }
        }
    }
    
    return 0;
    
}
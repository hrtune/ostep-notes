#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void leveler(int level){
    int i;
    for(i = 0; i < level; i++){
        printf(" ");
    }
}

int is_dotdir(const char *dir){
    if(dir[0] == '.'){
        if(dir[1] == '.' || dir[2] == '\0'){
            return 1;
        }
    }
    return 0;
}

int is_dir(const char *path){
    
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

void myls(const char *path, int level){
    
    struct dirent *entry;
    DIR *d = opendir(path);
    char fullpath[1024];
    strcpy(fullpath, path);
    while(1){
        entry = readdir(d);
        if((entry == NULL) || (is_dotdir(entry->d_name))){
            break;
        }

        strcat(fullpath, "/");
        strcat(fullpath, entry->d_name);

        leveler(level);
        printf("%s", entry->d_name);
        
        if(is_dir(fullpath)){
            printf(" (d)\n");
            myls(fullpath, level + 1);
        }
        else{
            printf("\n");
        }
        
        strcpy(fullpath, path);
    }

}



int main(int argc, char *argv[]){
    const char path[] = "/home";
    printf("%s\n", path);
    myls(path, 1);
}
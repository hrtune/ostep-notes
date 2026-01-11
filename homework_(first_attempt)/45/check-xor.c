#include <stdio.h>

int main(int argc, char *argv[]){

    unsigned char buff;
    unsigned char result = 0;
    FILE *fp;
    size_t size;

    fp = fopen(argv[1], "rb");
    
    while(fread(&buff, 1, 1, fp) == 1){
        result = result ^ buff;
    }
    
    printf("%d\n", result);

    fclose(fp);
    return 0;
}
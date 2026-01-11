#include <stdio.h>

int main(int argc, char *argv[]){

    unsigned char buff;
    int s1 = 0;
    int s2 = 0;
    FILE *fp;
    size_t size;

    fp = fopen(argv[1], "rb");
    
    while(fread(&buff, 1, 1, fp) == 1){
        printf("%x\n",buff);
        s1 = (s1 + (int)buff) % 255;
        s2 = (s1 + s2) % 255;
    }
    
    printf("%d %d\n", s1,s2);

    fclose(fp);
    return 0;
}
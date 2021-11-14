#include <stdio.h>

void printd(int d, FILE *fp){
    char buff;
    fseek(fp, d, SEEK_SET);
    fread(&buff, 1, 1, fp);
    printf("%c", buff);
}

int main(int argc, const char *argv[]){
    FILE *fp;
    char buff;

    fp = fopen("digits.txt", "r");

    for(int i = 0; i < 10; i++){
        printd(i, fp);
    }

    fclose(fp);
    printf("\n");
    return 0;
}
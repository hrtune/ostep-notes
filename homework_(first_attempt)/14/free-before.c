#include <stdio.h>
#include <stdlib.h>

int main(){
    int *data = (int *)malloc(10 * sizeof(int));

    data[0] = 0;
    data[1] = 3;
    data[2] = 12345;
    data[3] = -1;
    data[4] = 11111;
    data[5] = 1024;

    free(data);

    printf("%d\n", data[3]);
    return 0;
}
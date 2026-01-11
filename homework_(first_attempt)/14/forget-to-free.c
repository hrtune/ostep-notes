#include <stdio.h>
#include <stdlib.h>

int main(){
    int *a = (int *)malloc(10 * sizeof(int));
    a[0] = 100;
    a[1] = 33333;
    a[2] = -256;
    a[3] = 123456;
    return 0;
}
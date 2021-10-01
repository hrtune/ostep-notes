#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    pid_t child_a, child_b;

    child_a = fork();

    if (child_a == 0) {
        // child a code
        printf("a\n");
    } else {
        child_b = fork();

        if (child_b == 0) {
            /* Child B code */
            waitpid(child_a, NULL, 0);
            printf("b\n");
        } else {
            /* Parent Code */
            waitpid(child_b, NULL, 0);
            printf("p\n");
        }
    }
}
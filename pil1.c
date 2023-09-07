#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("I am the child\n");
        for (int i = 1; i <= 10; i++) {
            printf("Child message %d\n", i);
            sleep(1);
        }
        exit(0);
    } else if (pid > 0) {
        printf("I am the parent\n");
        for (int i = 1; i <= 10; i++) {
            printf("Parent message %d\n", i);
            sleep(2);
        }
        exit(0);
    }
}
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void wakeup(int signum) {
    for (int i = 1; i <= 20; i++) {
        printf("Message %d from child.\n", i);
        sleep(1);
    }
}

void main() {
    pid_t pid = fork();
    pid_t childpid;
    if (pid == 0) {
        printf("I am the child.\n");
        childpid = getpid();
        signal(SIGUSR1, wakeup);
        exit(1);
    } else if (pid > 0) {
        printf("I am the parent.\n");
        for (int i = 1; i <= 30; i++) {
            printf("Message %d from parent.\n", i);
            if (i == 5) {
                kill((int)childpid, SIGUSR1);
            }
            sleep(1);
        }
        exit(1);
    }
}
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
    signal(SIGUSR1, wakeup);
    pid_t pid = fork();

    if (pid == 0) {
        while (1);
        exit(1);
    }
    while (1) {
        for (int i = 1; i <= 30; i++) {
            printf("Message %d from parent.\n", i);
            if (i == 5) {
                kill(pid, SIGUSR1);
            }
            sleep(1);
        }

        exit(1);
    }
}
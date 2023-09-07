#include <stdio.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void main(int argc, char* cmd[]) {
    pid_t pid;
    char *argv[] = {"thunderbird", "-c", cmd[1], NULL};
    int status;
    status = posix_spawn(&pid, "/usr/bin/thunderbird", NULL, NULL, argv, environ);
    printf("The child pid is: %i\n", pid);
    waitpid(pid, &status, 0);
}
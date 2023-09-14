#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COUNT 200
#define N 10

char buffer[N];
int writeIndx = 0;
int readIndx = 0;
int count = 0;

int put(char item) {
    if(count == N) {
        return 0; // Buffer is full
    }
    buffer[writeIndx] = item;
    writeIndx = (writeIndx + 1)  % N;
    count++;
    return 1;
}
int get(int* item) {
    if (readIndx == writeIndx) {
        return 0; // buffer is empty
    }

    *item = buffer[readIndx];
    readIndx = (readIndx + 1) % N;
    count--;
    printf("Got the letter %s\n", &item);
    return 1;
}

void ChildProcess(void) {
    int i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("  This line is from child, value = %d\n", i);
    }
    printf("  *** Child process is done ***\n");
}

void ParentProcess(void) {
    int i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("*** Parent is done ***\n");

    char word[] = "Miguel";

    int i = 0;
    while(put(word[i])) {
        i++;
    }
}

void main(void) {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        ChildProcess();
    } else {
        ParentProcess();
    }
}void ChildProcess(void) {
    int i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("  This line is from child, value = %d\n", i);
    }
    printf("  *** Child process is done ***\n");
}

void ParentProcess(void) {
    int i;

    for (i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("*** Parent is done ***\n");

    char word[] = "Miguel";

    int i = 0;
    while(put(word[i])) {
        i++;
    }
}
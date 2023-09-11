#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <signal.h>

#define N 100

// Words to read
char word[10][20] = { "tiger", "lion", "elephant", "zebra", "horse", "camel", "deer", "crocodile", "rabbit", "monkey" };

// Shared Circular Buffer
struct CIRCULAR_BUFFER {
    int count;              // Number of items in the buffer
    int lower;              // Next slot to read in the buffer
    int upper;              // Next slot to write in the buffer
    char buffer[N][20];
};
struct CIRCULAR_BUFFER *buffer = NULL;

int put(char word[]) {
    if ((buffer->upper + 1) % N == buffer->lower) {
        // Buffer is full, avoid overflow
        return 0;
    }
    buffer->buffer[buffer->upper][20] = word;
    buffer->upper = (buffer->upper + 1) % N;
    return 1;
}

int get(char* word[]){
    if(buffer->lower == buffer->upper){
        //buffer is empty
        return 0;
    }

    *word = buffer->buffer[buffer->lower];
    buffer->lower = (buffer->lower) % N;
    return 1;
}

void producer(char word[]) {
    int i = 0;
    while(i < N){
        sleep(1);

        // Add word
        put(word);
        i++;
    }
}

void consumer(char word[]) {
    int i = 0;
    while(i < N){
        // Get word
        get(&word);
    }

    // Display word
    printf("The word is %s.\n", word);
    sleep(1);
}

void wakeupConsumer(int signum){
    int i = 0;
    while(i < 10) {
        consumer(word[i]);
    }
}

void wakeupProducer(int signum) {
    int i = 0;
    while(i < 10) {
        producer(word[i]);
    }
}

int main(int argc, char* argv[]) {
    signal(SIGUSR1, wakeupConsumer);
    signal(SIGUSR2, wakeupProducer);
    // Create shared memory for the Circular Buffer to be shared between the Parent and Child Processes
    buffer = (struct CIRCULAR_BUFFER*)mmap(0, sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;
    
    // Create threads
    __pid_t pid;
    __pid_t otherPid;
    
    // Use fork()
    pid = fork();
    if (pid == -1) {
        // Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // OK: If fork() returns non zero then the parent process is running else child process is running
    if (pid == 0) {
        // Run Producer Process logic as a Child Process
        otherPid = getppid();
        kill(pid, SIGUSR1);
    } else {
        // Run Consumer Process logic as a Parent Process
        otherPid = pid;
        kill(pid, SIGUSR2);
    }

    return 0;
}
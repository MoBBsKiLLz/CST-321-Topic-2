#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* show_message(void* arg) {
    long long *limit_ptr = (long long*) arg;
    long long limit = *limit_ptr;

    for (int i = 0; i <= 10; ++i) {
        printf("This is message %d\n", i);
        sleep(limit);
    }
}

int main(int argc, char **argv) {
    long long limit1 = 1;
    long long limit2 = 2;
    
    // Thread IDs
    pthread_t tid1;
    pthread_t tid2;

    // Create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Create Threads
    pthread_create(&tid1, &attr, show_message, &limit1);
    pthread_create(&tid2, &attr, show_message, &limit2);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
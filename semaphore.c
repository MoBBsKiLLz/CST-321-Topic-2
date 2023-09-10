#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Author: Miguel Zepeda
#define THREAD_NUM 2

int buffer[10];
int count = 0;

pthread_mutex_t mutexBuffer;

void* producer(void* args) {
    while(1) {
        // Produce random number
        int x = rand() % 100;

        pthread_mutex_lock(&mutexBuffer);
        // Add to buffer
        buffer[count] = x;
        count = count + 1;
        pthread_mutex_unlock(&mutexBuffer);
    }
}

void* consumer(void* args) {
    while(1) {
        // Remove from buffer
        pthread_mutex_lock(&mutexBuffer);
        int y = buffer[count - 1];
        count = count - 1;
        pthread_mutex_unlock(&mutexBuffer);

        // Consume
        printf("Got %d\n", y);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    // Create producer and consumer threads
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    int i;
    for(i = 0; i < THREAD_NUM; i++) {
        if(phtread_create(&th[i], NULL, &producer, NULL) != 0) {
            perror("Failed to create thread");
        } else {
            if(phtread_create(&th[i], NULL, &consumer, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    // Wait for threads to finish
    for (i = 0; i < THREAD_NUM; i++){
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}
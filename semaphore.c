#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Author: Miguel Zepeda
#define THREAD_NUM 4

sem_t semEmpty;
sem_t semFull;

int restroom[2];
int count = 0;

pthread_mutex_t mutexRestroom;

void* business(void* args) {
    while(1) {
        // Produce random number
        int x = rand() % 2;
        sleep(1);

        // Add to restroom
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexRestroom);
        if (count < 1) {
            restroom[count] = x + 1;
            count = count + 1;
        } else {
            printf("Skipped %d\n", x);
        }
        pthread_mutex_unlock(&mutexRestroom);
        sem_post(&semFull);
    }
}

void* customer(void* args) {
    while(1) {
        // Remove from restroom
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexRestroom);
        int y = restroom[count - 1];
        count = count - 1;
        pthread_mutex_unlock(&mutexRestroom);
        sem_post(&semEmpty);

        // Consume
        printf("Restroom %d is being used\n", y);
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    // Create business and customer threads
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexRestroom, NULL);
    sem_init(&semEmpty, 0, 1);
    sem_init(&semFull, 0, 0);
    int i;
    for(i = 0; i < THREAD_NUM; i++) {
        if (i == 0) {
            if(pthread_create(&th[i], NULL, &business, NULL) != 0) {
                perror("Failed to create thread");
            } 
        } else {
            if(pthread_create(&th[i], NULL, &customer, NULL) != 0) {
            perror("Failed to create thread");
            }
        }
    }

    // Wait for threads to finish
    for (i = 0; i < THREAD_NUM; i++){
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexRestroom);
    return 0;
}
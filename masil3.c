#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Global variables
#define NUM_DEPOSITS 1000000
long long balance = 0;

// Create semaphore
sem_t mutex;

void* add_balance(void* arg) {
    int amount = *(int *) arg;
    for (int i = 0; i < NUM_DEPOSITS; i++) {
        sem_wait(&mutex);
        balance += amount;
        sem_post(&mutex);
    }
    pthread_exit(NULL);
}

int main(void) {
    // Shared variable
    int amount = 1;

    // Initialize semaphore
    sem_init(&mutex, 0, 1);

    // Spawn threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, add_balance, &amount);

    pthread_t tid2;
    pthread_create(&tid2, NULL, add_balance, &amount);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Show the total balance
    printf("Balance = %lld\n", balance);

    // Destroy semaphore
    sem_destroy(&mutex);
    return 0;
}
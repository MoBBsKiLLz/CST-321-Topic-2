#include <stdio.h>
#include <pthread.h>

// Global variables
#define NUM_DEPOSITS 1000000
long long balance = 0;

void* add_balance(void* arg) {
    int amount = *(int *) arg;
    for (int i = 0; i < NUM_DEPOSITS; i++) {
        balance += amount;
    }
    pthread_exit(NULL);
}

int main(void) {
    // Shared variable
    int amount = 1;

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
    return 0;
}
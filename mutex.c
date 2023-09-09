#include <stdio.h>
#include <pthread.h>

// Author: Miguel Zepeda

// Global variable
long long balance = 1000000;

// Create mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* withdraw(void* arg) {
    // derefence amount from arg
    int amount = *(int *) arg;
    // loop until the amount is reached
    for (int i = 0; i < amount; i++) {
        // Begining of critical section
        pthread_mutex_lock(&mutex); // Lock the resource
        // decrease balance by 1
        balance -= 1;
        // End of critical section
        pthread_mutex_unlock(&mutex); // release the resource
    }
    // Exit thread with NULL
    pthread_exit(NULL);
}

int main(void) {
    // Amount variables
    int amount1 = 500000;
    int amount2 = 250000;
    int amount3 = 125000;

    // Spawn threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, withdraw, &amount1);

    pthread_t tid2;
    pthread_create(&tid2, NULL, withdraw, &amount2);

    pthread_t tid3;
    pthread_create(&tid3, NULL, withdraw, &amount3);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Show the remaining balance
    printf("Balance = %lld\n", balance);
    // Exit program
    return 0;
}
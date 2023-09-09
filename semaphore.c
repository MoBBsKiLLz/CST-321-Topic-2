#include <stdio.h>
#include <pthread.h>

// Author: Miguel Zepeda

// Global variable
int key = 1;

void* withdraw(void* arg) {
    // Derefence person from arg
    int person = *(int *) arg;
    // Begining of critical section
    key -= person; // Person takes key
    // End of critical section
    // Exit thread with 0
    pthread_exit(NULL);
}

int main(void) {
    // Person variable
    int person = 1;

    // Spawn threads
    pthread_t tid1;
    pthread_create(&tid1, NULL, withdraw, &person);

    pthread_t tid2;
    pthread_create(&tid2, NULL, withdraw, &person);

    pthread_t tid3;
    pthread_create(&tid3, NULL, withdraw, &person);

    // Wait for threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Exit program
    return 0;
}
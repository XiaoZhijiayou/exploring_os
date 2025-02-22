#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;

int shared_counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        shared_counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

// 线程之间的
int main() {
    pthread_t threads[2];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", shared_counter);
    return 0;
}
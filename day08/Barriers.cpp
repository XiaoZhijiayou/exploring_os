#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 3
pthread_barrier_t barrier;

void* barrier_thread(void* arg) {
    int id = *(int*)arg;
    
    printf("Thread %d before barrier\n", id);
    // 这个屏障相当于一个栅栏，让所有线程都到这个栅栏，然后一起继续，就例如于一个人要走，需要三个人一起到一个地方，然后一起走
    pthread_barrier_wait(&barrier);
    printf("Thread %d after barrier\n", id);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, barrier_thread, &thread_ids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_barrier_destroy(&barrier);
    return 0;
}
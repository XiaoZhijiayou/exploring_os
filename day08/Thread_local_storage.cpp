#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 用于标识线程局部存储数据的位置, 每个线程可以通过这个键存取属于它自己的数据。
pthread_key_t thread_key;

void cleanup_thread_data(void* data) {
    free(data);
}

void* thread_function(void* arg) {
    void* data = malloc(sizeof(int));
    *(int*)data = *(int*)arg;
    
    //当前线程设置线程局部存储（TLS）数据。
    pthread_setspecific(thread_key, data);
    
    //  用于访问当前线程的线程局部存储数据
    // Access thread-local storage
    void* tls_data = pthread_getspecific(thread_key);
    printf("Thread %d: TLS value = %d\n", *((int*)arg), *(int *)tls_data);
    
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_args[3] = {1, 2, 3};
    
    // 加上cleanup_thread_data清理函数，表示每次结束一个线程就调用cleanup_thread_data清理函数。
    pthread_key_create(&thread_key, cleanup_thread_data);
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_key_delete(thread_key);
    return 0;
}
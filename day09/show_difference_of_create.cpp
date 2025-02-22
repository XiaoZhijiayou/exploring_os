#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

// Timing structure
typedef struct {
    struct timeval start;
    struct timeval end;
} timing_t;

// Function to measure process creation time
void measure_process_creation() {
    timing_t timing;
    gettimeofday(&timing.start, NULL);
    
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        exit(0);
    } else {
        // Parent process
        wait(NULL);
    }
    
    gettimeofday(&timing.end, NULL);
    
    long microseconds = (timing.end.tv_sec - timing.start.tv_sec) * 1000000 +
                       (timing.end.tv_usec - timing.start.tv_usec);
    printf("Process creation time: %ld microseconds\n", microseconds);
}

// Function for thread creation measurement
void* thread_function(void* arg) {
    return NULL;
}

void measure_thread_creation() {
    timing_t timing;
    pthread_t thread;
    
    gettimeofday(&timing.start, NULL);
    
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);
    
    gettimeofday(&timing.end, NULL);
    
    long microseconds = (timing.end.tv_sec - timing.start.tv_sec) * 1000000 +
                       (timing.end.tv_usec - timing.start.tv_usec);
    printf("Thread creation time: %ld microseconds\n", microseconds);
}

int main() {
    measure_process_creation();
    measure_thread_creation();
    return 0;
}
# 线程与进程之间的区别

- 1. 内存空间进程中的内存空间是完全独立和隔离的。每个进程都有自己的地址空间，包括代码、数据和堆段。例如，如果进程 A 在地址 0x1000 处有一个变量“x”，则它与进程 B 在同一地址处的变量“x”完全不同。
- 2. 资源所有权进程独立拥有和控制其所有资源。当进程创建文件句柄时，如果没有显式共享机制，其他进程无法直接访问该句柄。但是，线程在同一进程中共享资源，这使得资源共享更加简单。
- 3. 上下文切换开销进程上下文切换需要保存和加载整个内存映射、缓存内容和 CPU 寄存器。线程上下文切换只需要保存和恢复 CPU 寄存器和堆栈指针，使其明显更轻。
- 4. 创建时间创建新进程涉及复制整个父进程的内存空间和资源。线程创建只需要分配新的堆栈和特定于线程的数据结构。

### CPU利用率
- 1. 进程调度开销由于内存管理单元 （MMU） 更新和 TLB 刷新，进程需要更多的 CPU 时间进行上下文切换。
    - 1. 内存访问模式线程共享相同的地址空间，从而提高缓存利用率.


### 通信机制
- 1. 共享内存进程可以共享内存区域以加快通信速度

####  进程中共享内存的创建方式，和如何使用的方法
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#define SHM_NAME "/my_shm"
#define SHM_SIZE 1024

void demonstrate_shared_memory() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    
    char* shm_ptr = (char*)mmap(NULL, SHM_SIZE,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED, shm_fd, 0);
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        sleep(1);  // Ensure parent writes first
        printf("Child read: %s\n", (char*)shm_ptr);
        exit(0);
    } else {
        // Parent process
        sprintf(shm_ptr, "Hello from shared memory!");
        wait(NULL);
        
        munmap(shm_ptr, SHM_SIZE);
        shm_unlink(SHM_NAME);
    }
}

int main() {
    demonstrate_shared_memory();
    return 0;
}
```

### 线程的通信 : 直接利用全局变量进行通信过程

```cpp
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int shared_data = 0;
int data_ready = 0;

void* producer(void* arg) {
    pthread_mutex_lock(&mutex);
    shared_data = 42;
    data_ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!data_ready) {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Received: %d\n", shared_data);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}
```
工艺资源
每个进程都维护自己的：

    文件描述符
    内存映射
    信号处理程序
    进程 ID
    用户和组 ID
线程资源
线程共享：

    地址空间
    文件描述符
    信号处理程序
    当前工作目录 但有自己的：
    叠
    线程 ID
    信号掩码
    errno 变量

### 何时使用进程：隔离要求当您需要在组件之间进行强隔离时，流程是理想的选择。例如，Web 浏览器对每个选项卡使用单独的进程，以防止一个选项卡中的崩溃影响其他选项卡。 安全问题在处理敏感数据时，进程通过内存隔离提供更好的安全性。

### 何时使用线程：1. 共享资源访问当多个执行单元需要频繁共享资源时，线程会更好 2.实时通信线程对于需要频繁通信的方案非常有效

- 看到9.实际演示








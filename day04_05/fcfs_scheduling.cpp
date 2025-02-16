#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void fcfs_scheduling(Process processes[], int n) {
    // 初始化总等待时间和总周转时间为 0
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // 第一个进程的等待时间为 0
    processes[0].waiting_time = 0;
    // 第一个进程的周转时间等于其执行时间
    processes[0].turnaround_time = processes[0].burst_time;

    // 从第二个进程开始计算每个进程的等待时间和周转时间
    for (int i = 1; i < n; i++) {
        // 当前进程的等待时间等于前一个进程的等待时间加上前一个进程的执行时间
        processes[i].waiting_time = 
            processes[i-1].waiting_time + processes[i-1].burst_time;
        
        // 当前进程的周转时间等于其等待时间加上执行时间
        processes[i].turnaround_time = 
            processes[i].waiting_time + processes[i].burst_time;
    }

    // 输出表头
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    
    // 遍历所有进程，累加总等待时间和总周转时间，并输出每个进程的信息
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t%d\t%d\t%d\t%d\n", 
               processes[i].process_id, 
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    // 输出平均等待时间
    printf("Average Waiting Time: %.2f\n", 
           (float)total_waiting_time / n);
    // 输出平均周转时间
    printf("Average Turnaround Time: %.2f\n", 
           (float)total_turnaround_time / n);
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 0, 10},
        {2, 1, 5},
        {3, 3, 8}
    };

    fcfs_scheduling(processes, 3);
    return 0;
}
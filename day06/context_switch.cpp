#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>

#define STACK_SIZE 8192

typedef struct {
    ucontext_t context;
    int id;
} Process;

void function1(void) {
    printf("Process 1 executing\n");
}

void function2(void) {
    printf("Process 2 executing\n");
}

void context_switch(Process* curr_process, Process* next_process) {
    swapcontext(&curr_process->context, &next_process->context);
}

int main() {
    Process p1, p2;
    char stack1[STACK_SIZE], stack2[STACK_SIZE];

    // Initialize process 1
    getcontext(&p1.context);
    p1.context.uc_stack.ss_sp = stack1;
    p1.context.uc_stack.ss_size = STACK_SIZE;
    p1.context.uc_link = NULL;
    p1.id = 1;
    makecontext(&p1.context, function1, 0);

    // Initialize process 2
    getcontext(&p2.context);
    p2.context.uc_stack.ss_sp = stack2;
    p2.context.uc_stack.ss_size = STACK_SIZE;
    p2.context.uc_link = NULL;
    p2.id = 2;
    makecontext(&p2.context, function2, 0);

    // Perform context switches
    printf("Starting context switching demonstration\n");
    context_switch(&p2, &p1);
    sleep(22000);
    context_switch(&p1, &p2);

    return 0;
}
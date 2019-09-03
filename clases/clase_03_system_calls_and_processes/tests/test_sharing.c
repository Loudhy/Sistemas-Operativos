#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void printInfo(pid_t pid, pid_t ppid, int *value, int* *pointer, char* message);

int main(void) {
    int value = 0;
    int *pointer = &value;
    pid_t childpid;

    printInfo(getpid(), getppid(), &value, &pointer, "[PARENT]");    
    childpid = fork();

    if (childpid == 0) value = 1;
    else waitpid(childpid, NULL, -1);


    if (childpid == 0)  printInfo(getpid(), getppid(), &value, &pointer, "[CHILD]");
    else                printInfo(getpid(), getppid(), &value, &pointer, "[PARENT]");

    exit(0);
}

void printInfo(pid_t pid, pid_t ppid, int *value, int* *pointer, char* message) {
    printf("================================================\n");
    printf("%s\n", message);
    printf("pid = %ld, ppid = %ld\n", (long)pid, (long)ppid);
    printf("value = %d, direction = %p\n", (*value), &(*value));
    printf("pointer = %p, direction = %p, value = %d\n", (*pointer), &(*pointer), *(*pointer));
    fflush(stdout);
}
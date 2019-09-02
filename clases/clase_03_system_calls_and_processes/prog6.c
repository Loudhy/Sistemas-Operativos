#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

    pid_t pid;

    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    fflush(stdout);

    if ((pid=fork()) == -1) {
        perror("fork failed");
        exit(1);
    }

    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    printf("that's all\n");
    exit(0);
}
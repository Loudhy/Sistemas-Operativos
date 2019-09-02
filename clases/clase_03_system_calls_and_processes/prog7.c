#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void) {
    pid_t pid, ppid;

    printf("pid = %d, ppid = %d [FATHER]\n", getpid(), getppid());
    fflush(stdout);

    if ((pid=fork()) == -1) {
        perror("fork failed");
        exit(1);
    }

    // child's dream
    if (!pid) sleep(1);

    printf("pid = %d, ppid = %d\n", getpid(), (ppid=getppid()));
    if (ppid == 1) printf("I have a new father - init\n");
    
    printf("that's all\n");
    exit(0);
}
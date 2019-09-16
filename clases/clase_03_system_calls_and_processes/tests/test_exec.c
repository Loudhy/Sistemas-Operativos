#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {

    char pidstr[100];
    sprintf(pidstr, "pstree -p %d", (int)getpid());    

    pid_t pid = fork();

    if (pid == 0) {
        if (fork() == 0) {
            printf("(execl)PID=%d, PPID=%d\n", (int)getpid(), (int)getppid());
            execlp("ps", "-p", NULL);
        }
        else {
            printf("(system)PID=%d, PPID=%d\n", (int)getpid(), (int)getppid());
            system(pidstr);
        }
    }
    else {
        wait(NULL);
    }

    return 0;
}
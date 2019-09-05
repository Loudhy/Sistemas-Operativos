#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 3

int main(void) {
    int i;

    int nchilds = 0;
    char command[100];
    pid_t pid, grand_pa;

    grand_pa = getpid();

    for (i=1; i<N; i++) {
    
        if (fork()) nchilds += 1;
        else nchilds = 0;

        if (fork()) nchilds += 1;
        else nchilds = 0;
    }

    // leaf children, go to sleep enough to wait for the rest leaf children
    if (nchilds == 0) sleep(2);

    // parents waiting for all their children
    for (i=1; i<=nchilds; ++i) wait(NULL);


    sprintf(command, "pstree -p %ld", grand_pa);
    system(command);

    printf("PID[%3.3d]\n", getpid());
    exit(0);
}
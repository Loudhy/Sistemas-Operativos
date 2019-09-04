/* isengfork.c (c) 2007-2009 Rahmat M. Samik-Ibrahim, GPL - Like */
/* ************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int ii = 0;

    if (fork() == 0) ii++;
    waitpid(-1, NULL, 0);

    if (fork() == 0) ii++;
    waitpid(-1, NULL, 0);

    if (fork() == 0) ii++;
    waitpid(-1, NULL, 0);

    printf("Result = %3.3d [PID=%5.5d, PPID=%5.5d]\n", ii, getpid(), getppid());
    return 0;
}
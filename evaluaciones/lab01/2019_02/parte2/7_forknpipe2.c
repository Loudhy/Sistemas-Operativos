/* forknpipe2.c 2007-2009 Rahmat M. Samik-Ibrahim, GPL-like */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 64

int main(void) {
    char buffer1[BUFSIZE], buffer2[BUFSIZE];
    int p_this, p_prev, p_no1, p_no2;
    int fd_pipe[4][2], ii, jj;

    pid_t mypid;

    memset(buffer1, 0, BUFSIZE);
    memset(buffer2, 0, BUFSIZE);
    
    // four pipes in the matrix fd_pipe
    for (ii=0; ii<4; ii++) pipe(fd_pipe[ii]);

    // 
    ii = (fork() != 0) ? 0 : 2;
    jj = (fork() != 0) ? 0 : 1;

    // close in pipe side of THIS
    p_this = ii + jj;
    close(fd_pipe[p_this][0]);

    // close out pipe side of PREV
    p_prev = (p_this + 3) % 4;
    close(fd_pipe[p_prev][1]);

    // 4 pipes in a process, close 1 no used
    p_no1 = (p_this + 1) % 4;
    close(fd_pipe[p_no1][0]);
    close(fd_pipe[p_no1][1]);

    // 3 pipes in a process, close 1 no used
    p_no2 = (p_this + 2) % 4;
    close(fd_pipe[p_no2][0]);
    close(fd_pipe[p_no2][1]);

    mypid = getpid();
    sprintf(buffer1, " A message from PID[%d]\n", (int)mypid);

    write(fd_pipe[p_this][1], buffer1, BUFSIZE-1);
    close(fd_pipe[p_this][1]);

    while (read(fd_pipe[p_prev][0], buffer2, BUFSIZE-1) != 0) {
        waitpid(-1, NULL, 0);
        printf("PID[%d] IS WAITING:\n%s\n", (int)mypid, buffer2);
    }

    close(fd_pipe[p_prev][0]);
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOREAD  0
#define TOWRITE 1
#define P1      0 // PIPELINE 1 =  PS    ->   SORT
#define P2      1 // PIPELINE 2 =  SORT  ->   LESS

int main(int argc, char const *argv[]) {
    pid_t child;
    int fds[2][2], error;    

    // parent waits childs dead
    if ((child=fork())!=0) waitpid(child, NULL, 0);    
    
    else {
        char commands[3][20] = {"/usr/bin/less", "/usr/bin/sort", "/bin/ps"};
        int i, nprocs = 3;
        int fd[2];

        for (i=0; i<(nprocs-1); ++i) {
            pipe(fd);

            // CHILD
            if (fork() == 0) {
                dup2(fd[TOWRITE], STDOUT_FILENO);
                close(fd[TOWRITE]);
                close(fd[TOREAD]);
            }
            // PARENT
            else {
                dup2(fd[TOREAD], STDIN_FILENO);
                close(fd[TOREAD]);
                close(fd[TOWRITE]);
                break;
            }
        }

        error = execl(commands[i], commands[i], NULL);
        fprintf(stderr, "[ERROR]: cannot run execl in process %s (error=%d, errno=%d)\n", commands[i], error, errno);
        exit(errno);
    }

    return 0;
}


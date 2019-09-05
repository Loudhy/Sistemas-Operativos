#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOREAD  0
#define TOWRITE 1
#define P1      0 // PIPELINE 1 =  PS    ->   SORT
#define P2      1 // PIPELINE 2 =  SORT  ->   LESS

int main(int argc, char const *argv[]) {
    pid_t child;
    int fds[2][2];    

    // parent waits childs dead
    if ((child=fork())!=0) waitpid(child, NULL, 0);    
    
    else {
        pipe(fds[0]);

        // ps
        if (fork() == 0) {
            dup2(fds[P1][TOWRITE], STDOUT_FILENO);
            close(fds[P1][TOWRITE]);
            close(fds[P1][TOREAD]);

            execv("ps", NULL);
        }

        // sort process will inherit stdin from pipe 1
        dup2(fds[P1][TOREAD], STDIN_FILENO);
        close(fds[P1][TOREAD]);
        close(fds[P1][TOWRITE]);

        pipe(fds[P2]);

        // sort
        if (fork() == 0) {
            dup2(fds[P2][TOWRITE], STDOUT_FILENO);
            close(fds[P2][TOWRITE]);
            close(fds[P2][TOREAD]);

            execv("sort", NULL);
        }

        // less process will adopt stdin from pipe 2
        dup2(fds[P2][TOREAD], STDIN_FILENO);
        close(fds[P2][TOREAD]);
        close(fds[P2][TOWRITE]);

        // less
        execv("less", NULL);
    }

    return 0;
}


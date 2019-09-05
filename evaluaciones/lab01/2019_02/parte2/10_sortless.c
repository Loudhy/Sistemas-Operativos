#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
        pipe(fds[0]);

        // ps
        if (fork() == 0) {
            dup2(fds[P1][TOWRITE], STDOUT_FILENO);
            close(fds[P1][TOWRITE]);
            close(fds[P1][TOREAD]);

            error = execl("/bin/ps", "/bin/ps", NULL);
            fprintf(stderr, "[ERROR]: cannot execute execl() in ps process (error=%d)\n", error);
            exit(error);
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

            error = execl("/bin/sort", "/usr/bin/sort", NULL);
            fprintf(stderr, "[ERROR]: cannot execute execl() in sort process (error=%d)\n", error);
        }

        // less process will adopt stdin from pipe 2
        dup2(fds[P2][TOREAD], STDIN_FILENO);
        close(fds[P2][TOREAD]);
        close(fds[P2][TOWRITE]);

        // less
        error = execl("/usr/bin/less", "/bin/less", NULL);
        fprintf(stderr, "[ERROR]: cannot execute execl() in less process (error=%d)\n", error);
    }

    return 0;
}


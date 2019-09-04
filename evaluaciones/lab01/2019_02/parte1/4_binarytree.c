#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "insert a number for the tree deep\n");
        exit(1);
    }

    int deep, i, procn;
    
    deep = atoi(argv[1]);
    procn = 1;

    pid_t pid_left, pid_right, pid_parent;
    fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
        
    for (i=1; i<=deep; ++i) {
        pid_parent = getpid();
        if (i == deep) break;

        // left code
        if ((pid_left=fork()) == 0) {
            procn = procn * 2;
            fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
            waitpid(pid_left, NULL, 0);
        }

        // right code
        if ((pid_parent==getpid()) && (pid_right=fork()) == 0) {
            procn = procn * 2 + 1;
            fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
            continue;
            // waitpid(pid_left, NULL, 0);
        }

        // parent code
        if (pid_parent == getpid()) {
            waitpid(pid_right, NULL, 0);
            break;
        }
    }

    return 0;
}


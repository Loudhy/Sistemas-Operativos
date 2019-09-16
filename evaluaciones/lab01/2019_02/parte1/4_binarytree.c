#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
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

    pid_t pid_left, pid_right, pid_parent, pid_grandpa;
    pid_grandpa = getpid();
    fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
        
    for (i=1; i<=deep; ++i) {
        pid_parent = getpid();
        if (i == (deep+1)) break;

        // left code
        if ((pid_left=fork()) == 0) {
            procn = procn * 2;
            sleep(procn);
            fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
            sleep((int)pow(2, deep)-1 - procn);
        }

        // right code
        if ((pid_parent==getpid()) && (pid_right=fork()) == 0) {
            procn = procn * 2 + 1;
            sleep(procn);
            fprintf(stderr, "Soy el proceso %d [PID=%ld -- PPID=%ld]\n", procn, (long)getpid(), (long)getppid());
            sleep((int)pow(2, deep)-1 - procn);
        }

        // parent code
        if (pid_parent == getpid() && pid_parent != pid_grandpa) {
            waitpid(pid_left, NULL, 0);
            waitpid(pid_right, NULL, 0);
            break;
        }
    }

    // leaf children running forever
    if (i > deep) for(;;);

    // grand parent takes the picture
    if (pid_grandpa == getpid()) {
        sleep((int)pow(2, deep));
        char command[200];
        sprintf(command, "pstree -p %d", pid_grandpa);
        system(command);
    }

    return 0;
}


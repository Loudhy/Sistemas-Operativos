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
    pid_t parent_pid, left_child, right_child;

    deep = atoi(argv[1]);
    procn = 1;

    for (i=1; i<=deep; ++i) {
        parent_pid = getpid();
        fprintf(stderr, "Soy el proceso %d [PID=%5.5ld]\n", procn, (long)getpid());
        if (i == deep) break;
        
        // left side
        if ((left_child = fork()) == 0) {
            procn = procn * 2;
            waitpid(right_child, NULL, 0);
        }

        // right side, just parent can create the right child
        if ((parent_pid==getpid()) && ((right_child=fork())==0)) {
            procn = procn * 2 + 1;
            waitpid(left_child, NULL, 0);
        }

        // parent code
        if (parent_pid == getpid()) {
            waitpid(left_child, NULL, 0);
            waitpid(right_child, NULL, 0);
            break;
        }
    }    

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1

void bifurcate(int deep, int procn);

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "insert a number for the tree deep\n");
        exit(1);
    }

    int deep = atoi(argv[1]);
    bifurcate(deep, 1);

    while(TRUE) {
        
    }

    return 0;
}

void bifurcate(int deep, int procn) {
    
    fprintf(stderr, "Soy el proceso %d [PID=%5.5d]\n", procn, (int)getpid());
    if (deep == 1) return;

    pid_t parent_pid=1, child_left=1, child_right=1;
    parent_pid = getpid();

    // left child code
    if ((child_left=fork()) == 0) {
        bifurcate(deep-1, procn*2);
        exit(0);    
    }
    waitpid(-1, NULL, 0);

    // right child code
    if ((child_right=fork()) == 0) {
        bifurcate(deep-1, procn*2+1);
        exit(0);
    }
    waitpid(-1, NULL, 0);
}
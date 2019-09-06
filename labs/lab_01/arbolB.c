#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define TRUE 1

void createBranch(int);

int main(int argc, char const *argv[]) {
    
    if (argc <= 1) {
        fprintf(stderr, "Necesita ingresar un número\n");
        exit(1);
    }

    // n representará el derecho a crear un número n de hijos a un proceso
    int n = atoi(argv[1]);
    int i, nchilds;
    pid_t pid, pid_grandparent;

    pid_grandparent = getpid();


    for (i=1; i<=n; ++i) {
        // child will have a branch with nchilds
        if (fork()==0) {
            nchilds = ( (i==1||i==n) ? n-2 : n-3 );
            createBranch(nchilds);
        }
    }

    
    char command[200];
    sprintf(command, "pstree -p %ld\n", (long)pid_grandparent);
    sleep(3);
    system(command);
    
    return 0;
}

void createBranch(int nchilds) {
    // if nchilds == 0, it's a leaf child, needs to sleep
    if (nchilds == 0) {
        sleep(4);
        return;
    }

    if (fork() == 0) createBranch(nchilds-1);
    else wait(NULL);

    exit(0);
}
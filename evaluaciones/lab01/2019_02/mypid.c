#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main(void) {
    pid_t child;
    int status;

    if ((child = fork())) {
        fprintf(stderr, "Fork() devolvió %d. Por tanto, soy el padre con ID = %d\n", child, getpid());
        waitpid(child, &status, 0);
    }
    else {
        fprintf(stderr, "Fork() devolvió %d. Por tanto, soy el hijo con ID = %d\n", child, getpid());
        system("pstree > mypid_procesos.txt");
    }

    return 0;
}
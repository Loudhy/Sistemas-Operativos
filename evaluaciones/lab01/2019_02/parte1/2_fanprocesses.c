#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
* Este programa crea un abanico de procesos. Es decir, el padre
* crea tres hijo.
* Ejm 2.6 del libro UNIX Programación Práctica  - Kay Robbins
*                                               - Steve Robbins
* Modificado por Alejandro Bello Ruiz - Informática PUCP
*
*/

int main(void) {

    int i, status;
    pid_t child, pid_padre;

    pid_padre = getpid();

    for (i=1; i<4; ++i) {
        // child code
        if ((child=fork()) <= 0) {
            sleep(5);
            break;
        }
        // parent code
        else fprintf(stderr, "Este es el ciclo Nro %d y se está creando el proceso %d\n", i, child);
    }
        
    // take picture & wait for children
    if (pid_padre == getpid()) {
        char command[100];
        sprintf(command, "pstree -p %ld > fanprocesses.txt", (long)pid_padre);
        system(command);

        for (i=1; i<4; ++i) wait(&status);
    }

    fprintf(stderr, "Este es el proceso %d con padre %d\n", getpid(), getppid());
    return 0;
}
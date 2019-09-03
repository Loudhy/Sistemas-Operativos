#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
* Este programa crea una cadena de procesos. Es decir, el padre
* crea un hijo, este a su vez crea otro y así en forma sucesiva
* Ejm 2.5 del libro UNIX Programación Práctica  - Kay Robbins
*                                               - Steve Robbins
* Modificado por Alejandro Bello Ruiz - Informática PUCP
*
*/

int main(void) {
    int i, status;
    pid_t child; // pid_t es un tipo definido en types.h
    pid_t first_ppid = getpid();

    for (i=1; i<4; ++i) if (child=fork()) break;

    fprintf(stderr, "Esta es la vuelva Nro %d\n", i);
    fprintf(stderr, "Recibí de fork el valor de %d\n", child);
    fprintf(stderr, "Soy el proceso %d con padre %d\n", getpid(), getppid());

    wait(&status);

    // si es el último hijo
    if (child == 0) {
        char command[1000];
        sprintf(command, "pstree -p %ld > chainprocesses.txt", (long)first_ppid);
        system(command);
    }

    return 0;    
}
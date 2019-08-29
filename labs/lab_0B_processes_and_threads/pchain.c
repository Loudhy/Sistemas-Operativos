#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


/* 
* Este programa crea procesos hijos en forma vertical. Es decir,
* el padre crea un hijo, este a su vez crea otro y así de forma
* sucesiva.
* Ejm 2.5 del libro UNIX Programación Práctica - Kay Robbins
*                                              Steve Robbins
* Modificado por Alejandro Bello Ruiz - Informática PUCP
*/


int main(void) {
    int i, status;
    pid_t child, grand_pa;

    grand_pa = getpid();

    for (i=1; i<4; ++i) if (child=fork()) break;

    fprintf(stderr, "Esta es la vuelva Nro %d con dirección: %p\n", i, &i);
    fprintf(stderr, "Recibí de fork el valor de %d\n", child);
    fprintf(stderr, "Soy el proceso %d con padre %d\n\n", getpid(), getppid());

    wait(&status);
    if (grand_pa == getpid()) printf("status: %d --- &status: %p\n", status, &status);

    return 0;
}

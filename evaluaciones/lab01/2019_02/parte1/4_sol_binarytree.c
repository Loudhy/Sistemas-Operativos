/* binarytree.c (c) 2010 Alejandro T. Bello Ruiz, GPL-like */
/* ******************************************************* */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

double final;
void crea_arbol(int);

int main(int argc, char const *argv[]) {
    int n;

    n = atoi(argv[1]);
    final = pow(2, (n-1));
    crea_arbol(1);

    return 0;
}

void crea_arbol (int x) {
    char cadena[60];

    sprintf(cadena, "Soy el proceso %d con pid %d y ppid %d\n", x, getpid(), getppid());
    write(1, cadena, strlen(cadena));

    if (x >= final) return;

    if (!fork()) { crea_arbol(2*x); exit(0); }
    if (!fork()) { crea_arbol(2*x+1); exit(0); }

    wait(NULL);
    wait(NULL);
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define TRUE 1

int main(int argc, char const *argv[]) {
    
    if (argc <= 1) {
        fprintf(stderr, "Necesita ingresar un número\n");
        exit(1);
    }

    // n representará el derecho a crear un número n de hijos a un proceso
    int n = atoi(argv[1]);
    int i, e;
    pid_t pid, pid_grandparent;

    pid_grandparent = getpid();

    while (TRUE) {
        // no puede procrear más hijos, rompe el bucle
        if (n == 0) break;

        pid = getpid();

        // create n childs
        for (i=0; i<n; ++i) {
            if (fork() == 0) break;
            else continue;
        }

        // PADRE: espera por sus n hijos y termina el programa
        if (pid == getpid()) {
            // el abuelo de todos no esperará, este tomará la foto fuera del bucle
            if (pid_grandparent!=pid) {
                for(e=0; e<n; e++) wait(NULL);
                exit(0);
            }
            break;
        }
        // HIJOS: podrán crear n-1 hijos
        else {
            n = n-1;
        }
    }

    // todos los hijos hojas saldrán del bucle y dormirán para salir en la foto
    if (n==0) sleep(5);    
    // el abuelo tomará la foto
    else {
        char command[200];
        sprintf(command, "pstree -p %ld\n", (long)pid_grandparent);
        sleep(3);
        system(command);
        // luego, esperará a por sus hijos
        for(e=0; e<n; e++) wait(NULL);
    }

    return 0;
}

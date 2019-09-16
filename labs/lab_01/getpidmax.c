#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
El programa se detendrá cuando el fork devuelva -1, es decir, cuando ya
no pueda producir más procesos hijos, y se lo devolverá al proceso que lo
invocó. Es ahí cuando se imprime el número de forks efectuados
*/

int main() {

    pid_t pid;
    int i = 0;

    while (1) {
        i++;
        pid = fork();

        // no se puede crear mas procesos
        if (pid == -1) break;

        // el hijo creará a otro hasta ya no poder
        if (pid == 0) continue;
        
        // el padre esperará a su hijo
        else {
            if (i % 1000 == 0) fprintf(stderr, "CREATING...%d\n", i);
            waitpid(pid, NULL, 0);
            exit(0);
        }
    }

    fprintf(stderr, "número de forks ejecutados: %d\n", i);
    return 0;
}


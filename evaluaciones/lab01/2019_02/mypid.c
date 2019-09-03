#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    pid_t child;
    int status;

    if ((child = fork())) {
        fprintf(stderr, "Fork() devolvió %d. Por tanto, soy el padre con ID = %d\n", child, getpid());
        waitpid(child, &status, 0);
    }
    else {
        fprintf(stderr, "Fork() devolvió %d. Por tanto, soy el hijo con ID = %d\n", child, getpid());
        char command[1000];

        // system("pstree > mypid_procesos.txt");                                           // (a)
        // sprintf(command, "pstree %ld > mypid_procesos_v3.txt", (long)getppid());         // (c) => se imprime en directorio actual
        sprintf(command, "cd ~; pstree %ld > mypid_procesos_v3.txt", (long)getppid());      // (d) => se imprime en directorio home
        system(command);
    }

    return 0;
}

/*
* Respuestas:
* b)    sh es el intérprete del comando que se ha ejecutado "pstree"
*   
* c)    ia está, usa sprintf <3

* d)    agregar "cd ~;" donde ~ representa el home
*/
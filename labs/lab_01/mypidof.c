#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
    
    if (argc <= 1) {
        fprintf(stderr, "Coloca el nombre del programa para encontrar su pid\n");
        exit(1);
    }


    // command: ps -o pid,comm
    char command[200] = "ps -o pid,comm";
    char cadena[200];
    char pid[10];
    int len;
    FILE* fr;
    
    fr = popen(command, "r");

    while (fgets(cadena, sizeof(cadena), fr) != NULL) {
       len = strlen(cadena)-1;
    
        // looking for the process id
        if (strstr(cadena, argv[1]) != NULL) {
            memset(pid, 0, sizeof(pid));
            strncpy(pid, cadena, 5);
            fprintf(stderr, "[PID] %.*s: %.*s\n", (int)strlen(argv[1]), argv[1], (int)strlen(pid), pid);
            break;
        }
    }

    // compile: gcc mpidof.c -o mpidof.out
    // run: ./mpidof.out mpidof.out

    return 0;
}

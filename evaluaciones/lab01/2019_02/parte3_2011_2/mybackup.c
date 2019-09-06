#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define TOREAD  0
#define TOWRITE 1

void usage(const char*);

int main(int argc, char const *argv[]) {
    char command[200];
    int fd[2];
    FILE* file;

    if (argc != 2) usage(argv[0]);
    pipe(fd);

    // child code
    if (fork() == 0) {
        dup2(fd[TOWRITE], STDOUT_FILENO);
        close(fd[TOWRITE]);
        close(fd[TOREAD]);

        char argument[1000]; 
        sprintf(argument, "ls -l %s | grep ^- | cut -c 47-", argv[1]);;
        int error = execl("/bin/sh", "/bin/sh", "-c", argument, NULL);
        fprintf(stderr, "[ERROR]: cannot execute execv, error=%d\n", error);    
        exit(1);
    }
    // parent code
    else {
        file = fdopen(fd[TOREAD], "r");
        
        char buffer[1000];
        char res;
        wait(NULL);
        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fprintf(stdout, "Desea hacer backup del archivo '%.*s'?(y/n): ", (int)strlen(buffer), buffer);
            scanf(" %c",&res);

            if (res=='Y' || res=='y' || res=='S' || res=='s') {
                memset(command, 0, sizeof(command)-1);
                sprintf(command, "cd %s; cp '%.*s' '%.*s.bak'", argv[1], (int)strlen(buffer), buffer, (int)strlen(buffer), buffer);
                system(command);
            }
        }
    }

    return 0;
}

void usage(const char* program) {
    fprintf(stderr, "Uso: %s <ruta_del_directorio>\n", program);
    exit(1);
}
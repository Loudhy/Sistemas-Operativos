#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#define TOWRITE     1
#define TOREAD      0
#define BUFFERSIZE 20

void readPromptAndPipe(int);
void reverseAndPipe(int, int);
void uppercaseAndPipe(int, int);
void display(int);

int main(int argc, char const *argv[]) {
    
    char cadena[BUFFERSIZE];
    int fd[3][2], i;
    pid_t grand_pa, pid, child;
    grand_pa = getpid();
    // creando pipe para conectar con ultimo proceso
    pipe(fd[0]);
    
    for (i=1; i<3; ++i) {
        pid = getpid();
        pipe(fd[i]);
        
        if ((child=fork()) != 0) {
            // parent just writes in this new pipe
            close(fd[i][TOREAD]);
            break;
        }
        else {
            // child just reads in this new pipe
            close(fd[i][TOWRITE]);
        }
    }
    
    if (i == 1) readPromptAndPipe(fd[1][TOWRITE]);                      // first process
    if (i == 2) reverseAndPipe(fd[1][TOREAD], fd[2][TOWRITE]);          // second process
    if (i == 3) uppercaseAndPipe(fd[2][TOREAD], fd[0][TOWRITE]);        // third process

    if (grand_pa == getpid()) display(fd[0][TOREAD]);

    return 0;
}

void readPromptAndPipe(int fd_write) {
    char cadena[BUFFERSIZE];
    printf("Por favor, ingrese una cadena: ");
    
    scanf("%s", cadena);
    write(fd_write, cadena, sizeof(cadena)-1);
}

void reverseAndPipe(int fd_read, int fd_write) {
    char cadena[BUFFERSIZE];
    char reverse[BUFFERSIZE];
    read(fd_read, cadena, BUFFERSIZE);
    
    for (int i=0; i<strlen(cadena); i++) reverse[i] = cadena[strlen(cadena)-i-1];
    write(fd_write, reverse, sizeof(reverse)-1);
}

void uppercaseAndPipe(int fd_read, int fd_write) {
    char cadena[BUFFERSIZE];
    char upper[BUFFERSIZE];
    read(fd_read, cadena, BUFFERSIZE);

    for (int i=0; i<BUFFERSIZE; i++) upper[i] = toupper(cadena[i]);
    write(fd_write, upper, sizeof(upper)-1);
}

void display(int fd_read) {
    char cadena[BUFFERSIZE];
    read(fd_read, cadena, BUFFERSIZE);
    fprintf(stdout, "%s\n", cadena);
}
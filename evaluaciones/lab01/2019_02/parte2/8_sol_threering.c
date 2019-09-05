/* ring3/c (c) 2010 Alejandro T. Bello Ruiz, GPL-like */
/* ************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define N       3
#define PADRE   0
#define HIJO    1
#define NIETO   2

int pfd[N][2];

void cierra_descriptores_sin_uso(int);
void padre(void);
void hijo(void);
void nieto(void);

int main(void) {
    int n;

    for (n=0; n<N; n++) pipe(pfd[n]);
    
    if (!fork()) {
        if (!fork()) nieto();
        else hijo();
    }

    padre();
    return 0;
}

void padre(void) {
    char c, cadena[20];
    int i, n;

    cierra_descriptores_sin_uso(PADRE);
    printf("Ingrese una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);
    write(pfd[0][1], cadena, sizeof(cadena));

    wait(NULL);
    printf("La cadena original es: %s", cadena);
    
    read(pfd[2][0], &n, sizeof(n));
    printf("La cadena invertida es: ");

    for (i=0; i<n; i++) {
        read(pfd[2][0], &c, sizeof(c));
        printf("%c", c);
    }
}

void hijo(void) {
    char cadena[20]; int i, n;
    cierra_descriptores_sin_uso(HIJO);
    
    read(pfd[0][0], cadena, sizeof(cadena));
    n = strlen(cadena);
    write(pfd[1][1], &n, sizeof(n));

    for (i=n-2; i>=0; i--) write(pfd[1][1], &cadena[i], 1);
    write(pfd[1][1], &cadena[n-1], 1);
    wait(NULL);
    exit(0);
}

void nieto(void) {
    int i, k; char c;
    cierra_descriptores_sin_uso(NIETO);

    read(pfd[1][0], &k, sizeof(k));
    write(pfd[2][1], &k, sizeof(k));

    for (i=0; i<k; i++) {
        read(pfd[1][0], &c, sizeof(c));
        if (isalpha(c)) c=toupper(c);
        write(pfd[2][1], &c, sizeof(c)); 
    }

    exit(0);
}

void cierra_descriptores_sin_uso(int i) {
    int prev, ambos, sgte;

    prev  = (i-1)<0 ? N-1 : i-1;
    ambos = (i+1)%N;
    sgte  = i;

    close(pfd[prev ][1]);
    close(pfd[ambos][0]);
    close(pfd[ambos][1]);
    close(pfd[sgte ][0]);
}


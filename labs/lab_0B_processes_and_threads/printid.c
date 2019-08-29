#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    printf("ID del proceso: %d\n", getpid());
    printf("ID del padre del proceso: %d\n", getppid());
    printf("ID del usuario propietario: %d\n", getuid());
    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Qué se queda después de mí? */
int main(void) {
  printf("hello world from the process ID %d\n", getpid());
  printf("and bye. BTW, my father was the process ID %d\n", getppid());
  // exit(0);
}

// echo $?
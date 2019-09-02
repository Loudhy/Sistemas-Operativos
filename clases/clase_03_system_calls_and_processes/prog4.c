#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Soy el hijo del shell y el shell es mi hijo */

int main(void) {
  printf("hello world from the process ID %d\n", getpid());
  system("echo and bye.; ps -l");
  printf("and bye. BTW, my father was the process ID %d\n", getppid());
  exit(0);
}

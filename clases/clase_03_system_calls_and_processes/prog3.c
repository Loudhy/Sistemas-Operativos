#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  printf("hello world from the process ID %d\n", getpid());
  system("echo and bye.");
  printf("BTW, my father was the process ID %d\n", getppid());
  exit(0);
}

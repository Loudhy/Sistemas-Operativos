#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* no tuvo problemas mi hijo? */

int main(void) {
  int status;
  printf("hello world from the process ID %d\n", getpid());

  status = system("echo and bye.; ps -l");
  printf("status (of ps) = %d\n", status);

  status = system("echo and bye.; foo");
  printf("status (of foo) = %d\n", status);

  status = system("echo and bye.; foo; exit 44");
  printf("status = %d\n", status);

  status = system("echo and bye.; foo; exit 44");
  printf("status = %d\n", WEXITSTATUS(status));

  printf("BTW, my father was the process ID %d\n", getppid());
  exit(0);
}

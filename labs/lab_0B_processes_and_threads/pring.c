#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t childpid;     // indicates process should spawn another
    int error;          // return value from
    int fd[2];          // file descriptors returned by pipe
    int i;              // number of
    int nprocs;         // total number of processes in ring

    nprocs = atoi(argv[1]);

    // check command line for a valid number of processes
    if (argc!=2 || nprocs<=0) {
        fprintf(stderr, "Usage: %s nprocs\n", argv[0]);
        return 1;
    }

    /*
    * --- FILE DESCRIPTORS ---
    * 0 => STDIN_FILENO
    * 1 => STDOUT_FILENO
    * 2 => STDERR_FILENO
    */
    // connect std input to std output via a pipe
    if (pipe(fd) == -1) {
        perror("Failed to create starting pipe");
        return 1;
    }
    /*
    * --- FILE DESCRIPTORS ---
    * 0 => STDIN_FILENO
    * 1 => STDOUT_FILENO
    * 2 => STDERR_FILENO
    * 3 => fd[0]
    * 4 => fd[1]
    */
    if (dup2(fd[0], STDIN_FILENO)==-1 || dup2(fd[1], STDOUT_FILENO)==-1) {
        perror("Failed to connect pipe");
        return 1;
    }
    /*
    * --- FILE DESCRIPTORS ---
    * 0 => STDIN_FILENO (closed) => fd[0]
    * 1 => STDOUT_FILENO (closed) => fd[1]
    * 2 => STDERR_FILENO
    * 3 => fd[0]
    * 4 => fd[1]
    */
    if (close(fd[0])==-1 || close(fd[1])==-1) {
        perror("Failed to close extra descriptors");
        return 1;
    }
    /*
    * --- FILE DESCRIPTORS ---
    * 0 => fd[0]
    * 1 => fd[1]
    * 2 => STDERR_FILENO
    * 3 => fd[0] (closed)
    * 4 => fd[1] (closed)
    */

   // @DanielGuzmanT code
   pid_t first_p = getpid();

   // create the remaining processes
   for (i=1; i<nprocs; i++) {
        
        // creating the pipe
        if (pipe(fd)==-1) {
            fprintf(stderr, "[%ld]: failed to create pipe %d:  %s\n", (long)getpid(), i, strerror(errno));
            return 1;
        }

        // creating the child process
        if ((childpid=fork()) == -1) {
            fprintf(stderr, "[%ld]: failed to create child %d:  %s\n", (long)getpid(), i, strerror(errno));
            return 1;
        }

        // for child process, reassign stdin
        // for parent process, reassign stdout
        if (childpid == 0)  error = dup2(fd[0], STDIN_FILENO);
        else                error = dup2(fd[1], STDOUT_FILENO);
        
        if (error == -1) {
            fprintf(stderr, "[%ld]: failed to dup pipes for iteration %d:  %s\n", (long)getpid(), i, strerror(errno));
            return 1;
        }

        if (close(fd[0])==-1 || close(fd[1])==-1) {
            fprintf(stderr, "[%ld]: failed to close extra descriptions %d:  %s\n", (long)getpid(), i, strerror(errno));
            return 1;
        }

        // if parent, then break
        if (childpid) break;
    }

    fprintf(stderr, "This is process %d with ID %ld and parent id %ld\n", i, (long)getpid(), (long)getppid());
    
    // @DanielGuzmanT code below
    // transmit message, wait for child to end, and print message
    int num = 0;
    // first process to start messaging
    if (first_p == getpid()) {
        write(fd[1], &num, sizeof(num));
        waitpid(childpid, NULL, 0);
        read(fd[0], &num, sizeof(num));
        fprintf(stderr, "number: %d\n", num);
    }
    // other processes to continu messaging
    else {
        if (childpid != 0) waitpid(childpid, NULL, 0);
        read(fd[0], &num, sizeof(num));
        num += 1;
        write(fd[1], &num, sizeof(num));
    }

    return 0;
}

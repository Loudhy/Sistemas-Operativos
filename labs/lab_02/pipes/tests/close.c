#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* if all file descriptors for writing are closed, an EOF will be put in the pipe
*  and the data won't desapear until a read from file_descriptor
*/

int main() {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";

    char buffer[BUFSIZ + 1];
    pid_t fork_result;
    
    memset(buffer, '\0', sizeof(buffer));
    
    if (pipe(file_pipes) == 0) {
        
        fork_result = fork();

        if (fork_result == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        // child process
        if (fork_result == 0) {
            // sleep enough to wait for parent who will close writing pipe side
            close(file_pipes[1]); // close child write fd
            sleep(2);
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        }
    
        // parent process
        else {
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            close(file_pipes[1]); // close parent write fd
            printf("Wrote %d bytes\n", data_processed);
            wait(NULL);
        }
        
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
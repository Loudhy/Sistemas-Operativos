#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

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

        // passing file_descriptor by argument to child process (with new program)
        if (fork_result == 0) {
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe4.out", "pipe4.out", buffer, (char*)0);
            exit(EXIT_FAILURE);
        }

        // parent writes a message to child
        else {
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("[PID]: %d - wrote %d bytes\n", (int)getpid(), data_processed);
        }
        
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
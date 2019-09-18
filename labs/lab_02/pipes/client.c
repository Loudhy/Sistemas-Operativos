#include "client.h"
#include <ctype.h>

/*
Here’s the client, client.c . The first part of this program opens the server FIFO,
if it already exists, as a file. It then gets its own process ID, which forms some
of the data that will be sent to the server. The client FIFO is created, ready for
the next section.
*/

int main() {
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;

    int times_to_send;
    char client_fifo[256];

    // CONNECT TO SERVER FIFO
    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1) {
        fprintf(stderr, "Sorry, no server\n");
        exit(EXIT_FAILURE);
    }
    
    // NAME CLIENT FIFO
    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);

    // CREATE CLIENT FIFO    
    if (mkfifo(client_fifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can’t make %s\n", client_fifo);
        exit(EXIT_FAILURE);
    }

    /*
    For each of the five loops, the client data is sent to the server. Then the
    client FIFO is opened (read-only, blocking mode) and the data read back.
    Finally, the server FIFO is closed and the client FIFO removed from the file
    system.
    */

    for (times_to_send = 0; times_to_send < 1; times_to_send++) {
        // SAVE DATA TO SEND TO SERVER, THEN SEND IT
        sprintf(my_data.some_data, "Hello from PID=%d", my_data.client_pid);
        printf("[PID=%d] sent ~~ %s ~~, ", my_data.client_pid, my_data.some_data);
        write(server_fifo_fd, &my_data, sizeof(my_data));

        // OPEN CLIENT FIFO TO READ SERVER RESPONSE, THEN READ IF POSSIBLE
        client_fifo_fd = open(client_fifo, O_RDONLY);
        if (client_fifo_fd != -1) {
            if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0) {
                printf("received: ~~ %s ~~\n", my_data.some_data);
            }

            close(client_fifo_fd);
        }
    }

    close(server_fifo_fd);
    unlink(client_fifo);
    exit(EXIT_SUCCESS);
}
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define TRUE        1
#define QUEUE_SIZE  5

void acceptClient(int fd);
void deleteClient(int fd);
void attendClient(int fd);

int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;    
fd_set readfds, testfds;
    
int main() {
    
    int result;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr*) &server_address, server_len);
    listen(server_sockfd, QUEUE_SIZE);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while (TRUE) {
        int fd, nread;

        testfds = readfds;
        result = select(FD_SETSIZE, &testfds, NULL, NULL, (struct timeval*) NULL);
        if (result < 1) { perror("[ERROR] server cannot select"); exit(EXIT_FAILURE); }
    
        for (fd=0; fd<FD_SETSIZE; fd++) {
            // if not fd in set, avoid proccessing it
            if (!FD_ISSET(fd, &testfds)) continue;

            // SERVER MUST ACCEPT CLIENT
            if (fd == server_sockfd) acceptClient(fd);
            
            else {
                ioctl(fd, FIONREAD, &nread);
                
                // DELETE CLIENT WHO DOESNT WRITE
                if (nread == 0) deleteClient(fd);

                // ATTENDE PENDIENT CLIENT
                else attendClient(fd);
            }
        }
    }

    exit(EXIT_SUCCESS);
}


void acceptClient(int fd) {
    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);

    FD_SET(client_sockfd, &readfds);
    printf("[SERVER]: Adding client on fd=%d\n", client_sockfd);
}


void deleteClient(int fd) {
    close(fd);
    FD_CLR(fd, &readfds);
    printf("[SERVER]: Removinf client on fd=%d\n", fd);
}


void attendClient(int fd) {
    /* REQUEST AND RESPONSE */

    /* ******************** */
}
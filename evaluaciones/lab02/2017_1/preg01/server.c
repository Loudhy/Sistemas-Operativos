#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define TRUE        1
#define QUEUE_SIZE  5

void acceptClient(int fd);
void deleteClient(int fd);
void attendClient(int fd);
void divisorsOf(int number, int* divisors, int* count);

int server_sockfd, client_sockfd;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;    
fd_set readfds, testfds;
    
int main() {
    
    int result;
    struct timeval timeout;

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
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;

        printf("[SERVER-ANALISIS]: selecting\n");

        result = select(FD_SETSIZE, &testfds, NULL, NULL, (struct timeval*) &timeout);
        if (result == -1) { perror("[ERROR] server cannot select"); exit(EXIT_FAILURE); }

        printf("[SERVER-ANALISIS]: after => result %d\n", result);

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
    printf("[SERVER]: Removing client on fd=%d\n", fd);
}


void attendClient(int fd) {
    printf("[SERVER]: Attending client on fd=%d\n", fd);
    /* REQUEST AND RESPONSE */
    int number=0, divisors[100], count=0;
    char *message; 

    read(fd, &number, sizeof(number));
    divisorsOf(number, divisors, &count);
    
    // Prime number
    if (count == 0) {
        message = "es número primo\n";
        write(fd, message, strlen(message));
    }

    // Not prime number
    else {
        message = "no es número primo porque tiene los siguientes divisores:\n";
        write(fd, message, strlen(message));
        
        char aux[100];
        memset(aux, 0, sizeof(aux));
        
        for (int i=0; i<count; i++) sprintf(aux, "%s - %d", aux, divisors[i]);
        aux[strlen(aux)] = 0;
        write(fd, aux, strlen(aux));
    }

    write(fd, "END", 3);
    // deleteClient(fd);
    /* ******************** */
}

void divisorsOf(int number, int* divisors, int* count) {
    for (int i=2; i<=(number/2); i++)
        if (number%i == 0) {
            divisors[*count] = i;
            *count += 1;
        }
}

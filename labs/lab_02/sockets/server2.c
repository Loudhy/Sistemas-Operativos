/*
* Be aware the there is a deliberate error in the programas client2.c and server2.c
* that you will fix in client3.c and server3.c. Please, do not use the code from
* client2.c and server2.c in your own programs.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE    1

int main() {

    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    // create an unnamed socket for the server
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // name the socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr*) &server_address, server_len);

    // create a connection queue and wait for clients
    listen(server_sockfd, 5);
    while(TRUE) {
        char ch;
        printf("server waiting...\n");
        
        // accept a connection
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);

        // read and write to client on client_socketfd
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);   
        close(client_sockfd);
    }
 
    exit(0);
}
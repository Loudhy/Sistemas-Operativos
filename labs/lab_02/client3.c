/*
* Be aware the there is a deliberate error in the programas client2.c and server2.c
* that you will fix in client3.c and server3.c. Please, do not use the code from
* client2.c and server2.c in your own programs.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int sockfd, len, result;
    struct sockaddr_in address;
    char ch = 'A';

    // create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

    // connect your socket to your server's socket
    result = connect(sockfd, (struct sockaddr *) &address, len);
    if (result == -1) { perror("oops: client"); exit(1); }

    // you can now read and write via sockfd
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);

    printf("char from server = %c\n", ch);
    close(sockfd);

    exit(0);    
}
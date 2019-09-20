#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1

int main(int argc, char const *argv[]) {
    
    if (argc < 2) {
        printf("[CLIENT-ERROR]: needs to add a number\n");
        exit(EXIT_FAILURE );
    }

    int sockfd, len, result;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);

    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if (result == -1) { perror("[ERROR] client cannot connect"); exit(1); }

    /* SEND AND RECEIVE */
    int number = atoi(argv[1]);
    write(sockfd, &number, sizeof(number));
    
    char message[100];
    int nreads = 0;
    while (TRUE) {
        
        memset(message, 0, sizeof(message));
        
        nreads = read(sockfd, message, 100);
        printf("strlen=%ld", strlen(message));
        if (strncmp(message, "END", 3)==0) break;
        message[nreads] = 0;
        
        printf("[CLIENT]: from server => %s\n", message);
    }
    /* **************** */

    close(sockfd);
    exit(0);
}

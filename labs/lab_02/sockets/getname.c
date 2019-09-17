#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    char *host, **names, **addresses;
    struct hostent *hostinfo;

    // set the host to hte argument supplied with the getname call,
    // or by default to the user's machine
    if (argc == 1) {
        char myname[256];
        gethostname(myname, 255);
        host = myname;
    }
    else {
        host = argv[1];
    }

    // call gethostbyname and report an error
    // if no information is found
    hostinfo = gethostbyname(host);
    if (!hostinfo) {
        fprintf(stderr, "cannot get info for host: %s\n", host);
        exit(1);
    }

    // display the hostname and any aliases that it may have
    printf("Results for host %s:\n", host);
    printf("Name: %s\n", hostinfo->h_name);
    printf("Aliases:");

    names = hostinfo->h_aliases;
    while (*names) {
        printf(" %s", *names);
        names++;
    }

    // warn and exit if the host in question isn't an IP host
    if (hostinfo->h_addrtype != AF_INET) {
        fprintf(stderr, "not an IP host!\n");
        exit(1);
    }

    // otherwise, display the IP address(es)
    addresses = hostinfo->h_addr_list;
    while (*addresses) {
        printf(" %s", inet_ntoa(*(struct in_addr*)*addresses));
        addresses++;
    }

    printf("\n");
    exit(0);
}
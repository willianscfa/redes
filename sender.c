#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "9999" // the port to advertise
#define HOST "localhost" 

int main(){
    int status;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *res;  // will point to the results

    memset(&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // port is the second argument of getaddrinfo, NULL defaults to the host IP address
    if ((status = getaddrinfo(HOST, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // res now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need res anymore ....

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if(sockfd == -1){
        // error checking
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(sockfd));
        exit(1);        
    }

    // connect!
    

    if((status = connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1){
        fprintf(stderr, "connect error: %s\n", gai_strerror(status));
        exit(1);    
    }


    char *msg = "ESSA EH A MENSAGEM";
    int len, bytes_sent;

    len = strlen(msg);
    bytes_sent = send(sockfd, msg, len, 0);

    if(bytes_sent == -1){
        fprintf(stderr, "send error: %s\n", gai_strerror(status));
        exit(1);
    }

    freeaddrinfo(res); // free the linked-list

    return 0;
}
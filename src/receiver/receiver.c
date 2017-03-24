#include "receiver.h"

#define PORT "35000"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold

void recvfile(){
    int status;
    int sockfd;

    sockfd = newlistensocket(PORT);
    
    status = listen(sockfd, BACKLOG);

    if(status < 0){
        fprintf(stderr, "listen error: %s\n", strerror(sockfd));
    }

    // socket to a new connection, blocks until a connection to PORT is made
    int new_fd = newrecvsocket(sockfd);

    char msg[18];
    int msg_size = sizeof msg;

    status = recv(new_fd, &msg, msg_size, 0);

    if(status < 0){
        fprintf(stderr, "recv error: %s\n", strerror(status));
        exit(1);
    }

    printf ("mensagem de tamanho: %d\n", msg_size);
    printf("mensagem em char: %s\n", msg);

    for(int i = 0; i < msg_size; i++){
        printf("%x", msg[i]);
    }

    printf("\n");

    if(status == 0){
        printf("%s\n", "connection closed");
        exit(0);
    }
}
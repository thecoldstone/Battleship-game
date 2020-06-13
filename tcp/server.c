#include "tcp_utilities.h"
#include "game.h"

int main(){
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    User* user = init_game(1);
    GAME = 1;

    // create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd < 0)
        error("[ERROR] opening socket");

    // clear address structure
    bzero((char*) &serv_addr, sizeof(serv_addr));

    /* setup the host_addr structure for use in bind call */
    // server byte order
    serv_addr.sin_family = AF_INET;
    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(PORT);

    // This bind() call will bind the socket to the current IP address on port
    if((bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) != 0)
        error("[ERROR] on binding");

    // Here, we set the maximum size for the backlog queue to 5
    if((listen(sockfd, 5)) != 0) 
        error("[ERROR] on listening");

    clilen = sizeof(cli_addr);

    // Accept the data packet from client 
    if((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
        error("[ERROR] on accept");
    } else {
        printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    }

    while(GAME){
        board_print(user, 1, newsockfd);
        // send(newsockfd, "Hello, world!\n", 13, 0);
    
        bzero(BUFFER, 256);

        if((n = read(newsockfd, BUFFER, 255)) < 0) 
            error("[ERROR] reading from socket");
        else {
             // if msg contains "Exit" then server exit and chat ended. 
            if (strncmp("exit", BUFFER, 4) == 0) { 
                printf("Server Exit...\n"); 
                break; 
            } else {
                printf("Received message: %s\n", BUFFER);
            }
        }

    }

    /* Deallocation */
    boardDestroy(user->board);
    userDestroy(user);
    close(newsockfd);
    close(sockfd);
    return 0;
}
#include "tcp_utilities.h"
#include "game.h"

int main(){
    int sockfd, newsockfd, n;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    // create a socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("[ERROR] opening socket");

    // clear address structure
    bzero((char*) &serv_addr, sizeof(serv_addr));

    /* setup the host_addr structure for use in bind call */
    // server byte order
    serv_addr.sin_family = AF_INET;
    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // convert short integer value for port must be converted into network byte order
    serv_addr.sin_port = htons(PORT);    
        
    // This bind() call will bind the socket to the current IP address on port
    if((bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) != 0)
        error("[ERROR] on binding");

    // Here, we set the maximum size for the backlog queue to 5
    if((listen(sockfd, 5)) != 0) 
        error("[ERROR] on listening");

    clilen = sizeof(cli_addr);

    User* user = init_game(1);

    // Accept the data packet from client 
    if((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
        error("[ERROR] on accept");
    } else {
        printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    }

    GAME = 1;
    SHOOT = 1;
    RECEIVE = 0;

    while(GAME){

        while(SHOOT){
            
            // board_print(user, 1, newsockfd);
            bzero(BUFFER, 256);

            inputCoordinates(BUFFER);
            write(newsockfd, BUFFER, sizeof(BUFFER));

            if((n = read(newsockfd, BUFFER, 255)) < 0) 
                error("[ERROR] reading from socket");
            else { 
                printf("%s\n", BUFFER);
                if (strncmp("exit", BUFFER, 4) == 0) { 
                    printf("Server Exit...\n"); 
                    SHOOT = 0;
                    GAME = 0;
                } else if(strcmp(BUFFER, "WON") == 0) {
                    WON = 1;
                    SHOOT = 0;
                    GAME = 0;
                } else if(strcmp(BUFFER, "FAILED") == 0 || strcmp(BUFFER, "MISS") == 0){ 
                    SHOOT = 0;
                    RECEIVE = 1;
                }
            }

        }

        // while(RECEIVE && GAME) {

        //     get_board(newsockfd);
            
        //     board_print(user, 1, newsockfd);
        //     bzero(BUFFER, 256);

        //     if((n = read(newsockfd, BUFFER, 255)) < 0) 
        //         error("[ERROR] reading from socket");
        //     else { 
        //         if (strncmp("exit", BUFFER, 4) == 0) { 
        //             printf("Server Exit...\n"); 
        //             RECEIVE = 0;
        //             GAME = 0;
        //         } else if(strcmp(BUFFER, "WON") == 0) {
        //             WON = 1;
        //             SHOOT = 0;
        //             GAME = 0;
        //         } else if(strcmp(BUFFER, "FAILED") == 0 || strcmp(BUFFER, "MISS") == 0){ 
        //             SHOOT = 0;
        //             RECEIVE = 1;
        //         }
        //     }

        // }
    }

    /* Deallocation */
    boardDestroy(user->board);
    userDestroy(user);
    close(newsockfd);
    close(sockfd);
    return 0;
}
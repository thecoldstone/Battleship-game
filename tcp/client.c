#include "tcp_utilities.h"
#include "game.h"

int main(){
    int sockfd, n;
    struct sockaddr_in serv_addr;

    User* user = init_game(2);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("[ERROR] opening socket");

    bzero((char*) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serv_addr.sin_port = htons(PORT); 

    if((connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
        error("[ERROR] connection with the server failed...");
    } else {
        printf("[+]connected...");
    }

    GAME = 1;
    // SHOOT = 0;
    // RECEIVE = 1;

    while(GAME){
        
        bzero(BUFFER, 256);

        if((n = read(sockfd, BUFFER, 255)) < 0) {
            error("[ERROR] reading from socket");
        } else {
            if (strncmp("exit", BUFFER, 4) == 0) { 
                    printf("Server Exit...\n"); 
                    // GAME = 0;
            }
            printf("%s", BUFFER);
        }

        board_print(user, 1, sockfd);

        // while(SHOOT){
            
        //     board_print(user, 1, sockfd);
        //     bzero(BUFFER, 256);

        //     inputCoordinates(BUFFER);
        //     write(sockfd, BUFFER, sizeof(BUFFER));

        //     if((n = read(sockfd, BUFFER, 255)) < 0) 
        //         error("[ERROR] reading from socket");
        //     else { 
        //         if (strncmp("exit", BUFFER, 4) == 0) { 
        //             printf("Server Exit...\n"); 
        //             SHOOT = 0;
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

        // while(RECEIVE && GAME) {
            
        //     board_print(user, 1, sockfd);
        //     bzero(BUFFER, 256);

        //     if((n = read(sockfd, BUFFER, 255)) < 0) 
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
    close(sockfd);
    return 0;

}
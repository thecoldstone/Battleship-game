/**
 * @file game.c
 * @brief Game utilities
 * @author Nikita Zhukov
 * @date 26.05.20
 * 
*/

#include "game.h"

User* init_game(int id) {
    /* FOR RANDOM INSERTION */
    srand((unsigned int) time(NULL)); 

    BOARD_SIZE = 15;
    NUMBER_OF_SHIPS = 5;

    /*INITIALIZE THE GAME*/
    User* user = initUser(1, BOARD_SIZE, NUMBER_OF_SHIPS);
    user->id = id;
    /*INITIALIZE THE SHIPS*/
    initShips(user);

    return user;
}

void board_print(User* user, bool noShip, int fd) {
    
    char buffer[256];
    memset(buffer, 0, strlen(buffer));
    lseek(fd, 0, SEEK_SET);

    write(fd, "\t    ", 6);

    for(int i = 0; i < BOARD_SIZE; ++i) {
        if(i >= 10){
            sprintf(&buffer[strlen(buffer)], " %d ", i);
        } else{
            sprintf(&buffer[strlen(buffer)], " %d  ", i);
        }
    }

    write(fd, buffer, strlen(buffer));
    memset(buffer, 0,strlen(buffer));

    write(fd, "\n", 2);

    for(int i = 0; i < BOARD_SIZE; ++i) {
        
        if(i < 10){
            sprintf(&buffer[strlen(buffer)], "\t %i", i);
        } else {
            sprintf(&buffer[strlen(buffer)], "\t%i", i);
        }

        for(int j = 0; j < BOARD_SIZE; ++j) {
            sprintf(&buffer[strlen(buffer)], " | ");

            /***PRINT SHIP TYPE***/
            if(user->board[i][j].ship && noShip && user->board[i][j].state == NO_SHOOT) {
                // printf("%d", board[i][j].ship->size);

                switch(user->board[i][j].ship->type)
                {
                case MONOMINO:
                    sprintf(&buffer[strlen(buffer)], "M");
                    break;
                case DOMINO:
                    sprintf(&buffer[strlen(buffer)], "D");
                    break;
                case TROMINO:
                    sprintf(&buffer[strlen(buffer)], "I");  
                    break;  
                case T_TETROMINO:
                    sprintf(&buffer[strlen(buffer)], "T");
                    break;
                case L_TETROMINO:
                    sprintf(&buffer[strlen(buffer)], "L");
                    break;
                }

                continue;
            }
            /***PRINT BOARD STATES***/
            switch (user->board[i][j].state)
            {
            case HIT:
                sprintf(&buffer[strlen(buffer)], RED"X"RESET_COLOR);
                break;
            case MISS:
                sprintf(&buffer[strlen(buffer)], "*");
                break;    
            default: //NO_SHOOT
                sprintf(&buffer[strlen(buffer)], BLUE"~"RESET_COLOR);
                break;
            }

            write(fd, buffer, strlen(buffer));
            memset(buffer, 0, strlen(buffer));
        }

        sprintf(&buffer[strlen(buffer)], " |\n");
        write(fd, buffer, strlen(buffer));
        memset(buffer, 0, strlen(buffer));

    }

    write(fd, "\n\n", 3);
}

int get_board(int fd){

    char c;

    lseek(fd, 0, SEEK_SET);

    while(read(fd, &c, 1)) {
        write(STDOUT_FILENO, &c, 1);
    }

    fflush(0);

    return 1;

}

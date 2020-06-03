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

void board_print(Cell** board, bool noShip, int fd) {

    char *buffer = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(buffer == MAP_FAILED)
            perror("mmap");

    sprintf(&buffer[strlen(buffer)], "\t    ");

    for(int i = 0; i < BOARD_SIZE; ++i) {
        if(i >= 10){
            sprintf(&buffer[strlen(buffer)], " %d ", i);
        } else{
            sprintf(&buffer[strlen(buffer)], " %d  ", i);
        }
    }

    sprintf(&buffer[strlen(buffer)], "\n");

    for(int i = 0; i < BOARD_SIZE ;i++) {

        if(i < 10){
            sprintf(&buffer[strlen(buffer)], "\t %i", i);
        } else {
            sprintf(&buffer[strlen(buffer)],  "\t%i", i);
        }

        for(int j = 0; j < BOARD_SIZE; ++j) {
            sprintf(&buffer[strlen(buffer)], " | ");

            /***PRINT SHIP TYPE***/
            if(board[i][j].ship && noShip && board[i][j].state == NO_SHOOT) {
                // printf("%d", board[i][j].ship->size);

                switch(board[i][j].ship->type)
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
            switch (board[i][j].state)
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
        }
        sprintf(&buffer[strlen(buffer)], " |\n");
    }  

    sprintf(&buffer[strlen(buffer)], "\n");
    
    munmap(buffer, SIZE);

}

// void get_board(int fd, char* buffer) {

//     if(buffer == MAP_FAILED)
//             perror("mmap");

//     printf("%s\n", buffer);
//     munmap(buffer, SIZE);
    
// }
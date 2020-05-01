#include "io_handler.h"

int inputBoardSize(){
    
    int size;

    //1.Board size
    printf("Size of board: ");
    scanf("%d", &size);
    //1. [RULE]: The allowed game size should be between 20x20 to 40x40 (always squares).
    while(size < 0 || size > 40){
        printf("[FAILED] Enter the size of board again: ");
        scanf(" %d", &size);
    }  

    return size;

}

int inputShips(){

    int number;

    printf("Number of ships: ");
    scanf(" %d", &number);
    //[RULE]: (N * N)/(5*5) < NUMBER_OF_SHIPS, where N is size of a board
    while((BOARD_SIZE * BOARD_SIZE)/(5*5) < NUMBER_OF_SHIPS || NUMBER_OF_SHIPS < 0) {
        printf("[FAILED] Enter the number of ships again: ");
        scanf(" %d", &NUMBER_OF_SHIPS);
    }

    return number;
}

int inputMode(){

    char *c;

    /**MODE 1 = BORDER **/
    printf("Set gap between ships to one cell?[y/n]:");
    scanf(" %1s", c);
    while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0 && strcmp(c, "Y") != 0 && strcmp(c, "N") != 0){
        scanf(" %1s", c);
    }

    if(strcmp(c, "y") == 0){
        BORDER_ON = 1;
    }

    return 1;

}

void getStatus(User* user){
    
    int activeUser;

    if(user->id == 1){
        activeUser = 2;
    } else {
        activeUser = 1;
    }

    printf("\tACTIVE USER: %i\n\t-------------\n", activeUser);
    printf("\tYOU ARE ATTACKING THE USER: %i\n\t-------------\n", user->id);
    boardPrint(user->board, true);
    printf("\n\n\n\n\n");

}

/**
 * @file program.c 
 * @brief Implementation of API to run the program
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include"program.h"

void initShips(Cell** Board){

    /******INPUT******/
    // int i = 0;
    // while(i != NUMBER_OF_SHIPS) {
        
    //     tTypeShip type;
    //     printf("Choose the type of board to insert:");
    //     scanf("%d", type);

        
        
    // }

    int x, y; 
    bool inserted = false;

    tTypeShip type = 4;
    // printf("Choose the type of board to insert:");
    // scanf("%d", &type);

    while(!setShip(Board, type, 3, 3, 0)){
        printf("[FAILED] Choose the type of board to insert: ");
        scanf("%d", &type);
    }

    type = 1;
    while(!setShip(Board, type, 2, 1, 0)){
        printf("[FAILED] Choose the type of board to insert: ");
        scanf("%d", &type);
    }

    type = 0; 
    while(!setShip(Board, type, 0, 3, 0)){
        printf("[FAILED] Choose the type of board to insert: ");
        scanf("%d", &type);
    }

    // TODO [BAD] Need to be improved. Between ships should be at least one box 
    // type = 3; 
    // while(!setShip(Board, type, 6, 3, 0)){
    //     printf("[FAILED] Choose the type of board to insert: ");
    //     scanf("%d", &type);
    // }

}

void processStartInput(){
    
    //1.Board size
    printf("Enter the size of board: ");
    scanf("%d", &BOARD_SIZE);
    //1. [RULE]: The allowed game size should be between 20x20 to 40x40 (always squares).
    while(BOARD_SIZE < 20 || BOARD_SIZE > 40){
        printf("[FAILED] Enter the size of board again: ");
        scanf(" %d", &BOARD_SIZE);
    }

    //2.Number of ships(boats)
    printf("Enter the number of ships: ");
    scanf(" %d", &NUMBER_OF_SHIPS);
    //2.1 [RULE]: (N * N)/(5*5) < NUMBER_OF_SHIPS, where N is size of a board
    while((BOARD_SIZE * BOARD_SIZE)/(5*5) < NUMBER_OF_SHIPS || NUMBER_OF_SHIPS < 0) {
        printf("[FAILED] Enter the number of ships again: ");
        scanf(" %d", &NUMBER_OF_SHIPS);
    }

}

void initProgram(){

    /******INPUT******/
    // processStartInput();

    BOARD_SIZE = 10;

    /* Initialize Users */
    Cell** BoardUserOne = boardInit(BOARD_SIZE);
    // Cell** BoardUserTwo = boardInit(BOARD_SIZE);

    /* Set Ships */
    initShips(BoardUserOne);

    boardPrint(BoardUserOne);
    // boardPrint(BoardUserTwo);

    /* Deallocate everything at the end of game */
    //TODO Destroy for ships
    boardDestroy(BoardUserOne);
    // boardDestroy(BoardUserTwo);

}

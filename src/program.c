/**
 * @file program.c 
 * @brief Implementation of API to run the program
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include <time.h>
#include "program.h"
#include "battleship.h"

Cell** BoardUserOne;
Cell** BoardUserTwo;

bool USER_FIRST;
bool USER_SECOND;

int genRandomNumber(int lowest, int heighest){

    if(lowest == 0){
        return rand() % heighest;
    } else if(lowest > 0){
        return rand() % heighest + lowest;
    } else {
        return -1;
    }

}

void initShipsRandomly(Cell** board){
 
    int x, y, type, rotation;

    for(int i = 0; i < NUMBER_OF_SHIPS; i++){

        while(true){
            type = genRandomNumber(0, 5);
            x    = genRandomNumber(0, BOARD_SIZE);
            y    = genRandomNumber(0, BOARD_SIZE);
            rotation = genRandomNumber(0, 4);

            if(insertShip(board,type, x, y, rotation)) break;            
        }

    }

}

void initShipsManually(Cell** board){
    
    int i = 0;

    while(i != NUMBER_OF_SHIPS) {

        //boardPrint before inserting
        
        tTypeShip type;
        printf("Choose the type of board to insert [0-4]: ");
        while(!scanf("%d", &type));       

        int x, y, rotate;

        printf("Set coordinates [x, y]: ");
        scanf(" %d,%d", &x, &y);

        printf("Rotate [0-4] (0˚, 90˚, 180˚, 270˚, 360˚)): ");
        scanf(" %d", &rotate);

        while(!insertShip(board, type, x, y, rotate)){
            printf("[FAILED] You can not insert there [%d, %d]\n", x, y);
            printf("Set coordinates [x, y]: ");
            scanf(" %d,%d", &x, &y);

            printf("Rotate [0-4] (0˚, 90˚, 180˚, 270˚, 360˚)): ");
            scanf(" %d", &rotate);
            printf("\n");
        }

        if(NUMBER_OF_SHIPS - i - 1 != 0){
            printf("Ship remained to insert: %d\n", NUMBER_OF_SHIPS - i - 1);
        }
        
        i++;
    }
}

void initShips(Cell** board){

    /******INPUT******/
    bool isInitialized = false;
    int howToSetShips = 2;
    // printf("Choose how to insert ships\n[1] Manually\n[2] Randomly\n:");
    // scanf(" %1d", &howToSetShips);
    
    while(!isInitialized){
        
        switch(howToSetShips){
        
        case 1:
            initShipsManually(board);
            isInitialized = true;
            break;
        case 2:
            initShipsRandomly(board);
            isInitialized = true;
            break;
        default:
            printf(RED"[FAIL]"RESET_COLOR"This option does not exist. Try again: ");
            scanf(" %1d", &howToSetShips);

        }      
    }

    // printf("Your board is done!\n\n");

}

void processStartInput(){
    
    //1.Board size
    printf("Size of board: ");
    scanf("%d", &BOARD_SIZE);
    //1. [RULE]: The allowed game size should be between 20x20 to 40x40 (always squares).
    while(BOARD_SIZE < 0 || BOARD_SIZE > 40){
        printf("[FAILED] Enter the size of board again: ");
        scanf(" %d", &BOARD_SIZE);
    }

    //2.Number of ships(boats)
    printf("Number of ships: ");
    scanf(" %d", &NUMBER_OF_SHIPS);
    //2.1 [RULE]: (N * N)/(5*5) < NUMBER_OF_SHIPS, where N is size of a board
    // while((BOARD_SIZE * BOARD_SIZE)/(5*5) < NUMBER_OF_SHIPS || NUMBER_OF_SHIPS < 0) {
    //     printf("[FAILED] Enter the number of ships again: ");
    //     scanf(" %d", &NUMBER_OF_SHIPS);
    // }


    /***********OPTIONS***********/
    
    #ifdef OPTIONS

    /**BORDER**/
    //Set gap(border) bewteen ship to one cell
    char *c;
    printf("Set gap between ships to one cell?[y/n]:");
    scanf(" %1s", c);
    while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0 && strcmp(c, "Y") != 0 && strcmp(c, "N") != 0){
        scanf(" %1s", c);
    }

    if(strcmp(c, "y") == 0){
        BORDER_ON = 1;
    }

    #endif

}

void INPUT(){

    // processStartInput();

    // TEST
    BOARD_SIZE = 10;
    NUMBER_OF_SHIPS = 5;
    // BORDER_ON = 1;

    /* Initialize Users */
    BoardUserOne = boardInit(BOARD_SIZE);
    // Cell** BoardUserTwo = boardInit(BOARD_SIZE);

    /* Set Ships */
    initShips(BoardUserOne);
    // initShips(BoardUserTwo);

}

void initProgram(){

    /******INPUT******/
    srand((unsigned int) time(NULL));
    
    INPUT();

    /* Print out first state of game */
    boardPrint(BoardUserOne);
    // boardPrint(BoardUserTwo);

    /******LOGIC******/


    /* Deallocate everything at the end of game */
    //TODO Destroy for ships
    boardDestroy(BoardUserOne);
    // boardDestroy(BoardUserTwo);

}

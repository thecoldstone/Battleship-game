/**
 * @file program.c 
 * @brief Implementation of API to run the program
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include "init.h"

int genRandomNumber(int lowest, int highest){

    if(lowest == 0){
        return rand() % highest;
    } else if(lowest > 0){
        return rand() % highest + lowest;
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
    int howToSetShips;
    printf("Choose how to insert ships\n[1] Manually\n[2] Randomly\n:");
    scanf(" %1d", &howToSetShips);
    
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

}

int initShoot(User* user){

    int x, y;

    printf("Set coordinates [x, y]: ");
    scanf(" %d,%d", &x, &y);

    return shoot(user, x, y);

}

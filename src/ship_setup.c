/**
 * @file ship_setup.c 
 * @brief API for ship setup
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include "ship_setup.h"

static int genRandomNumber(int lowest, int highest){

    if(lowest == 0){
        return rand() % highest;
    } else if(lowest > 0){
        return rand() % highest + lowest;
    } else {
        return -1;
    }

}

static void initShipsRandomly(Cell** board){
 
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

static void initShipsManually(Cell** board){
    
    int i = 0;

    while(i != NUMBER_OF_SHIPS) {

        boardPrint(board, 1);
        
        int type;
        printf("Choose the type of board to insert [0-4]: ");
        while(!scanf("%d", &type));       

        int x, y, rotate;

        printf("Set coordinates [x, y]: ");
        scanf(" %d,%d", &x, &y);

        printf("Rotate [0-4] (0˚, 90˚, 180˚, 270˚, 360˚)): ");
        scanf(" %d", &rotate);

        while(!insertShip(board, type, x, y, rotate)){
            fprintf(stdout, RED"[FAILED]"RESET_COLOR"You can not insert there [%d, %d]\n", x, y);
            printf("Set coordinates [x, y]: ");
            scanf(" %d,%d", &x, &y);

            printf("Rotate [0-4] (0˚, 90˚, 180˚, 270˚, 360˚)): ");
            scanf(" %d", &rotate);
            printf("\n");
        }

        // To clear terminal window
        system("clear");

        if(NUMBER_OF_SHIPS - i - 1 != 0){
            printf("Ship remained to insert: %d\n\n", NUMBER_OF_SHIPS - i - 1);
        }
        
        i++;
    }
}

void initShips(User* user){

    /******INPUT******/
    bool isInitialized = false;
    int howToSetShips;
    fprintf(stdout, "User %i\n", user->id);
    fprintf(stdout, "Choose how to insert ships\n[1] Manually\n[2] Randomly\n:");
    scanf(" %1d", &howToSetShips);
    
    while(!isInitialized){
        
        switch(howToSetShips){
        
        case 1:
            initShipsManually(user->board);
            isInitialized = true;
            break;
        case 2:
            initShipsRandomly(user->board);
            isInitialized = true;
            break;
        default:
            printf(RED"[FAIL]"RESET_COLOR"This option does not exist. Try again: ");
            scanf(" %1d", &howToSetShips);

        }      
    }

}

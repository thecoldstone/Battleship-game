/**
 * @file Header of battleship game 
 * @brief Implementation of board methods
 * @author Nikita Zhukov
 * @date 04.04.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "battleship.h"

bool isOccupied(Cell** board, int x, int y){
    return (board[x][y].ship != NULL || board[x][y].isBorder);
}

bool isOutOfBoard(int i){
    return ((i >= BOARD_SIZE || i < 0 ) ? 1 : 0);  
}

void deleteFailedShip(Cell** board, Coordinates* coord){

    for(int i = 0; i < BITMAP_SIZE; i++){
        
        //Stopper
        if(coord[i].x == -1) {
            break;
        }

        board[coord[i].x][coord[i].y].ship = NULL;
    }

    free(coord);
    coord = NULL;

}

bool isItBorder(Cell** board, int x, int y){
    return board[x][y].isBorder != false;
}

/* Needed function for future */
// bool isNeighbour(Cell** board, int x, int y){
    
//     bool itIsNeighbour = false;

//     if(!isOutOfBoard(x - 1) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x - 1, y);
//     }

//     if(!isOutOfBoard(y - 1) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x, y - 1);
//     }

//     if(!isOutOfBoard(x - 1) && !isOutOfBoard(y - 1) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x - 1, y - 1);
//     }

//     if(!isOutOfBoard(x + 1) && !isOutOfBoard(y) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x + 1, y);
//     }

//     if(!isOutOfBoard(x) && !isOutOfBoard(y + 1) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x, y + 1);
//     }

//     if(!isOutOfBoard(x + 1) && !isOutOfBoard(y + 1) && !itIsNeighbour){
//         itIsNeighbour = isItBorder(board, x + 1, y + 1);
//     }    

//     return itIsNeighbour;

// }

void setBorder(Cell** board, Coordinates* coordOfTheShip){

    for(int i = 0; i < BITMAP_SIZE + 1; i++){

        int x = coordOfTheShip[i].x;
        int y = coordOfTheShip[i].y;
        
        //Stopper
        if(x == -1) {
            break;
        }

        if(!isOutOfBoard(x - 1) && !isItBorder(board, x - 1, y)){
            board[x - 1][y].isBorder = true;
        }

        if(!isOutOfBoard(y - 1) && !isItBorder(board, x, y - 1)){
           board[x][y - 1].isBorder = true;
        }

        if(!isOutOfBoard(x - 1) && !isOutOfBoard(y - 1) && !isItBorder(board, x - 1, y - 1)){
            board[x - 1][y - 1].isBorder = true;
        }

        if(!isOutOfBoard(x + 1) && !isOutOfBoard(y) && !isItBorder(board, x + 1, y)){
            board[x + 1][y].isBorder = true;
        }

        if(!isOutOfBoard(x) && !isOutOfBoard(y + 1) && !isItBorder(board, x, y + 1)){
            board[x][y + 1].isBorder = true;
        }

        if(!isOutOfBoard(x + 1) && !isOutOfBoard(y + 1) && !isItBorder(board, x + 1, y + 1)){
            board[x + 1][y + 1].isBorder = true;
        }    

        if(!isOutOfBoard(x - 1) && !isOutOfBoard(y + 1) && !isItBorder(board, x - 1, y + 1)){
            board[x - 1][y + 1].isBorder = true;
        }

        if(!isOutOfBoard(x + 1) && !isOutOfBoard(y - 1) && !isItBorder(board, x + 1, y - 1)){
            board[x + 1][y - 1].isBorder = true;
        }

    }
    
    for(int i = 0; i < BITMAP_SIZE + 1; i++){
        
        //Stopper
        if(coordOfTheShip[i].x == -1) {
            break;
        }

        if(board[coordOfTheShip[i].x][coordOfTheShip[i].y].isBorder){
            board[coordOfTheShip[i].x][coordOfTheShip[i].y].isBorder = false;
        }

    }

}

bool isItInserted(Cell** board, int x, int y, Ship* ship){

    int x_ship, y_ship;
    //Coordinates are used to delete pointers to the ship if the insertion failed
    //OR
    //To set borders if insertion has been successful 
    Coordinates* coordToFree = (Coordinates*) malloc(sizeof(Coordinates) * (BITMAP_SIZE + 1));

    //Check allocation
    if(!coordToFree){
        fprintf(stderr, "[INTERNAL ERROR] Failed allocation.\n");
        return false;
    }

    int indexCoord = 0;

    if(isOccupied(board, x, y)){
        return false;
    }

    for(int i = 0; i < ship->size; i++) {
        for(int j = 0; j < ship->size; j++){
            if(ship->bitmap[i][j] != '#'){
                
                int x_tmp = x;
                int y_tmp = y;
                 //Insert Stopper
                coordToFree[indexCoord].x = -1;

                x_ship = i;
                y_ship = j;

                if(x_ship < 1) {
                    --x_tmp;
                }

                if(y_ship < 1) {
                    --y_tmp;
                }

                if(x_ship > 1) {
                    ++x_tmp;
                } 

                if(y_ship > 1) {
                    ++y_tmp;
                }

                if(isOutOfBoard(x_tmp) || isOutOfBoard(y_tmp)) {
                    deleteFailedShip(board, coordToFree);
                    return false;
                }

                if(isOccupied(board, x_tmp, y_tmp)){
                    deleteFailedShip(board, coordToFree);
                    return false;
                }

                coordToFree[indexCoord].x = x_tmp;
                coordToFree[indexCoord].y = y_tmp;
                indexCoord++;
                board[x_tmp][y_tmp].ship = ship;
                #ifdef DEBUG
                shipPrint(board[x_tmp][y_tmp].ship);
                fprintf(stdout, "Board cell: %p\n Ship to be inserted: %p\n",(void*) &board[x][y].ship, (void*) &(ship));
                #endif
            }
        }
    }

    if(BORDER_ON){
        setBorder(board, coordToFree);
    }

    free(coordToFree);
    coordToFree = NULL;

    return true;
}

bool insertShip(Cell** board, tTypeShip type, int x, int y, int rotate){
    
    if(board == NULL) {
        return false;
    }

    // Check inserted coordinates: x and y
    if(isOutOfBoard(x) || isOutOfBoard(y)) {
        return false;
    }

    // Create ship
    Ship* ship = shipCreate(type);

    if(!ship) {
        fprintf(stderr, RED"[INTERNAL ERROR] Failed Allocation.\n"RESET_COLOR);
        return false;
    }

    //Check inserted rotation: rotate
    if(rotate > 0){
        shipRotate(ship, rotate);
    }

    if(!isItInserted(board, x, y, ship)){
        return false;
    } 

    return true;
} 

int shoot(User* user, int x, int y){

    if(user->board == NULL) {
        return -1;
    }

    // Check inserted coordinates: x and y
    if(isOutOfBoard(x) || isOutOfBoard(y)) {
        return -1;
    }

    // If it's a miss
    if(!isOccupied(user->board, x, y) && user->board[x][y].state == NO_SHOOT){
        user->board[x][y].state = MISS;
    }

    if(isOccupied(user->board, x, y) && user->board[x][y].state == NO_SHOOT && user->board[x][y].ship->hp){
        user->board[x][y].state = HIT;

        if(--user->board[x][y].ship->hp == 0){
            user->ships--;
        }

        return 1;
    }

    return 0;

}

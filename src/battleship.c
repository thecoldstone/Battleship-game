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
    return (board[x][y].ship != NULL);
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

}

bool isItBorder(Cell** board, int x, int y){
    return board[x][y].isBorder != false;
}

void setBorder(Cell** board, int x, int y){
    
    if(!isOutOfBoard(x - 1)){
        board[x - 1][y].isBorder = true;
    }

    if(!isOutOfBoard(y - 1)){
        board[x][y - 1].isBorder = true;
    }

    if(!isOutOfBoard(x + 1)){
        board[x + 1][y].isBorder = true;
    }

    if(!isOutOfBoard(y + 1)){
        board[x][y+1].isBorder = true;
    }

    if(!isOutOfBoard(x + 1) && !isOutOfBoard(y + 1)){
        board[x + 1][y + 1].isBorder = true; 
    } 

    if(!isOutOfBoard(x - 1) && !isOutOfBoard(y - 1)){
        board[x - 1][y - 1].isBorder = true; 
    }

}

bool isItInserted(Cell** board, int x, int y, Ship* ship){

    int x_ship, y_ship;
    //Coordinates are used to delete pointers to the ship if the insertion failed
    Coordinates* coordToFree = (Coordinates*) malloc(sizeof(Coordinates) * (BITMAP_SIZE));

    //Check allocation
    if(!coordToFree){
        fprintf(stderr, "[INTERNAL ERROR] Failed allocation.\n");
        return false;
    }

    int indexCoord = 0;

    if(isOccupied(board, x, y) || isItBorder(board, x, y)){
        return false;
    }

    for(int i = 0; i < ship->size; i++) {
        for(int j = 0; j < ship->size; j++){
            if(ship->bitmap[i][j] != '#'){
                
                int x_tmp = x;
                int y_tmp = y;

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
                //Insert Stopper
                coordToFree[indexCoord+1].x = -1;
                
                indexCoord++;

                board[x_tmp][y_tmp].ship = malloc(sizeof(Ship));
                board[x_tmp][y_tmp].ship = ship;

                //Set border
                setBorder(board, x_tmp, y_tmp);
            }
        }
    }

    if(coordToFree) {
        free(coordToFree);
        coordToFree = NULL;
    }

    return true;
}

bool setShip(Cell** board, tTypeShip type, int x, int y, int rotate){
    
    if(board == NULL) {
        return false;
    }

    // Check inserted coordinates: x and y
    if(isOutOfBoard(x) || isOutOfBoard(y)) {
        return false;
    }

    // Create ship
    Ship* ship = shipCreate(type);

    //Check inserted rotation: rotate
    if(rotate > 0){
        shipRotate(ship, rotate);
    }

    if(!isItInserted(board, x, y, ship)){
        printf("[FAILED] Impossible to place to [%d,%d] position\n", x, y);
        return false;
    } 

    return true;
} 

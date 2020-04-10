/**
 * @file ship.c
 * @brief The ship.c file 
 * @author Nikita Zhukov
 * @date 04.04.20
 **/

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"

Ship* shipCreate(tTypeShip type){
    
    BITMAP_SIZE = 3;
    Ship* ship = malloc(sizeof(Ship));
    ship->size = BITMAP_SIZE;
    ship->bitmap = (char**) malloc(sizeof(char*) * BITMAP_SIZE);
        
    for(int i = 0; i < BITMAP_SIZE; i++){
        ship->bitmap[i] = (char*) malloc(sizeof(char) * BITMAP_SIZE);
        for(int j = 0; j < BITMAP_SIZE; j++){
            ship->bitmap[i][j] = '#';
        }
    }
    
    switch (type){
    /******
     * |#|#|#|
     * |#|M|#| array - 3x3
     * |#|#|#|
     ******/    
    case MONOMINO:
        
        ship->bitmap[1][1] = 'M';
        ship->type = MONOMINO;
        ship->hp   = 1;

        break;

    /******
     *|#|D|#|  array - 3x3
     *|#|D|#| 
     *|#|#|#|  
     ******/ 
    case DOMINO:

        ship->bitmap[0][1] = 'D';
        ship->bitmap[1][1] = 'D';
        ship->type = DOMINO;
        ship->hp   = 2;

        break;    
    
    /******
     * |#|I|#|  array - 3x3
     * |#|I|#|
     * |#|I|#|  
     ******/ 
    case TROMINO:
    
        ship->bitmap[0][1] = 'I';
        ship->bitmap[1][1] = 'I';
        ship->bitmap[2][1] = 'I';
        ship->type = TROMINO;
        ship->hp   = 3;

        break;

    /******
     * |#|T|#|  array - 3x3
     * |#|T|T|
     * |#|T|#|  
     ******/ 
    case T_TETROMINO:
        ship->bitmap[0][1] = 'T';
        ship->bitmap[1][1] = 'T';
        ship->bitmap[1][2] = 'T';
        ship->bitmap[2][1] = 'T';
        ship->type = T_TETROMINO;
        ship->hp   = 4;
        
        break;
    /******
     * |#|L|#|  array - 3x3
     * |#|L|#|
     * |#|L|L|  
     ******/ 
    case L_TETROMINO:
        ship->bitmap[0][1] = 'L';
        ship->bitmap[1][1] = 'L';
        ship->bitmap[2][1] = 'L';
        ship->bitmap[2][2] = 'L';
        ship->type = L_TETROMINO;
        ship->hp   = 4;

        break;
    }

    return ship;
}

void shipPrint(Ship* ship){
    for(int i = 0; i < ship->size; i++) {
        printf("|");
        for(int j = 0; j < ship->size; j++) {
            printf(" %c |", ship->bitmap[i][j]);
        }
        printf("\n");
    }
}

//@link https://www.codespeedy.com/rotate-a-matrix-in-cpp/
void shipRotate(Ship* ship, int k){

    int n = ship->size;

    for(int timeToRotate = 0; timeToRotate < k; timeToRotate++){
        for(int i = 0; i < n/2; i++) {
            for(int j = i; j < n - i - 1; j++) {
                char tmp = ship->bitmap[i][j];
                ship->bitmap[i][j] = ship->bitmap[n - 1 - j][i];
                ship->bitmap[n - 1 - j][i] = ship->bitmap[n - 1 - i][n - 1 - j];
                ship->bitmap[n - 1 - i][n - 1 - j] = ship->bitmap[j][n - 1 - i];
                ship->bitmap[j][n - 1 - i] = tmp;
            }
        }
    }

} 

void destroyShip(Ship* ship){
    
    for(int i = ship->size; 0 < i ; i--) {
        free(ship->bitmap[i]);
        ship->bitmap[i] = NULL;
    }

    free(ship->bitmap);
    ship->bitmap = NULL;

}

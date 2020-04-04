/**
 * @file board.c 
 * @brief Board implementation 
 * @author Nikita Zhukov 
 * @date 21.03.20
*/

#include <stdlib.h>
#include <stdio.h>
#include "board.h" 

/**
 * @brief Initialize the board
 * 
 * @param size - the size of board (n x n)
 * @return two dimensional board
 */ 
Cell** boardInit(int size) {

    if(size <= 0){
        return NULL;
    }

    Cell** newBoard = (Cell**) malloc(size * sizeof(Cell*));

    if(newBoard == NULL) {
        fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        newBoard[i] = (Cell*) malloc(size * sizeof(Cell));
        if((newBoard)[i] == NULL) {
                    fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
                    exit(1);
                }
        for(int j = 0; j < size; j++) {
                newBoard[i][j].ship = NULL;
                newBoard[i][j].state = 0;
                newBoard[i][j].isBorder = false;
        }
    }

    return newBoard;
}

/**
 * @brief Print out the board
 * 
 * @param board
 */ 
void boardPrint(Cell** board) {
    
    if(board == NULL) {
        return;
    }

    printf(" ");
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf(" %d", i);
    }

    printf("\n");

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%i", i);
        for(int j = 0; j < BOARD_SIZE; j++) {
            printf("|");

            /***PRINT SHIP TYPE***/
            if(board[i][j].ship != NULL) {
                // printf("%d", board[i][j].ship->size);

                switch(board[i][j].ship->type)
                {
                case MONOMINO:
                    printf("M");
                    break;
                case DOMINO:
                    printf("D");
                    break;
                case TROMINO:
                    printf("I");  
                    break;  
                case T_TETROMINO:
                    printf("T");
                    break;
                case L_TETROMINO:
                    printf("L");
                    break;
                }

                continue;
            }
            /***PRINT BOARD STATES***/
            switch (board[i][j].state)
            {
            case HIT:
                printf(RED"X"RESET_COLOR);
                break;
            case MISS:
                printf(BLUE"*"RESET_COLOR);
                // printf();
                break;    
            default:
                printf(BLUE"~"RESET_COLOR);
                break;
            }

        }
        printf("|\n");
    }

    printf("\n");

}

/**
 * @brief Destroy the board
 * 
 * @param board 
 */ 
void boardDestroy(Cell** board) {
    
    if(board == NULL) {
        return;
    }

    for(int i = BOARD_SIZE; 0 < i ; i--) {

        free(board[i]);
        board[i] = NULL;
    }

    free(board);
    board = NULL;
}

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

bool isItBoard(Cell** board, int x, int y){
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

bool isPossible(Cell** board, int x, int y, Ship* ship){

    int x_ship, y_ship;
    Coordinates* coordToFree = (Coordinates*) malloc(sizeof(Coordinates) * (BITMAP_SIZE));
    int indexCoord = 0;

    if(isOccupied(board, x, y) || isItBoard(board, x, y)){
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
                // if(board[x_tmp][y_tmp].isBorder){
                    
                // }
            }
        }
    }

    if(coordToFree) {
        free(coordToFree);
        coordToFree = NULL;
    }

    return true;
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

    if(!isPossible(board, x, y, ship)){
        printf("[FAILED] Impossible to place to [%d,%d] position\n", x, y);
        return false;
    } 

    return true;
} 

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

        break;
    }

    return ship;
}

void destroyShip(Ship* ship){
    
    for(int i = ship->size; 0 < i ; i--) {
        free(ship->bitmap[i]);
        ship->bitmap[i] = NULL;
    }

    free(ship->bitmap);
    ship->bitmap = NULL;

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
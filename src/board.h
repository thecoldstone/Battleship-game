/**
 * @file board.h
 * @brief The structures used for board
 * @author Nikita Zhukov
 * @date 21.03.20
 **/

#ifndef _BOARD_H
#define _BOARD_H

//Colors
#define RESET_COLOR "\x1B[0m"
#define BLUE "\x1B[34m"
#define RED  "\x1B[0;31m"
#define CYAN "\x1B[0;36m"

//Board characteristics
int BOARD_SIZE; 
int NUMBER_OF_SHIPS;

//Ship characteristics
int BITMAP_SIZE; 

#include<stdbool.h>

typedef enum {
    MONOMINO      = 0,
    DOMINO        = 1,
    TROMINO       = 2,
    T_TETROMINO   = 3,
    L_TETROMINO   = 4
} tTypeShip;

typedef struct tShip{
    int type;
    int size;
    char **bitmap;
} Ship;

typedef enum tState{
    NO_SHOOT = 0,
    MISS     = 1,
    HIT      = 2
} State;

typedef struct tCoordinates{
    int x; // colomn
    int y; // row
} Coordinates;

typedef struct tCell{
    Ship *ship;
    State state;
    bool isBorder;   
} Cell;

/**********************Board***********************/
Cell** boardInit(int);
bool boardIsHitted(Cell**, int, int);
Cell boardShoot(int, int);
void boardPrint(Cell**);
void boardDestroy(Cell**);

/**********************Ship***********************/

/**
 * @brief Function to insert ship into the board
 * 
 * @param board - User's board
 * @param type  - Type of the ship 
 * @param x, y  - x and y coordinates on a board
 * @param rotation - Rotation factor
 */
bool setShip(Cell**, tTypeShip, int, int, int);

bool isOccupied(Cell**, int, int);
bool isPossible();
bool isRotatable(Cell**, tTypeShip, int, int);
Ship* shipCreate(tTypeShip);
void shipRotate(Ship*, int);
void destroyShip(Ship*);
void shipPrint(Ship*);

#endif

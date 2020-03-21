/**
 * @file board.h
 * @brief The structures used for board
 * @author Nikita Zhukov
 * @date 21.03.20
 **/

#ifndef _BOARD_H
#define _BOARD_H

#include<stdbool.h>

/* Board -> | * | * |
            | * | * |  
*/  

/* 
    | * | < - Cell 
*/

/*
    | *S |
    | *H |
    | *I |
    | *P |
*/

typedef struct tShip{
    int size;
    int **location;
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
    int size;
    State state;      
    Coordinates location; 
} Cell;

/**Future functions**/
Cell** boardInit(int);
bool boardIsHitted(Cell**, int, int);
Cell boardShoot(int, int);
void boardPrint(Cell**);
void boardDestroy(Cell**);

#endif

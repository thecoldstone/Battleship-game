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

#include<stdbool.h>
#include"ship.h"

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

/**
 * @brief Initialize the board
 * @param size - the size of board (n x n)
 * @return two dimensional board
 */ 
Cell** boardInit(int);


/**
 * @brief Print out the board
 * @param board
 * @param noShip - print out without ships
 */ 
void boardPrint(Cell **board, bool noShip);

/**
 * @brief Destroy the board
 * @param board 
 */ 
void boardDestroy(Cell **board);

#endif

/**
 * @file board.h
 * @brief The structures used for board
 * @author Nikita Zhukov
 * @date 21.03.20
 **/

#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "ship.h"
#include "utilities.h"


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
    bool isBorder; // User for mode with border  
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

/**
 * @file board.h
 * @brief The structures used for board
 * @author Nikita Zhukov
 **/

#ifndef _BOARD_H
#define _BOARD_H

#include<stdbool.h>

typedef struct board{
    int size;
    int **array; // TODO <- Should be more complex 
} Board;

/**Future functions**/
Board boardInit(int);
bool boardIsHitted(Board, int, int);
Board boardShoot(int, int);
void boardPrint(Board);
Board boardDestroy(int);

#endif
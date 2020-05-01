/**
 * @file Header of program.c 
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "battleship.h"

#ifndef _PROGRAM_H
#define _PROGRAM_H

/**
 * @brief Initalize ships
 * 
 * @param board - User's board
 */ 
void initShips(Cell** board);

/**
 * @brief Initialize shoot
 * 
 * @param board - User's board
 * @return 1 - hit, 0 - miss
 */ 
int initShoot(User* user);

#endif 

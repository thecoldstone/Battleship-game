/**
 * @file Header of ship_setup.c 
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
 * @param user - User's board
 */ 
void initShips(User* user);

/**
 * @brief Initialize shoot
 * 
 * @param user - User's board
 * @return 1 - hit, 0 - miss
 */ 
int initShoot(User* user);

#endif 

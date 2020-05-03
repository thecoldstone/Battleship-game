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
 * @brief Get random number in a range (lowest..highest);
 * 
 * @param lowest
 * @param highest
 * 
 * @return random number
 */
static int genRandomNumber(int lowest, int highest);

/**
 * @brief Mode to insert ship at random positions
 * 
 * @param board - User's board
 */ 
static void initShipsRandomly(Cell** board);

/**
 * @brief Mode to insert ships manually
 * 
 * @param board - User's board
 */ 
static void initShipsManually(Cell** board);

/**
 * @brief Initalize ships
 * 
 * @param user - User's board
 */ 
void initShips(User* user);

#endif 

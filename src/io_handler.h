/**
 * @file io_handler.h
 * @brief API for analyzing user's input and output
 * @author Nikita Zhukov
 * @date 01.05.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utilities.h"
#include "user.h"

#ifndef _INPUT_H
#define _INPUT_H

/**
 * @brief Get user's input and set the size for the game's board
 * 
 * @return board_size
 */
int inputBoardSize();

/**
 * @brief Get user's input and set the number of ships used in the game
 * 
 * @return number_ships
 */ 
int inputShips(int size);

/**
 * TODO
 */ 
int inputMode();

/**
 * @brief Show the current status of game 
 */ 
void getStatus(User* user);

#endif

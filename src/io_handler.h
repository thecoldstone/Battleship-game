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

/**
 * @brief Analyze coordinates whether they are correct
 * 
 * @param s - string (input)
 * @param x - x axe coordinate
 * @param y - y axe coordinate
 * 
 * @return 1 whether the coordinates are correct otherwise 0
 */ 
int getCoordinates(char *s, int *x, int *y);

/**
 * @brief Get coordinates from input into buffer
 * 
 * @param buf - buffer
 * 
 * @return 1 whether the input is correct otherwise 0
 */
int inputCoordinates(char *buf);

#endif

/**
 * @file user.h
 * @brief API for USER
 * @author Nikita Zhukov
 * @date 03.03.05
 **/

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#ifndef _USER_H
#define _USER_H

typedef struct tUser {
    int id;
    Cell** board;
    int ships;
} User;

/**
 * @brief Initialization for user
 * 
 * @param id - number of user
 * @param board_size 
 * @param number_of_ships
 * 
 * @return a new user
 */ 
User* initUser(int id, int board_size, int number_of_ships);

/**
 * @brief Destroy the user
 */
void userDestroy(User* user);

#endif

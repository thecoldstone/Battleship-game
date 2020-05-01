/**
 * @file user.h
 * @brief API for USER
 * @author Nikita Zhukov
 * @date 21.03.20
 **/

#include <stdlib.h>
#include "board.h"

#ifndef _USER_H
#define _USER_H

typedef struct tUser {
    int id;
    Cell** board;
    int ships;
} User;

User* initUser(int id, int board_size, int number_of_ships);
void userDestroy(User* user);

#endif

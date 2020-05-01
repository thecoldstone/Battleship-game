/**
 * @file Header for input
 * @brief API for analyzing user's input
 * @author Nikita Zhukov
 * @date 01.05.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "modes.h"
#include "user.h"

#ifndef _INPUT_H
#define _INPUT_H

int inputBoardSize();
int inputShips();
int inputMode();

void getStatus(User* user);

#endif

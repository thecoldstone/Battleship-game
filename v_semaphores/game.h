#include <time.h>
#include <unistd.h>

#include "../src/utilities.h"
#include "../src/io_handler.h"
#include "../src/ship_setup.h"

#ifndef _GAME_H
#define _GAME_H

/**
 * @brief Initialize user
 * 
 * @return defined user
 */
User* init_game(int id);

#endif

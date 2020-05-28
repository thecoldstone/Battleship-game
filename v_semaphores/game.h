#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <err.h>

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

void board_print(Cell** board, bool noShip, int fd);

int get_board(int fd);

#endif

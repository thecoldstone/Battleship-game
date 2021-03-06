/**
 * @file game.h
 * @brief API Game
 * @author Nikita Zhukov
 * @date 26.05.20
 * 
*/

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

/**
 * @brief Print board into file descriptor
 * 
 * @param user 
 * @param noShip - print with ships or not
 * @param fd - file descriptor
 */
void board_print(User* user, bool noShip, int fd);

/**
 * @brief Print board into stdin
 * 
 * @param fd - file descriptor
 */
int get_board(int fd);

#endif

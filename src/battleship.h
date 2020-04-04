/**
 * @file Header of battleship game 
 * @brief API for battleship game 
 * @author Nikita Zhukov
 * @date 04.04.20
 * 
*/

#include "board.h"
#include "ship.h"

#ifndef _BATTLESHIP_H
#define _BATTLESHIP_H

/**
 * @brief Check whether Cell is occupied or not
 * 
 * @param board - User's board
 * @param x, y  - x and y coordinates on a board
 * 
 * @return TRUE - if the Cell does not have a pointer to the ship
 */
bool isOccupied(Cell** board, int x, int y);

/**
 * @brief Verify whether the coordinate 'i' is inside of game board
 * 
 * @param i - coordinate (x or y)
 * @return TRUE - if 'i' is inside of game board
 */ 
bool isOutOfBoard(int i);

/**
 * @brief Delete pointers to the ship after failed insertion into the board
 * 
 * @param board - User's board
 * @param coor - array of coordinates to track failed position 
 */ 
void deleteFailedShip(Cell** board, Coordinates* coord);

/**
 * @brief Verify whether the Cells around is a border or not
 * 
 * @param board - User's board
 * @param x, y  - x and y coordinates on a board
 * @return TRUE - if Cells around are not borders (...ship.isBoard = false)
 */ 
bool isItBorder(Cell** board, int x, int y);

/**
 * @brief Set border around the ship
 * 
 * @param board - User's board
 * @param x, y  - x and y coordinates on a board
 */ 
void setBorder(Cell** board, int x, int y);

/**
 * @brief Main function to insert ship into the user's board
 * 
 * @param board - User's board
 * @param x, y  - x and y coordinates on a board
 * @param ship  - ship to insert
 * @return TRUE - if the ship was inserted correctly 
 */
bool isItInserted(Cell** board, int x, int y, Ship* ship);

/**
 * @brief Insert ship into the board
 * 
 * @param board - User's board
 * @param type  - Type of the ship 
 * @param x, y  - x and y coordinates on a board
 * @param rotation - Rotation factor
 * 
 * @return TRUE - if the ship has been inserted correctly, otherwise false
 */
bool setShip(Cell** board, tTypeShip type, int x, int y, int rotate);

/**
 * Is it needed?
 */
bool isRotatable(Cell**, tTypeShip, int, int);

#endif

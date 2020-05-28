/**
 * @file ship.h
 * @brief The ship header file
 * @author Nikita Zhukov
 * @date 04.04.20
 **/

#ifndef _SHIP_H
#define _SHIP_H

int BITMAP_SIZE; 

typedef enum {
    MONOMINO      = 0,
    DOMINO        = 1,
    TROMINO       = 2,
    T_TETROMINO   = 3,
    L_TETROMINO   = 4
} tTypeShip;

typedef struct tBitMap{
    char** bitmap;
} BitMap;

typedef struct tShip2{
    int hp;
    int type;
    BitMap* map;
} Ship2;

typedef struct tShip{
    int hp;
    int type;
    int size;
    char bitmap[3][3]; // Set to be constant. [Reason: Memleeks]
} Ship;


/****/
Ship2* shipCreate2(tTypeShip type);

/**
 * @brief Creat a ship according to the type
 * 
 * @param t - type of the ship
 * 
 * @return a new ship
 */ 
Ship* shipCreate(tTypeShip t);

/**
 * @brief Rotation (0, 90, 180, 270, 360) = (0, 1, 2, 3, 4) respectively
 * 
 * @param ship
 * @param anlge
 */
void shipRotate(Ship* ship, int angle);

/**
 * @brief Print out the bitmap of the ship
 * 
 * @param ship
 */
void shipPrint(Ship* ship);

/**
 * @brief Destroy th ship
 * 
 * @param ship
 * 
 * @return pointer to the ship
 */ 
Ship* destroyShip(Ship* ship);

#endif

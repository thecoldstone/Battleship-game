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

typedef struct tShip{
    int hp;
    int type;
    int size;
    char** bitmap;
} Ship;

Ship* shipCreate(tTypeShip);
void shipRotate(Ship*, int);
void destroyShip(Ship*);
void shipPrint(Ship*);

#endif

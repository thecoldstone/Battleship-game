#include "game.h"

User* init_game(int id) {
    /* FOR RANDOM INSERTION */
    srand((unsigned int) time(NULL)); 

    BOARD_SIZE = 10;
    NUMBER_OF_SHIPS = 5;

    /*INITIALIZE THE GAME*/
    User* user = initUser(1, BOARD_SIZE, NUMBER_OF_SHIPS);
    user->id = id;
    /*INITIALIZE THE SHIPS*/
    initShips(user);

    return user;
}

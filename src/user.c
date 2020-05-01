#include "user.h"

User* initUser(int id, int BOARD_SIZE, int NUMBER_OF_SHIPS){

    User* user = malloc(sizeof(User));
    user->id = id;
    user->board = boardInit(BOARD_SIZE);
    user->ships = NUMBER_OF_SHIPS;

    return user;

}

void userDestroy(User* user){
    free(user);
}

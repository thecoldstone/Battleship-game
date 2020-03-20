/**
 * @file board.c 
 * @brief Board implementation 
 * @author Nikita 
 * 
*/

#include "board.h"

/**
 * 
*/
Board boardInit(int size) {

    Board newBoard;
    newBoard.size = size;

    for (int i = 0; i < size; i++){
 
        for(int j = 0; j < size; j++){

        }
    }

    return newBoard;
}

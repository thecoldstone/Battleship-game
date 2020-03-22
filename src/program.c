/**
 * @file run.c 
 * @brief Implementation of API to run the program
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include"program.h"

//TODO Make it more modular 
int initProgram(int sizeOfBoard){

    int status = 0;

    Cell** newBoard = boardInit(sizeOfBoard);
    
    // 1. Show the initialize empty board
    boardPrint(newBoard);
    
    // 2. UserOne and UserTwo starts creating their own boards
    /* User One */
        //....
    printf("Enter the type of ship: ");

    /* User Two */
        //....

    /* Deallocate everything at the end of game */
    boardDestroy(newBoard);

    return status;
}

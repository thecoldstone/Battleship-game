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

    //DIOGO FOR YOU!!!!
    // | | | | | | | 
    // V V V V V V V
    //UNCOMMENT BELLOW CODE
    // //It's the same as newBoard[0][0]
    // (*(newBoard))->state = 4;
    // //It's the same as newBoard[0][2]
    // (*(newBoard) + 2)->state = 2;
    // //It's the same as above
    // (*(*(newBoard) + 2)).state = 3;
    // //It's the same as newBoard[1][2] 
    // (*(*(newBoard + 1) + 2)).state = 2;
    // // newBoard[1][2].state = 4; <- Uncomment this to see the difference
    // // printf("%d", (*(newBoard))->state);
    
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

/**
 * @file main.c 
 * @brief Main file 
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

  
int main() 
{ 
    int size;

    printf("Enter the size of board: ");
    //If scanf is failed -> Program is terminated
    if(!scanf("%d", &size)){
        fprintf(stderr, "[ERROR] Input is incorrect\n");
        printf("[ADVICE] Type please number\n\n");
        exit(2);
    }

    Cell** newBoard = boardInit(size);

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
    boardPrint(newBoard);

    boardDestroy(newBoard);
  
    return 0; 
} 

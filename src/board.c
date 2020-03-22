/**
 * @file board.c 
 * @brief Board implementation 
 * @author Nikita Zhukov 
 * @date 21.03.20
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "board.h" 

/**
 * @brief Initialize the board
 * 
 * @param size - the size of board (n x n)
 * @return two dimensional board
 */ 
Cell** boardInit(int size) {

    Cell** newBoard = (Cell**) malloc(size * sizeof(Cell*));

    if(newBoard == NULL) {
        fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
                newBoard[i] = (Cell*) malloc(size * sizeof(Cell));
                if((newBoard)[i] == NULL) {
                    fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
                    exit(1);
                }
                newBoard[i][j].state = 0;
        }
    }

    //Set up the size of board
    (**(newBoard)).size = size;

    return newBoard;
}

/**
 * @brief Print out the board
 * 
 * @param board
 */ 
void boardPrint(Cell** board) {
    assert(board != NULL);

    for(int i = 0; i < (**(board)).size; i++) {
        for(int j = 0; j < (**(board)).size; j++) {
            printf("|");


            switch (board[i][j].state)
            {
            case HIT:
                // printf();
                break;
            case MISS:
                // printf();
                break;    
            default:
                printf(BLUE"~"RESET_COLOR);
                break;
            }

        }
        printf("|\n");
    }
}

/**
 * @brief Destroy the board
 * 
 * @param board 
 */ 
void boardDestroy(Cell** board) {
    
    for(int i = (**(board)).size; 0 < i; i--) {
        free(board[i]);
        board[i] = NULL;
    }

    free(board);

    board = NULL;
}

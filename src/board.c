/**
 * @file board.c 
 * @brief Board implementation 
 * @author Nikita Zhukov 
 * @date 21.03.20
*/

#include <stdlib.h>
#include <stdio.h>
#include "board.h" 

Cell** boardInit(int size) {

    if(size <= 0){
        return NULL;
    }

    Cell** newBoard = (Cell**) malloc(size * sizeof(Cell*));

    if(newBoard == NULL) {
        fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        newBoard[i] = (Cell*) malloc(size * sizeof(Cell));
        if((newBoard)[i] == NULL) {
                    fprintf(stderr, "[ERROR] Internal Error: Allocation error\n");
                    exit(1);
                }
        for(int j = 0; j < size; j++) {
                newBoard[i][j].ship = NULL;
                newBoard[i][j].state = 0;
                newBoard[i][j].isBorder = false;
        }
    }

    return newBoard;
}

void boardPrint(Cell** board) {
    
    if(board == NULL) {
        return;
    }

    printf(" ");
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf(" %d", i);
    }

    printf("\n");

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%i", i);
        for(int j = 0; j < BOARD_SIZE; j++) {
            printf("|");

            /***PRINT SHIP TYPE***/
            if(board[i][j].ship != NULL) {
                // printf("%d", board[i][j].ship->size);

                switch(board[i][j].ship->type)
                {
                case MONOMINO:
                    printf("M");
                    break;
                case DOMINO:
                    printf("D");
                    break;
                case TROMINO:
                    printf("I");  
                    break;  
                case T_TETROMINO:
                    printf("T");
                    break;
                case L_TETROMINO:
                    printf("L");
                    break;
                }

                continue;
            }
            /***PRINT BOARD STATES***/
            switch (board[i][j].state)
            {
            case HIT:
                printf(RED"X"RESET_COLOR);
                break;
            case MISS:
                printf(BLUE"*"RESET_COLOR);
                // printf();
                break;    
            default:
                printf(BLUE"~"RESET_COLOR);
                break;
            }

        }
        printf("|\n");
    }

    printf("\n");

}

void boardDestroy(Cell** board) {
    
    if(board == NULL) {
        return;
    }

    for(int i = BOARD_SIZE; 0 < i ; i--) {

        free(board[i]);
        board[i] = NULL;
    }

    free(board);
    board = NULL;
}

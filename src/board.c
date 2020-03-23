/**
 * @file board.c 
 * @author Diogo Gomes
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

        /*
        Board boardInit(int size){
        Board newBoard;
        newBoard.size = size;

        //Alocar memória
        newBoard.board = malloc(sizeof(int*) * size);
        for(int k=0;k<size;k++){
            *(newBoard.board + k) = malloc(sizeof(int) * size);
        }

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                *(*(newBoard.board + i) + j) = 0;
            }
        }

        return newBoard;
    }

    void printBoard(Board x){
        int size = x.size;
        for(int i=0;i<size;i++){
            printf("|");
            for(int j=0;j<size;j++){
                printf("%d|", *(*(x.board+i) + j));
            }
            printf("\n");
        }
        printf("\n");
    }

    Board play(Board newBoard, int x, int y){
        *(*(newBoard.board + x) + y) = 1;
        return newBoard;
    }

    */

    Cell** createBoard(int size){
        Cell** board;

        //Alocar memória
        board = (Cell**) malloc(sizeof(Cell*) * size);

        for(int k=0;k<size;k++){
            *(board + k) = (Cell*) malloc(sizeof(Cell) * size);
        }

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                (*(board + i)+j)->state=0;
            }
        }

        return board;
    }

    void printCell(Cell** board, int size){
        for(int i=0;i<size;i++){
            printf("|");
            for(int j=0;j<size;j++){
                printf("%d|", (*(board + i) + j)->state);
            }
            printf("\n");
        }
        printf("\n");
    }

    Cell** atack(Cell** board, int x, int y){
        (*(board + x) + y)->state = 1;

        return board;
    }



/*
    Board boardInit(){
        Board newBoard;
        newBoard.size = 10;
        newBoard.board = malloc(sizeof(int) * 10);
        for(int i=0;i<10;i++){
            *(newBoard.board+i) = 0;
        }

        return newBoard;
    }

    void printBoard(Board x){
        printf("|");
        for(int j=0;j<10;j++){
            printf("%d| ", *(x.board)+j);
        }
        printf("\n");
        */
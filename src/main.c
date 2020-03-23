/**
 * @file board.c 
 * @author Diogo Gomes
 * 
*/

#include <stdio.h>

#include "board.h"


int main(){

	/*
	Board newBoard = boardInit(input_size);

	//Input: Coordenadas de um ataque
	printf("Coordinates to attack: ");
	int x, y;
	scanf("%d %d", &x, &y);

	newBoard = play(newBoard, x, y);

	printBoard(newBoard);
*/

	//Input: size of board
	printf("Size of the Board: ");
	int input_size;
	scanf("%d", &input_size);

	Cell** board = createBoard(input_size);

	printCell(board, input_size);

	//Input: Coordenadas de um ataque
	printf("Coordinates to attack: ");
	int x, y;
	scanf("%d %d", &x, &y);

	board = atack(board, x, y);

	printCell(board,input_size);

	return 0;
}
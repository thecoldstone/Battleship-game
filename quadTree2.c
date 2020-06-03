#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Points{
	int x;
	int y;
} point;

typedef struct QuadTrees{
	struct QuadTrees* NW;
	struct QuadTrees* NE;
	struct QuadTrees* SW;
	struct QuadTrees* SE;

	//--------------------------------------------------------
	//Point of the top most right corner of the quadrante
	int x;
	int y;


	//Size of the side of the quadrante
	int L;
	//--------------------------------------------------------

	//Informes if the node is leaf or not
	bool leaf;

	//If is higher than 1 turnes the leaf false
	int full;
	//--------------------------------------------------------

	//Value of the node | 1-empty, 2-ship
	int value;

} quadTree;

void addPoint(quadTree* board, point p, int v){
	printf("teste1");
	if(board->full != 1 || board == NULL){
		if(board == NULL){
			board = (quadTree*) malloc(sizeof(quadTree*));
		}
		board->value = v;
		board->full = 1;
		printf("teste2");
		board->NW = NULL;		
		board->NE = NULL;		
		board->SW = NULL;		
		board->SE = NULL;
	}
	
	else{
		/*
		if(p.x <= (board->x + (board->L/2)) && p.y <= (board->y + (board->L/2)))
		*/
			if(board->NW == NULL){
				printf("teste3");
				addPoint(board->NW, p, v);
			}
	}
	
	
}

int main(){

	//Ask and store the size of the board
	printf("Choose size of the board: ");
	int size;
	scanf("%d", &size);

	//Create board
	quadTree* board;
	board = (quadTree*) malloc(sizeof(quadTree*));

	//Give size to the quadTree
	board->x = 1;
	board->y = 1;
	board->L = size;

	//Ask the point to insert and store in point
	point point1;
	printf("What point do you want to insert?\n");
	printf("x: "); scanf("%d", &point1.x);
	printf("y: "); scanf("%d", &point1.y);

	//Test function
	addPoint(board, point1, 2);

	//Ask the point to insert and store in point
	point point2;
	printf("What point do you want to insert?\n");
	printf("x: "); scanf("%d", &point2.x);
	printf("y: "); scanf("%d", &point2.y);

	addPoint(board, point2, 1);

	free(board);
	/*
	free(board->NW);
*/
	/*
	printf("%d \n", board->NW->full);
	*/
	return 0;
}

		/*
		board->Nw = (quadTree*) malloc(sizeof(quadTree*));		
		board->NE = (quadTree*) malloc(sizeof(quadTree*));		
		board->Sw = (quadTree*) malloc(sizeof(quadTree*));		
		board->SE = (quadTree*) malloc(sizeof(quadTree*));
		*/
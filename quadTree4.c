#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Points{
	int x;
	int y;
} point;

typedef struct QuadTrees quadTree;

struct QuadTrees{
	quadTree* NW;
	quadTree* NE;
	quadTree* SW;
	quadTree* SE;

	//--------------------------------------------------------
	//Point of the top most right corner of the quadrante
	int x;
	int y;

	//Size of the side of the quadrante
	int L;
	//--------------------------------------------------------

	//If is higher than 1 turnes the leaf false
	int full;
	//--------------------------------------------------------

	//Value of the node | 1-empty, 2-ship
	int value;

};

quadTree* addPoint(quadTree* board, point p, int v, int size){

	if(board == NULL){
		board = (quadTree*) malloc(sizeof(quadTree*));
		board->full = 1;
		board->value = v;

		if(size == 32 || size == 64){
			board->x = 0;
			board->y = 0;
			board->L = 32;
		}

	}
	else{
		size = size / 2;
		if(p.x <= (board->x + size) && p.y <= (board->y + size)) {
			board->NW = addPoint(board->NW, p, v, size);
		}
		else if(p.x > size && p.y <= (board->y + size)) {
			board->NE = addPoint(board->NE, p, v, size);
			
		}
		else if(p.x > size && p.y > size) {
			board->SW = addPoint(board->SW, p, v, size);
		}
		else{
			board->SE = addPoint(board->SE, p, v, size);
			printf("WORKSSSSS \n");
		}




	}
		
	
	
	return board;
}

void printFull(quadTree* board){
	printf("%d \n", board->full);
}

int main(){

	//Ask and store the size of the board
	printf("Choose size of the board: ");
	int size;
	scanf("%d", &size);

	quadTree* board = NULL;

	point point1;
	printf("What point do you want to insert?\n");
	printf("x: "); scanf("%d", &point1.x);
	printf("y: "); scanf("%d", &point1.y);


	//Test function
	board = addPoint(board, point1, 1, 32);
	board = addPoint(board, point1, 1, 32);



	printf("%d \n", board->full);
	printf("%d \n", board->SE->full);


	return 0;

}


/*
	size = size / 2;
		if(p.x <= (board->x + size) && p.y <= (board->y + size)){ 
			board->NW = addPoint(board->NW, p, v, size);
*/







/*
	//Ask the point to insert and store in point
	point point2;
	printf("What point do you want to insert?\n");
	printf("x: "); scanf("%d", &point2.x);
	printf("y: "); scanf("%d", &point2.y);
*/










/*
	//Ask the point to insert and store in point
	point point2;
	printf("What point do you want to insert?\n");
	printf("x: "); scanf("%d", &point2.x);
	printf("y: "); scanf("%d", &point2.y);
*/


	

	
	
	

	/*
	printf("%d \n", board->NW->full);
	*/


		/*
		board->Nw = (quadTree*) malloc(sizeof(quadTree*));		
		board->NE = (quadTree*) malloc(sizeof(quadTree*));		
		board->Sw = (quadTree*) malloc(sizeof(quadTree*));		
		board->SE = (quadTree*) malloc(sizeof(quadTree*));
		*/





//TENS QUE TORNAR A VARIAVEL BOARD GLOBAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
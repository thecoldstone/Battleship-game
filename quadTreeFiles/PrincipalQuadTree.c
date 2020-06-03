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

	point coordinate;


};

quadTree* initQuad(int size){
    quadTree* board = (quadTree*) malloc(sizeof(quadTree*));
    board->full = 1;

	board->x = 0;
	board->y = 0;
	board->L = size;
	
    return board;
}

quadTree* addPoint(quadTree* board, point p, int v, int size, point location){

	if(board == NULL){
		board = (quadTree*) malloc(sizeof(quadTree*));
		board->full = 1;
		board->value = v;
		board->coordinate.x = p.x;
		board->coordinate.y = p.y;
		board->x = location.x;
		board->y = location.y;

	}
	else{

		//If point has been taken already
        if(board->coordinate.x == p.x && board->coordinate.y == p.y) {
        	printf("ERROR: Point is already taken! \n");
            return NULL;
        }

        //LAST PART, WHEN IT ARRIVES THE END!!!!!!!
        if(size == 1){}



        //----------------------------

        size = size / 2;

		if(p.x <= (board->x + size) && p.y <= (board->y + size)) {
			printf("1 QUADRANT!!! \n");
			board->NW = addPoint(board->NW, p, v, size, board->coordinate);
		}
		else if(p.x > size && p.y <= (board->y + size)) {
			printf("2 QUADRANT!!! \n");
			point newLocation;
			newLocation.x = size;
			newLocation.y = board->coordinate.y;

			board->NE = addPoint(board->NE, p, v, size, newLocation);
		}
		else if(p.x <= size && p.y > size) {
			printf("3 QUADRANT!!! \n");
			point newLocation;
			newLocation.x = board->coordinate.x;
			newLocation.y = size;

			board->SW = addPoint(board->SW, p, v, size, newLocation);
		}
		else if(p.x > size && p.y > size){
			printf("4 QUADRANT!!! \n");
			point newLocation;
			newLocation.x = size;
			newLocation.y = size;

			board->SE = addPoint(board->SE, p, v, size, newLocation);
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

	//Create Board
	quadTree* board = initQuad(size);

    point point1;

    for(int i = 0; i < 5; i++) {
        printf("What point do you want to insert?\n");
        printf("x: "); scanf("%d", &point1.x);
        printf("y: "); scanf("%d", &point1.y);
        board = addPoint(board, point1, 1, size, board->coordinate);
    }

	return 0;

}

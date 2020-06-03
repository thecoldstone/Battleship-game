#include <stdio.h>
#include <stdlib.h>

//Coordenates of a cell
typedef struct Coordenates{
	int x;
	int y;
} coordenates;

//Quad Tree
typedef struct QuadTree{
	//points that define de size of partition
	coordenates topLeft;
	coordenates bottomRight;

	//value | ship = 1, empty cell attacked  = 2 or cell w/ ship attacked = 3
	int value;

	//pointers of the 4 partitions
	struct QuadTree* northeast;
	struct QuadTree* northwest;
	struct QuadTree* southeast;
	struct QuadTree* southwest;

	//int that informes if node is relevant, 0 - not relevant or 1 - relevant
	int relevant;

} quadTree;

//Function that creates a board
quadTree* createBoard(int size){
	//Creates a board and allochates memory
	quadTree* board;
	board = (quadTree*) malloc(sizeof(quadTree*));

	//Point top left partition
	board->topLeft.x = 1;	
	board->topLeft.y = 1;
	
	//Point bottom right partition
	board->bottomRight.x = size;
	board->bottomRight.y = size;

	board->relevant = 1;

	board->northeast = NULL;
	board->southwest = NULL;
	board->northwest = NULL;
	board->southeast = NULL;

	board->value = 5;

	return board;
}

//Function that registe a cell on the Quad Tree
void registeCell(quadTree* board, coordenates point, int size, int value){
	
	//Calculate new distance between quadrantes
	int x = (board->topLeft.x - board->bottomRight.x) / 2;
	int y = (board->topLeft.y - board->bottomRight.y) / 2;	

	if(board->relevant == 1){
		//This node is not relevant anymore
		board->relevant = 0;	

		//Initialize all quadrantes

		board->northwest = (quadTree*) malloc(sizeof(quadTree*));
		board->northwest->topLeft.x = board->topLeft.x;
		board->northwest->topLeft.y = board->topLeft.y;
		board->northwest->bottomRight.x = board->topLeft.x + x;
		board->northwest->bottomRight.y = board->topLeft.y + y;

		/*
		board->northeast = (quadTree*) malloc(sizeof(quadTree*));
		board->northeast->topLeft.x = board->topLeft.x + x + 1;
		board->northeast->topLeft.y = board->topLeft.y;
		board->northeast->bottomRight.x = board->bottomRight.x;
		board->northeast->bottomRight.y = board->topLeft.y + y;

		board->southwest = (quadTree*) malloc(sizeof(quadTree*));
		board->southwest->topLeft.x = board->topLeft.x;
		board->southwest->topLeft.y = board->topLeft.y + y;
		board->southwest->bottomRight.x = board->topLeft.x + x;
		board->southwest->bottomRight.y = board->bottomRight.y;

		board->southeast = (quadTree*) malloc(sizeof(quadTree*));
		board->southeast->topLeft.x = board->topLeft.x + x + 1;
		board->southeast->topLeft.y = board->topLeft.y + y +1;
		board->southeast->bottomRight.x = board->bottomRight.x;
		board->southeast->bottomRight.y = board->bottomRight.y;
		*/

		//if its located on quadrant northwest
		if(point.x <= board->northwest->bottomRight.x && point.y <= board->northwest->bottomRight.y){
			board->northwest->value = value;
		}
		//if its located on quadrant northeast		
		else if(point.x > size && point.y <= size){

		}
		//if its located on quadrant southwest		
		else if(point.x <= size && point.y > size){

		}
		//if its located on quadrant southeast		
		else{

		}

	}

	else{
		//if its located on quadrant northwest
		if(point.x <= board->northwest->bottomRight.x && point.y <= board->northwest->bottomRight.y){
			
		}
		//if its located on quadrant northeast		
		else if(point.x > size && point.y <= size){

		}
		//if its located on quadrant southwest		
		else if(point.x <= size && point.y > size){

		}
		//if its located on quadrant southeast		
		else{

		}

	}

}


int main(){
	
	//Size of first Partition
	printf("Size of board: ");
	int size;
	scanf("%d", &size);

	//Create board
	quadTree* board = createBoard(size);

	//Test attacking a cell
	coordenates point1;
	point1.x = 3;
	point1.y = 2;
	
	registeCell(board, point1, size , 2);

	printf("board value: %d \n", board->northwest->value);

	/*
	//Test of createBoard
	printf("(%d,%d) \n", board->bottomRight.x, board->bottomRight.y);
	*/
	
	free(board->northwest);
	/*
	free(board->northeast);
	free(board->southeast);
	free(board->southwest);
*/
	free(board);




	return 0;
}



/**
 * @file board.h
 * @author Diogo Gomes
 **/


/*
typedef struct {
	int **board;
	int size;
} Board;
*/

typedef struct{
	int state;
} Cell;

/*
Board boardInit(int);
void printBoard(Board);
Board play(Board, int, int);
*/

Cell** createBoard(int);
void printCell(Cell**, int);
Cell** atack(Cell**, int, int);
/**
 * @file board.h
 * @brief The structures used for board
 * @author Nikita Zhukov
 **/

typedef struct board{
    int size;
    int **array;
} Board;

/**Future functions**/
Board boardInit(int);
Board boardDestroy(int);
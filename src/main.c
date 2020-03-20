#include <stdio.h>
#include "board.h"

  
int main() 
{ 
    int size;
    printf("Enter the size of board: ");
    scanf("%d", &size);
    Board newBoard = boardInit(size);
  
    return 0; 
} 
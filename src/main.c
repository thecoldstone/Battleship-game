/**
 * @file main.c 
 * @brief Main file 
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include"program.h"

int main() 
{ 
    // printf("\nThe maximum number of ships [%d * %d/ 25]\n", size, size);
    // printf("Enter the number of ships: ");
    // if(!scanf("%d", &numOfShips)){
    //     fprintf(stderr, "[ERROR] Input is incorrect\n");
    //     printf("[ADVICE] Type please number\n\n");
    //     exit(2); // Incorrect input 
    // }

    // if(size * size / 25  < numOfShips) {
    //     fprintf(stderr, "[ERROR] The maximum number of ships for %dx%d board is %d\n", size, size, size*size/25);
    //     exit(3); // Incorrect input [The number of boat]
    // } 
    
   

    int status = initProgram();

    // Idea to handle the errors in program
    switch (status)
    {
        case 0:
            break;
        case 1:
            return 1;
        case 2:
            return 2;
    }

    return 0; 
} 

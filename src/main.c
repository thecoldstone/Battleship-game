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
    int size;

    printf("Enter the size of board: ");
    //If scanf is failed -> Program is terminated
    if(!scanf("%d", &size)){
        fprintf(stderr, "[ERROR] Input is incorrect\n");
        printf("[ADVICE] Type please number\n\n");
        exit(2);
    }
    
    int status = initProgram(size);

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

/**
 * @file io_handler.c
 * @brief API for analyzing user's input and output
 * @author Nikita Zhukov
 * @date 01.05.20
 * 
*/

#include "io_handler.h"

int inputBoardSize(){
    
    int size;

    fprintf(stdout, "Size of board: ");
    scanf("%d", &size);
    //1. [RULE]: The allowed game size should be between 20x20 to 40x40 (always squares).
    while(size < 20 || size > 40){
        fprintf(stderr, RED"[FAILED]"RESET_COLOR" Enter the size of board again between [20..40]: ");
        scanf(" %d", &size);
    }  

    return size;

}

int inputShips(int size){

    int number;
    #ifdef DEBUG
    (void) size;
    #endif


    printf("Number of ships: ");
    scanf(" %d", &number);
    //[RULE]: (N * N)/(5*5) < NUMBER_OF_SHIPS, where N is size of a board
    while((size * size)/(5*5) < number || number < 1) {
        fprintf(stdout, "Number between: [1..%d]\n"RED"[FAILED]"RESET_COLOR" Enter the number of ships again: ", (size * size)/(5*5));
        scanf(" %d", &number);
    }

    return number;
}

//FIXME: Not well organized function!
// int inputMode(){

//     char *c;

//     /**MODE 1 = BORDER **/
//     printf("Set gap between ships to one cell?[y/n]:");
//     scanf(" %1s", c);
//     while(strcmp(c, "y") != 0 && strcmp(c, "n") != 0 && strcmp(c, "Y") != 0 && strcmp(c, "N") != 0){
//         scanf(" %1s", c);
//     }

//     if(strcmp(c, "y") == 0){
//         BORDER_ON = 1;
//     }

//     return 1;

// }

void getStatus(User* user){
    
    // printf("\tACTIVE USER: %i\n\t-------------\n", activeUser);
    // printf("\tYOU ARE ATTACKING THE USER: %i\n\t-------------\n", user->id);
    boardPrint(user->board, true);
    printf("\n\n\n\n\n");

}

int getCoordinates(char *s, int *x, int *y){

    int j = 0;  
    int comma = 0;
    char x_c[4], y_c[4];

    for(unsigned long i = 0; i < strlen(s); i++) {
        
        if(s[i] >= '0' && s[i] <= '9') {
            if (comma == 0) {
                x_c[j] = s[i];
                j++;
            } else if (comma == 1) {
                y_c[j] = s[i];
                j++;
            }           
        } else if (s[i] == ',') {
            
            if(comma > 1) {
                fprintf(stderr, RED"[ERROR]"RESET_COLOR" Not correct coordinates\n");
                return 0;
            }

            j = 0;
            comma++;

        } else {
            fprintf(stderr, RED"[ERROR]"RESET_COLOR" Not correct coordinates\n");
            return 0;
        }
    }

    *x = atoi(x_c);
    *y = atoi(y_c);

    return 1;
}

int inputCoordinates(char *buf) {

    fprintf(stdout, "Enter coordinates [x,y]: ");
    fgets(buf, sizeof(buf), stdin);

    if(buf[strlen(buf) - 1] == '\n') {
        buf[strlen(buf) - 1] = '\0';
    } else {
        return 1;
    }

    fflush(0);

    return 0;

}

/**
 * @file main.c 
 * @brief Main file 
 * @author Nikita Zhukov
 * @date 21.03.20
 * 
*/

#include <time.h>
#include <unistd.h>

#include "user.h"
#include "io_handler.h"
#include "init.h"

int main() 
{   
    /* FOR RANDOM INSERTION */
    srand((unsigned int) time(NULL)); 

    /***********************************************/
    /*START INPUT*/ 
    BOARD_SIZE = 10;
    NUMBER_OF_SHIPS = 5;

    /***********************************************/

    /***********************************************/
    /*INITIALIZE THE GAME*/
    User* user_one = initUser(1, BOARD_SIZE, NUMBER_OF_SHIPS);
    User* user_two = initUser(2, BOARD_SIZE, NUMBER_OF_SHIPS);
    User** active_user = &user_two;

    initShips(user_one->board);
    sleep(1);
    initShips(user_two->board);
    fprintf(stdout, "Game has been initialized.\n");
    sleep(1);
    system("clear");
    /***********************************************/
    
    /***********************************************/
    /*THE GAME'S LOGIC*/
    fprintf(stdout, "Game has started!\n");
    sleep(1);
    system("clear");

    do {

        getStatus(*active_user);

        switch((*active_user)->id){

            case 1:

                if(!initShoot(*active_user)){
                    fprintf(stdout, "Miss\n");
                    active_user = &user_two;
                }

                break;

            case 2:

                if(!initShoot(*active_user)){
                    fprintf(stdout, "Miss\n");
                    active_user = &user_one;
                }

                break;

        } 

        sleep(1);
        system("clear");

        if((*active_user)->ships == 0){
            printf("Game is finished\n");
            printf("USER%i won!\n", (*active_user)->id);
            break;
        }

    } while(true);
    /***********************************************/

    /***********************************************/
    /*DESTROY EVERYTHING*/
    boardDestroy(user_one->board);
    userDestroy(user_one);

    boardDestroy(user_two->board);
    userDestroy(user_two);

    /***********************************************/
    
    return 0; 
} 

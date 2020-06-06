/**
 * @file user2.c
 * @brief User two
 * @author Nikita Zhukov
 * @date 26.05.20
 * 
*/

#define _BSD_SOURCE

#include "v_utilities.h"
#include "game.h"

int main() {
  int fd_shoot = open(FILE_SHOOT, MODES);
  SEMID = init_v_system(FILE_SHOOT, sizeof(BUFFER));

  int fd_board = open(FILE_BOARD, MODES);
  SEMID_B = init_v_system(FILE_BOARD, sizeof(BUFFER_BOARD));
  
  int SHOOT = 0;
  int RECIEVE = 1;
  int GAME = 1;
  int WON = 0;

  User* user = init_game(2);

  SLEEP;
  printf("Press 'enter' once you are ready\n");
  getchar();

  system("clear");

  /* Game Logic */
  while(GAME) {

    while (RECIEVE) {
      
      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user, 1, fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, FULL);

      SLEEP;

      lock(SEMID_B, FULL);
      lock(SEMID_B, MUTX);
      get_board(fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, EMPT);

      SLEEP;

      lock(SEMID, FULL);
      lock(SEMID, MUTX);
      read(fd_shoot, BUFFER, sizeof(BUFFER));
      printf("%s\n", BUFFER);

      if(strcmp(BUFFER, "exit") == 0) {
        RECIEVE = 0;
        GAME = 0;
      }  else {
        
        int x, y;

        if(!getCoordinates(BUFFER, &x, &y) || isOutOfBoard(x) || isOutOfBoard(y)) {
          strcpy(BUFFER, "FAILED");
          SHOOT = 1;
          RECIEVE = 0;
        } else {
          int success = shoot(user, x, y);

          if(success == 0){
            SHOOT = 1;
            RECIEVE = 0;
            strcpy(BUFFER, "MISS");
          } else {
            if(user->ships == 0) {
              strcpy(BUFFER, "WON");
              RECIEVE = 0;
              GAME = 0;
            } else {
              strcpy(BUFFER, "HIT");
            }
          }
        } 
      } 

      unlock(SEMID, MUTX);
      unlock(SEMID, EMPT);
      
      SLEEP;

      w_shoot(SEMID, fd_shoot, BUFFER);

      SLEEP;
      system("clear");
    }
   
    SLEEP;

    while (SHOOT && GAME) {
      
      /* GET UPDATED BOARD */
      lock(SEMID_B, FULL);
      lock(SEMID_B, MUTX);
      get_board(fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, EMPT);

      SLEEP;

      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user, 1, fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, FULL);

      SLEEP;

      /* SHOOT */
      inputCoordinates(BUFFER);
      w_shoot(SEMID, fd_shoot, BUFFER);

      SLEEP;
      
      // READ
      lock(SEMID, FULL);
      lock(SEMID, MUTX);
      read(fd_shoot, BUFFER, sizeof(BUFFER));
      printf("%s\n", BUFFER);
      unlock(SEMID, MUTX);
      unlock(SEMID, EMPT);

      if(strcmp(BUFFER, "WON") == 0) {
        WON = 1;
        SHOOT = 0;
        GAME = 0;
      }

      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
      } else if(strcmp(BUFFER, "FAILED") == 0 || strcmp(BUFFER, "MISS") == 0){ 
        SHOOT = 0;
        RECIEVE = 1;
      } 
     
      memset(BUFFER, 0, strlen(BUFFER));
      SLEEP;
      system("clear");
    }

  }

  if(WON) {
    fprintf(stdout, "WON\n");
  } else {
    fprintf(stdout, "LOST\n");
  }

  /* Deallocation */
  boardDestroy(user->board);
  userDestroy(user);
  /* Delete Semaphore */
  if(semctl(SEMID, 0, IPC_RMID) == -1) {
    end_program("semctl SEMID");
  }

  if(semctl(SEMID_B, 0, IPC_RMID) == -1) {
    end_program("semctl SEMID_B");
  }

  close(fd_board);
  close(fd_shoot);
  return 0;  
}

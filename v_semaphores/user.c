#include "v_utilities.h"
#include "game.h"


int main() {
  int fd_shoot = open(FILE_SHOOT, MODES);
  SEMID = init_v_system(FILE_SHOOT, sizeof(BUFFER));

  int fd_board = open(FILE_BOARD, MODES);
  SEMID_B = init_v_system(FILE_BOARD, sizeof(BUFFER_BOARD));

  int SHOOT = 1;
  int RECIEVE = 0;
  int GAME = 1;

  User* user = init_game(1);
  
  printf("Press 'enter' once you are ready\n");
  getchar();

  system("clear");

  #ifdef DEBUG_FILE_BOARD
  /* GET UPDATED BOARD */
  lock(SEMID_B, FULL);
  lock(SEMID_B, MUTX);
  get_board(fd_board);
  fflush(0);
  unlock(SEMID_B, MUTX);
  unlock(SEMID_B, EMPT);
  
  sleep(1);

  lock(SEMID_B, EMPT);
  lock(SEMID_B, MUTX);
  board_print(user->board, 1, fd_board);
  fflush(0);
  unlock(SEMID_B, MUTX);
  unlock(SEMID_B, FULL);

  sleep(1);

  /* GET UPDATED BOARD */
  lock(SEMID_B, EMPT);
  lock(SEMID_B, MUTX);
  board_print(user->board, 1, fd_board);
  fflush(0);
  unlock(SEMID_B, MUTX);
  unlock(SEMID_B, FULL);

  sleep(1);

  lock(SEMID_B, FULL);
  lock(SEMID_B, MUTX);
  get_board(fd_board);
  fflush(0);
  unlock(SEMID_B, MUTX);
  unlock(SEMID_B, EMPT);

  sleep(1);
  #endif

  /* Game Logic */  
  while(GAME) {

    while(SHOOT) {
      
      /* GET UPDATED BOARD */
      lock(SEMID_B, FULL);
      lock(SEMID_B, MUTX);
      get_board(fd_board);
      fflush(0);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, EMPT);

      sleep(1);

      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user->board, 1, fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, FULL);

      sleep(1);

      // WRITE
      printf("Enter coordinates to shoot: ");
      scanf("%s", BUFFER);
      printf("\n");
      fflush(0);
      w_shoot(SEMID, fd_shoot, BUFFER);

      sleep(1);
      
      // READ
      lock(SEMID, FULL);
      lock(SEMID, MUTX);
      read(fd_shoot, BUFFER, sizeof(BUFFER));
      printf("%s\n", BUFFER);
      fflush(0);
      unlock(SEMID, MUTX);
      unlock(SEMID, EMPT);

      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
      } else {
        strcpy(BUFFER, ""); 
      }

      sleep(1);
      SHOOT = 0;
      RECIEVE = 1;
      system("clear");
    }
    
    sleep(1);

    while (RECIEVE && GAME) {
      
      /* GET UPDATED BOARD */
      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user->board, 1, fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, FULL);

      sleep(1);

      lock(SEMID_B, FULL);
      lock(SEMID_B, MUTX);
      get_board(fd_board);
      // fflush(0);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, EMPT);

      sleep(1);

      /* SHOOT */
      lock(SEMID, FULL);
      lock(SEMID, MUTX);
      read(fd_shoot, BUFFER, sizeof(BUFFER));
      
      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
        strcpy(BUFFER, "exit");
      } else {

        char x[4];
        char y[4];

        if(!getCoordinates(BUFFER, x, y)) {
          strcpy(BUFFER, "MISS");
        } 

        #ifdef DEBUG
        printf("%s\n", BUFFER);
        #endif
      }

      unlock(SEMID, MUTX);
      unlock(SEMID, EMPT);
      
      sleep(1);

      // WRITE
      w_shoot(SEMID, fd_shoot, BUFFER);
      sleep(1);
      SHOOT = 1;
      RECIEVE = 0;
      system("clear");
    }

  }

  /* Deallocation */
  boardDestroy(user->board);
  userDestroy(user);
  close(fd_board);
  close(fd_shoot);
  return 0;  
}

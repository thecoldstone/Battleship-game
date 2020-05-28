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

  User* user = init_game(2);
  printf("Press 'enter' once you are ready\n");
  getchar();

  system("clear");

  #ifdef DEBUG_FILE_BOARD
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
  #endif

  /* Game Logic */
  while(GAME) {

    while (RECIEVE) {
      
      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user, 1, fd_board);
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

      lock(SEMID, FULL);
      lock(SEMID, MUTX);
      read(fd_shoot, BUFFER, sizeof(BUFFER));
      
      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
      } else {
        char x[4];
        char y[4];

        if(!getCoordinates(BUFFER, x, y) || isOutOfBoard(atoi(x)) || isOutOfBoard(atoi(y))) {
          strcpy(BUFFER, "FAILED");
          SHOOT = 1;
          RECIEVE = 0;
        } else {
          int success = shoot(user, atoi(x), atoi(y));

          if(success == 0){
            SHOOT = 1;
            RECIEVE = 0;
            strcpy(BUFFER, "MISS");
          } else {
            strcpy(BUFFER, "HIT");
          }
        }

        #ifdef DEBUG
        printf("%s\n", BUFFER);
        #endif
      }

      unlock(SEMID, MUTX);
      unlock(SEMID, EMPT);
      
      sleep(1);

      w_shoot(SEMID, fd_shoot, BUFFER);

      sleep(1);
      system("clear");
    }
   
    sleep(1);

    while (SHOOT && GAME) {
      
      /* GET UPDATED BOARD */
      lock(SEMID_B, FULL);
      lock(SEMID_B, MUTX);
      get_board(fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, EMPT);

      sleep(1);

      lock(SEMID_B, EMPT);
      lock(SEMID_B, MUTX);
      board_print(user, 1, fd_board);
      unlock(SEMID_B, MUTX);
      unlock(SEMID_B, FULL);

      sleep(1);

      /* SHOOT */
      printf("Enter coordinates to shoot: ");
      scanf("%s", BUFFER);
      printf("\n");
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
      } else if(strcmp(BUFFER, "FAILED") == 0 || strcmp(BUFFER, "MISS") == 0){
        SHOOT = 0;
        RECIEVE = 1;
      } else {
        memset(BUFFER, 0, strlen(BUFFER));
        sleep(1);
        system("clear");
      }
    
    }

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

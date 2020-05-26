#include "v_utilities.h"
#include "game.h"

int main() {
  int fd_game = open(FILE_GAME, O_RDWR | O_CREAT);
  key_t key = 0;
  SEMID = init_v_system(key);
  int SHOOT = 0;
  int RECIEVE = 1;
  int GAME = 1;

  // User* user = init_game(2);
  // printf("Press 'enter' once you are ready\n");
  // getchar();

  // system("clear");

  /* Game Logic */
  while(GAME) {

    while (RECIEVE) {
      // getStatus(user);
      lock(FULL);
      lock(MUTX);
      read(fd_game, BUFFER, sizeof(BUFFER));
      
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

      unlock(MUTX);
      unlock(EMPT);
      
      sleep(1);

      w_shoot(fd_game, BUFFER);

      sleep(1);
      SHOOT = 1;
      RECIEVE = 0;
      // system("clear");
    }
   
    sleep(1);

    while (SHOOT && GAME) {
      // WRITE
      // getStatus(user);
      printf("Enter coordinates to shoot: ");
      scanf("%s", BUFFER);
      printf("\n");
      lock(EMPT);
      lock(MUTX);
      write(fd_game, BUFFER, sizeof(BUFFER));
      unlock(MUTX);
      unlock(FULL);

      sleep(1);
      
      // READ
      lock(FULL);
      lock(MUTX);
      read(fd_game, BUFFER, sizeof(BUFFER));
      printf("%s\n", BUFFER);
      fflush(0);
      unlock(MUTX);
      unlock(EMPT);

      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
      } else {
        strcpy(BUFFER, "");
      }

      sleep(1);
      SHOOT = 0;
      RECIEVE = 1;
      // system("clear");
    }

  }

  /* Deallocation */
  // boardDestroy(user->board);
  // userDestroy(user);
  /* Delete Semaphore */
  if (semctl(SEMID, 0, IPC_RMID) == -1) {
    end_program("semctl");
  }

  close(fd_game);
  return 0;  
}

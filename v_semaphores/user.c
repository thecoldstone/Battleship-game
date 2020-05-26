#include "v_utilities.h"
#include "game.h"

int main() {
  int fd_game = open(FILE_GAME, O_RDWR | O_CREAT);
  key_t key = 0;
  SEMID = init_v_system(key);
  int SHOOT = 1;
  int RECIEVE = 0;
  int GAME = 1;

  User* user = init_game(1);
  
  printf("Press 'enter' once you are ready\n");
  getchar();

  system("clear");

  /* Game Logic */  
  while(GAME) {

    while(SHOOT) {
      // WRITE
      getStatus(user);
      printf("Enter coordinates to shoot: ");
      scanf("%s", BUFFER);
      printf("\n");
      w_shoot(fd_game, BUFFER);

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
      system("clear");
    }
    
    sleep(1);

    while (RECIEVE && GAME) {
      // READ
      getStatus(user);
      lock(FULL);
      lock(MUTX);
      read(fd_game, BUFFER, sizeof(BUFFER));
      printf("%s\n", BUFFER);
      fflush(0);
      unlock(MUTX);
      unlock(EMPT);

      sleep(1);

      if(strcmp(BUFFER, "exit") == 0) {
        GAME = 0;
        strcpy(BUFFER, "exit");
      } else {
        strcpy(BUFFER, "MISS");
      }

      // WRITE
      w_shoot(fd_game, BUFFER);

      sleep(1);
      SHOOT = 1;
      RECIEVE = 0;
      system("clear");
    }

  }

  /* Deallocation */
  boardDestroy(user->board);
  userDestroy(user);
  close(fd_game);
  return 0;  
}

#include "v_utilities.h"

void end_program(const char *msg) {
  perror(msg);
  exit(1);
}

void lock(int sem_num) { 
  struct sembuf semb;

  semb.sem_num = sem_num;
  semb.sem_op = -1;
  semb.sem_flg = SEM_UNDO;
  if (semop(SEMID, &semb, 1) == -1) {
    end_program("semop lock");
  }

}

void unlock(int sem_num) {
  struct sembuf semb;

  semb.sem_num = sem_num;
  semb.sem_op = 1;
  semb.sem_flg = SEM_UNDO;
  if (semop(SEMID, &semb, 1) == -1) {
    end_program("semop unlock");
  }

}

void w_shoot(int fd, char *buf) {
    lock(EMPT);
    lock(MUTX);
    write(fd, buf, sizeof(BUFFER));
    unlock(MUTX);
    unlock(FULL);
}

int init_v_system(key_t key){

  int semid;
  union semun sop;
  unsigned short array[3];
  array[MUTX] = 1;
  array[FULL] = 0;
  array[EMPT] = sizeof(BUFFER);
  sop.array = array;
  // fprintf(stdout, "%d\n", sizeof(BUFFER));  

  if ((key = ftok(FILE_GAME, 'O')) == -1) { 
    end_program("ftok");
  }

  /* create a semaphore set with 1 semaphore: */
  if ((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1) {
    end_program("semget");
  }

  #ifdef DEBUG
  fprintf(stdout, "%d\n", semid);
  #endif

  /* initialize semaphore #0 to 1: */
  if (semctl(semid, 0, SETALL, sop) == -1) {
    end_program("semctl");
  }

  return semid;
}
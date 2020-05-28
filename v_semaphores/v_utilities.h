/**
 * @file utilities.h
 * @brief API for V Semaphore System 
 * @author Nikita Zhukov
 * @date 26.05.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef _UTILITIES_H
#define _UTILITIES_H

// #define DEBUG
// #define DEBUG_FILE_BOARD

#define FILE_SHOOT  "shoot.txt"
#define FILE_BOARD  "board.txt"

#define MODES O_RDWR | O_CREAT | O_TRUNC

// #define FILE_GAME FILE_SHOOT

/* Definition for set of semaphores */
enum {MUTX, FULL, EMPT};

/* Buffer for communication between two users */
char BUFFER[20];
char BUFFER_BOARD[200];

int SEMID;
int SEMID_B;

/**
 * @brief End program due to error
 * 
 * @param msg - comment about problem
 */ 
void end_program(const char *msg);

/**
 * @brief Lock semaphore
 * 
 * @param sem_num - number of semaphore in V Semaphore System 
 */
void lock(int semid, int sem_num);

/**
 * @brief Unlock semaphore
 * 
 * @param sem_num - number of semaphore in V Semaphore System 
 */
void unlock(int semid, int sem_num);

void w_shoot(int semid, int fd, char *buf);

/**
 * @brief Initiaization of V System
 * 
 * @param key - key derived from FILE
 * @return Id of set of semaphore
 */
int init_v_system(const char* f_name, int buffer_size);

#endif

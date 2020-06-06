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

#define _XOPEN_SOURCE 500

#ifndef _UTILITIES_H
#define _UTILITIES_H

// #define DEBUG
// #define DEBUG_FILE_BOARD

#define FILE_SHOOT  "shoot.txt"
#define FILE_BOARD  "board.txt"

#define MODES O_CREAT | O_RDWR | O_TRUNC

#define SLEEP usleep(4500)

/* Definition for set of semaphores */
enum {MUTX, FULL, EMPT};

/* Buffer for communication between two users */
char BUFFER[20];
char BUFFER_BOARD[300];

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
 * @param semid - id of semaphore set
 * @param sem_num - number of semaphore in V Semaphore System 
 */
void lock(int semid, int sem_num);

/**
 * @brief Unlock semaphore
 * 
 * @param semid - id of semaphore set
 * @param sem_num - number of semaphore in V Semaphore System 
 */
void unlock(int semid, int sem_num);

/**
 * @brief Shoot
 * API for function shoot in terms of V System
 * 
 * @param semid - id of semaphore set
 * @param fd - file descriptor to where shoot be written
 * @param buf - string with coordinates
 */ 
void w_shoot(int semid, int fd, char *buf);

/**
 * @brief Initiaization of V System
 * 
 * @param f_name - file name
 * @param buffer_size 
 * 
 * @return Id of set of semaphore
 */
int init_v_system(const char* f_name, int buffer_size);

#endif

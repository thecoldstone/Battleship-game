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
#define FILE_GAME     "game.txt"

/* Definition for set of semaphores */
enum {MUTX, FULL, EMPT};

/* Buffer for communication between two users */
char BUFFER[10];

int SEMID;

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
void lock(int sem_num);

/**
 * @brief Unlock semaphore
 * 
 * @param sem_num - number of semaphore in V Semaphore System 
 */
void unlock(int sem_num);

void w_shoot(int fd, char *buf);

void r_shoot(int fd, char *buf);

/**
 * @brief Initiaization of V System
 * 
 * @param key - key derived from FILE
 * @return Id of set of semaphore
 */
int init_v_system(key_t key);

#endif

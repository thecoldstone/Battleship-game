#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t *mutex; 
  
void thread(void* arg) 
{ 
    //wait 
    sem_wait(mutex); 

    printf("\nEntered..\n"); 
  
    //critical section 
    sleep(4); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(mutex); 

} 
  
int main() 
{ 
    mutex = sem_open("/semaphore", O_CREAT, 0644, 1); 
    pthread_t t1,t2;    
    pthread_create(&t1,NULL,(void*)thread,NULL); 
    sleep(2); 
    pthread_create(&t2,NULL,(void*)thread,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_close(mutex);
    sem_unlink("/semaphore"); 
    return 0; 
} 
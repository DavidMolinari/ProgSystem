#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

sem_t *ptsema;
void * fonction(){
  printf("Fils - Posix TID : %ld\n",pthread_self() );
  sleep(1);


  sem_wait(ptsema);
  printf("Debut thread\n" );
  sleep(10);
  printf("fin Thread\n" );
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){

  ptsema = sem_open("/meh", O_CREAT, 0600, 0);
  pthread_t threads[2];
  pthread_create(&threads[0], NULL, fonction, NULL);
  pthread_create(&threads[1], NULL, fonction, NULL);
  printf("Thread Père Posix TID : %ld\n",pthread_self());
  sleep(5);
  sem_post(ptsema);
  sleep(2);
  sem_post(ptsema);

  for (int i = 0; i < 2; i++)
    pthread_join(threads[i], NULL);

  sem_close(ptsema);
  system("ls -l /dev/shm");
  sem_unlink("/meh");
  exit(0);
}

#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

void * libere();
void * fonction();

int main(int argc, char* argv[]){

  pthread_t threads[2];
  pthread_create(&threads[0], NULL, fonction, NULL);
  pthread_create(&threads[1], NULL, fonction, NULL);
  printf("Thread pere - PId : %d, Posix TID : %ld\n",getpid(), pthread_self());
  sleep(5);
  pthread_cancel(threads[0]);

  for (int i = 0; i < 2; i++)
    pthread_join(threads[i], NULL);

  exit(0);
}


void * libere(){
  printf("OK\n");
  return(NULL);
}

void * fonction(){
  pthread_cleanup_push((void *)libere, NULL);
  printf("Thread pere - PId : %d, Posix TID : %ld\n",getpid(), pthread_self());
  sleep(20);
  pthread_cleanup_pop(1);
  pthread_exit(NULL);
}

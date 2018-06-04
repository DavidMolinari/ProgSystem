#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

void * fonction();

int main(int argc, char* argv[]){

  pthread_t threads[2];
  pthread_create(&threads[0], NULL, fonction, NULL);
  pthread_create(&threads[1], NULL, fonction, NULL);
  printf("Thread Père PID : %d, Linux TID : %ld,  Posix TID : %ld\n",getpid(), syscall(SYS_gettid),pthread_self());
  sleep(10);
  pthread_cancel(threads[0]);

  for (int i = 0; i < 2; i++)
    pthread_join(threads[i], NULL);

  exit(0);
}



void * fonction(){
  printf("Je suis un Thread ... \n");
  printf("Thread PID : %d, Linux TID : %ld,  Posix TID : %ld\n",getpid(), syscall(SYS_gettid),pthread_self());
  exit(0);
}

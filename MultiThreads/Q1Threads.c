#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>




void* th(void *arg){
  printf("thr : %d , proc : %d\n",pthread_self(), getpid() );
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
  pthread_t id1, id2;
  pthread_create(&id1, NULL, th, NULL);
  pthread_create(&id2, NULL, th, NULL);
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
  printf("fin th principal %d => Processus %d\n",pthread_self(), getpid() );
  pthread_exit(NULL);

  }

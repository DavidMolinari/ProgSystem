#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>




void* th(void *arg){
  printf("thr : %d \n",pthread_self() );
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
  pthread_t thr;
  int nb = 1000;
  for (int i = 0; i < nb; i++) {
    printf("th nb %d ",i );
    sleep(0.5);
    pthread_create(&thr, NULL, th, NULL);
  }
}

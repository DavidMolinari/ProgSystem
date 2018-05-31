#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;
phthread_con_t cond;
int v = 0;

void* th(void *arg){
  pthread_mutex_lock(&mut);
  sleep(2);
  //printf("ID_FILLE=%d\n",pthread_self());
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}

void* inc(void *arg){
  pthread_mutex_lock(&mut);
  v++;
  printf("V++\n");
  sleep(1);
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}

void* in(void * arg){
  for (int i = 0; i < 4; i++) {
    sleep(1);
    v++;
    printf("v++\n");
  }
}

int main(int argc, char* argv[]){
  pthread_t thr;
  for (int i = 0; i < 2; i++) {
    pthread_mutex_lock(&mut);
    printf("i = %d\n",i );
    pthread_create(&thr, NULL, in, NULL);
    pthread_mutex_unlock(&mut);
    sleep(5);
    pthread_join(thr, NULL);
  }
  printf("v = %d\n",v );
  //pthread_create(&thr, NULL, in, NULL);
  /*
    while(cond)
      __wait libere mutex
    unlock
  */

}

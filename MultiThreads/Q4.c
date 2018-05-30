#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;
int v = 0;

void* th(void *arg){
  pthread_mutex_lock(&mut);
  sleep(2);
  printf("ID_FILLE=%d\n",pthread_self());
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

int main(int argc, char* argv[]){
  pthread_t thr;
    for (int i = 0; i < 2; i++) {
      pthread_mutex_lock(&mut);
      printf("%d\n",i );
      pthread_create(&thr, NULL, inc, NULL);
      pthread_mutex_unlock(&mut);
      pthread_join(thr, NULL);
  }
  printf("v = %d\n",v );

}

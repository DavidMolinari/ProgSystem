#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;
pthread_cond_t cond;
int v = 0;

void* inc(void *arg){
  pthread_mutex_lock(&mut);
  v++;
  printf("V++\n");
  sleep(1);
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}


void * incv2(void * arg){

  /*
  Exemple cours :
  Lock Mutex
  if condition vraie
  Fait qqchose
  Envoi Signal (&cond)
  Unlock mutex
  */
  for (int i = 0; i < 4; i++) {
    pthread_mutex_lock(&mut);
    if(v < 3) {
      printf("v++ done\n");
      v++;
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mut);
  }
}

int main(int argc, char* argv[]){
  /*
  Exemple cours :
  while(condition inverse)
  __WAIT
  unlock mutex
  */
  pthread_t threads[2];
  for( int t=0; t<2; t++ )
    pthread_create( &threads[t], NULL, incv2, NULL );
  pthread_mutex_lock(&mut);
  while (v < 2)
    pthread_cond_wait( &cond, &mut );
  printf("v=%d\n", v);
  pthread_mutex_unlock(&mut);


}

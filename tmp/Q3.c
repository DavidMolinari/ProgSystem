#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;

void* th(void *arg){
  pthread_mutex_lock(&mut);
  sleep(2);
  printf("ID_FILLE=%d\n",pthread_self());
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
  pthread_t idt[3];
  pthread_mutex_init(&mut); // ne pas oublier
  pthread_mutex_lock(&mut);
  for (int i = 0; i < 3; i++)
    pthread_create(&idt[i], NULL, th, NULL);
  sleep(3);

  pthread_mutex_unlock(&mut);
  printf("fin thr principal\n");
  pthread_exit(NULL);

}

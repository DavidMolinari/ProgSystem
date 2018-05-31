#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;
void *res;

void* th(void *arg){
  int *valret;
  valret = (int*)malloc(sizeof(int));
  printf("IdFille => %d\n",(int)pthread_self());
  sleep(2);
  *valret=(int)pthread_self();
  pthread_exit((void *)valret);
}

int main(int argc, char* argv[]){
  pthread_t idt;
  int *returnValue;
  for (int i = 0; i < 3; i++) {
    pthread_create(&idt, NULL, th, NULL);
    pthread_join( idt, (void **)&returnValue);
    printf("PapaIdFille> %d\n",  *returnValue);
    free(returnValue);
  }
  printf("fin thr principal\n");
  pthread_exit(NULL); // tue le thread
}

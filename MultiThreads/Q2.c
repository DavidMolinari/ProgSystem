#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#define handle_error_en(en, msg) \
do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
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

  pthread_t threads[2];
  for( int t=0; t<2; t++ ){
    int s;
    if( s = pthread_create(&threads[t], NULL, th, NULL)== 0){
      pthread_join( threads[t], (void **)&returnValue);
      printf("PapaIdFille> %d\n",  *returnValue);
      free(returnValue);
    } else handle_error_en(s, "pthread_create");
  }
  printf("fin thr principal\n");
  pthread_exit(NULL); // tue le thread
  //pthread_exit(0); Kill processus, sons => zombies
}

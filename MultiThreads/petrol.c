#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

int val;

void* readVal();

int main(int argc, char* argv[]){
  pthread_t threads[8];
  pthread_create(&threads[0], NULL, readVal, NULL); // first thread lit val
  pthread_join(threads[0], NULL);


}

void* readVal(){
  scanf("%d\n", &val);
  printf("Valeur à transformer : [%d]\n",val);
}


int modulo(int n){
    if((n%2) == 1) return 1;
    else return 0;
}

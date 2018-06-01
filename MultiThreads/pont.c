#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


sem_t mut;
/* charge max du point */
#define CHARGEMAX 15
/* Poids Camion */
#define PC 15
/* Poids voiture */
#define PV 5



 void TODO(){};


int main(int argc, char* argv[]){

  /* semaphore / Non partagé par les fork /  Valeur de départ */
  sem_init(&mut,0,CHARGEMAX);

  /* TODO */
  // pthread_t threads[3];
  // pthread_create(&threads[0], NULL, TODO, NULL);
  // pthread_create(&threads[1], NULL, TODO, NULL);
  // pthread_create(&threads[2], NULL, TODO, NULL);
  // for (int i = 0; i < 3; i++) {
    // pthread_join(threads[i], NULL);
  // }

  return 0;
}

/* v = poids */
void enterPont(int v){
if(v <= CHARGEMAX){
  for (int i = 0; i < v; i++) { sem_post(&mut);}
}



}
void ex(){
  sem_wait(&mut);
  printf("Meh\n");
  sem_post(&mut);
}

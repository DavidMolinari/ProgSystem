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

void* traverseeCamion();
void* traverseeVoiture();
void attendre(double max);
void enterPont(int v);
void exitPont(int v);



pthread_mutex_t crit;


int main(int argc, char* argv[]){

  /* semaphore / Non partagé par les fork /  Valeur de départ */
  sem_init(&mut,0,CHARGEMAX);

  /* TODO */
  pthread_t threads[7];
  pthread_create(&threads[0], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[1], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[2], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[3], NULL, traverseeCamion, NULL);
  pthread_create(&threads[4], NULL, traverseeCamion, NULL);
  pthread_create(&threads[5], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[6], NULL, traverseeVoiture, NULL);
  for (int i = 0; i < 7; i++)
    pthread_join(threads[i], NULL);
  return 0;
}


void* traverseeVoiture(){
  enterPont(5);
    attendre(5);
  exitPont(5);
  pthread_exit(NULL);

}

void* traverseeCamion(){
  enterPont(15);
    attendre(4);
  exitPont(15);
  pthread_exit(NULL);

}


/*
  v =  Poids
*/
void enterPont(int v){
  if(v == PV){
    for (int i = 0; i < PV; i++)  sem_wait(&mut); // Décrémente voiture
    printf("traversee Voiture : %d\n", (int)pthread_self());
  } else {
    pthread_mutex_lock(&crit);
    for (int i = 0; i < PC; i++)  sem_wait(&mut); // Décrémente camion
    pthread_mutex_unlock(&crit);
    printf("traversee Camion : %d\n", (int)pthread_self());
  }
}

/*
  v =  Poids
*/
void exitPont(int v){
  if(v == PV){
    for (int i = 0; i < PV; i++)  sem_post(&mut); // Incrémente voiture
    printf("Fin traversee Voiture : %d\n", (int)pthread_self());
  } else {
    for (int i = 0; i < PC; i++)  sem_post(&mut);// Incrémente Camion
    printf("Fin traversee Camion: %d\n", (int)pthread_self());
  }
}


int tirage_aleatoire(double max)
{
        int j=(int) (max*rand()/(RAND_MAX+1.0));
        if(j<1)
                j=1;
        return j;
}

void attendre(double max)
{
        struct timespec delai;
        delai.tv_sec=tirage_aleatoire(max);
        delai.tv_nsec=0;
        nanosleep(&delai,NULL);
}

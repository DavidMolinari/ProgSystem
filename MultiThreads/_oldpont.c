#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define couleur(param) printf("\033[%sm",param)

sem_t mut;
/* charge max du point */
#define CHARGEMAX 3
/* Poids Camion */
#define PC 3
/* Poids voiture */
#define PV 1

void* traverseeCamion();
void* traverseeVoiture();
void attendre(double max);
void enterPont(int v);
void exitPont(int v);

pthread_mutex_t crit;


int main(int argc, char* argv[]){


  /* semaphore / Non partagé par les fork /  Valeur de départ */
  sem_init(&mut,0,CHARGEMAX);

  pthread_mutex_init(&crit, NULL);
  /* TODO */
  pthread_t threads[7];



  pthread_create(&threads[0], NULL, traverseeCamion, NULL);
  pthread_create(&threads[1], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[2], NULL, traverseeCamion, NULL);
  pthread_create(&threads[3], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[4], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[5], NULL, traverseeVoiture, NULL);
  pthread_create(&threads[6], NULL, traverseeVoiture, NULL);
  for (int i = 0; i < 7; i++)
    pthread_join(threads[i], NULL);
  return 0;

}


void* traverseeVoiture(){
  enterPont(PV);
    attendre(3);
  exitPont(PV);
  pthread_exit(NULL);

}

void* traverseeCamion(){
  enterPont(PC);
    attendre(2);
  exitPont(PC);
  pthread_exit(NULL);

}


/*void attendre(double max)

  v =  Poids
*/
void enterPont(int v){

  printf("222\n");
  pthread_mutex_lock(&crit);
  printf("==%d\n", v);
  if(v == PV){

    sem_wait(&mut); // Décrémente voiture
    // pthread_mutex_unlock(&crit);
    printf("traversee Voiture : %d\n", (int)pthread_self());
  } else {
    // pthread_mutex_lock(&crit);
    for (int i = 0; i < PC; i++)  {
      sem_wait(&mut); // Décrémente camion
    }
    printf("traversee Camion : %d\n", (int)pthread_self());
  }
  pthread_mutex_unlock(&crit);
  printf("fdsfdsfs\n");
}

/*
  v =  Poids
*/
void exitPont(int v){
  pthread_mutex_lock(&crit);
  printf(" exit ==%d\n", v);
  if(v == PV){
      sem_post(&mut); // Incrémente voiture
    printf("____________Fin traversee Voiture : %d\n", (int)pthread_self());
  } else {
    for (int i = 0; i < PC; i++)  {
      sem_post(&mut);// Incrémente Camion
    }
    printf("____________Fin traversee Camion: %d\n", (int)pthread_self());
  }
  pthread_mutex_unlock(&crit);
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

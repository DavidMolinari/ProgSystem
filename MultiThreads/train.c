
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


/* Les villes */
#define A 0
#define B 1
#define C 2
#define D 3

/* 3 sections critiques , 3 mutex  */
pthread_mutex_t AB;
pthread_mutex_t BC;
pthread_mutex_t DB;


/* Code des threads */
void* train_de_A_vers_C(void* arg);
void* train_de_D_vers_A(void* arg);

int tirage_aleatoire(double max);
void attendre(double max);

/* Moniteur : gestion du chemin de fer  */
void utiliser_le_segment(int ville_depart, int ville_arrivee){
  if(ville_depart == A)
    pthread_mutex_lock(&AB);
  if(ville_depart == B && ville_arrivee == C)
    pthread_mutex_lock(&BC);
  if(ville_depart == B && ville_arrivee == D)
    pthread_mutex_lock(&DB);
  if(ville_depart == C)
    pthread_mutex_lock(&BC);
  if(ville_depart == D)
    pthread_mutex_lock(&DB);
}

void liberer_le_segment(int ville_depart, int ville_arrivee)
{
  if(ville_depart == A)
    pthread_mutex_unlock(&AB);
  if(ville_depart == B && ville_arrivee == C)
    pthread_mutex_unlock(&BC);
  if(ville_depart == B && ville_arrivee == D)
    pthread_mutex_unlock(&DB);
  if(ville_depart == C)
    pthread_mutex_unlock(&BC);
  if(ville_depart == D)
    pthread_mutex_unlock(&DB);
}


int main(int argc, char* argv[])
{
  pthread_t threads[3];

  pthread_create(&threads[0], NULL, train_de_A_vers_C, NULL);
  pthread_create(&threads[1], NULL, train_de_D_vers_A, NULL);
  pthread_create(&threads[2], NULL, train_de_A_vers_C, NULL);
  for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
  }

}


void* train_de_A_vers_C(void* arg)
{
	utiliser_le_segment(A, B);
	printf("Train %d : utilise segment AB \n",(int)pthread_self());
	attendre(6);
	liberer_le_segment(A, B);

	utiliser_le_segment(B, C);
	printf("Train %d : utilise segment BC \n",(int)pthread_self());
	attendre(6);
	liberer_le_segment(B, C);

	pthread_exit(NULL);
}

void* train_de_D_vers_A(void* arg)
{

	utiliser_le_segment(D, B);
	printf("Train %d : utilise segment DB \n",(int)pthread_self());
	attendre(5);
	liberer_le_segment(D, B);

	utiliser_le_segment(A, B);
	printf("Train %d : utilise segment BA \n",(int)pthread_self());
	attendre(5);
	liberer_le_segment(A, B);

	pthread_exit(NULL);
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

/********************************************************
 * An example source module to accompany...
 *
 * "Using POSIX Threads: Programming with Pthreads"
 *     by Brad nichols, Dick Buttlar, Jackie Farrell
 *     O'Reilly & Associates, Inc.
 *
 ********************************************************
 *
 * cvsimple1.c
 * adapt� et modifi� F. Touchard
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#define NB_THREADS  3
#define NB_INCR 4
#define SEUIL 3

int     compte = 0;
int     thread_ids[3] = {0,1,2};
pthread_mutex_t verrou_compte=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_seuil=PTHREAD_COND_INITIALIZER;
struct timespec timeToWait;
struct timeval now;

void *incremente_compte(void *idp)
{
  // if(idp == (void *)&thread_ids[0]) sleep(5);

  // while(compte <= SEUIL){

  int *my_id = idp;
  int i;

  if(idp == (void *)&thread_ids[1]) sleep(5);
  for (i=0; i<NB_INCR; i++) {
    pthread_mutex_lock(&verrou_compte);
    compte++;
    printf("incremente_compte() : thread %d, compte = %d\n",
	   *my_id, compte);
    if (compte == SEUIL) {
      printf("incremente_compte() : Thread %d, compte %d, signale condition\n", *my_id, compte);
      pthread_cond_signal(&condition_seuil);
      // return(NULL);
    }
    pthread_mutex_unlock(&verrou_compte);
  }

  return(NULL);
}
// }

void *attente_seuil(void *idp)
{

  int rc;
  struct timespec ts;
  struct timeval    tp;
  int TIMETOWAIT = 2;

  rc =  gettimeofday(&tp, NULL);
      ts.tv_sec  = tp.tv_sec;
      ts.tv_nsec = tp.tv_usec * 1000;
      ts.tv_sec += 2;

  int *my_id = idp;

  printf("idP Thread no 3 : %d\n",idp );
  printf("attente_seuil(): thread %d\n", *my_id);

  pthread_mutex_lock(&verrou_compte);

  // if (compte < SEUIL) {
    rc = pthread_cond_timedwait(&condition_seuil, &verrou_compte, &ts);
    // pthread_mutex_lock(&verrou_compte);
    // int rc = pthread_cond_timedwait(&condition_seuil, &verrou_compte, &timeToWait);
    if (rc == ETIMEDOUT)
      printf("TIME OUT =>  %d secondes dépassées!\n", TIMETOWAIT);


    printf ("attente_seuil() : attente signalisation de la condition\n");
    // pthread_cond_wait(&condition_seuil, &verrou_compte);
    printf("attente_seuil() : thread %d, compte %d condition recue\n", *my_id, compte);
  // }

  pthread_mutex_unlock(&verrou_compte);

  printf("attente_seuil(): fin du thread %d\n", *my_id);

  return(NULL);
}

main(void)
{
  int       i;
  pthread_t threads[3];

  pthread_create(&threads[0], NULL, incremente_compte, (void *)&thread_ids[0]);
  pthread_create(&threads[1], NULL, incremente_compte, (void *)&thread_ids[1]);
  pthread_create(&threads[2], NULL, attente_seuil, (void *)&thread_ids[2]);
  for (i = 0; i < NB_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

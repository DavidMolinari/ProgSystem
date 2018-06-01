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

#define NB_THREADS  3
#define NB_INCR 4
#define SEUIL 3

int     compte = 0;
int     thread_ids[3] = {0,1,2};
pthread_mutex_t verrou_compte=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_seuil=PTHREAD_COND_INITIALIZER;


void *incremente_compte(void *idp)
{
  int *my_id = idp;
  int i;
  if(idp == (void *)&thread_ids[0]) sleep(3);

  for (i=0; i<NB_INCR; i++) {
    pthread_mutex_lock(&verrou_compte);
    compte++;
    printf("incremente_compte() : thread %d, compte = %d\n",
	   *my_id, compte);
    if (compte == SEUIL) {
      printf("incremente_compte() : Thread %d, compte %d, signale condition\n", *my_id, compte);
      pthread_cond_signal(&condition_seuil);
    }
    pthread_mutex_unlock(&verrou_compte);
  }

  return(NULL);
}

/* Exemple
gettimeofday(&now);
timeout.tv_sec = now.tv_sec + 5;
timeout.tv_nsec = now.tv_usec * 1000;
retcode = 0;
while (x <= y && retcode != ETIMEDOUT) {
    retcode = pthread_cond_timedwait(&cond, &mut, &timeout);
}
if (retcode == ETIMEDOUT) {
  timeout
} else {
     agir sur x et y
}
pthread_mutex_unlock(&mut);
*/
void *attente_seuil(void *idp)
{
  int *my_id = idp;

  printf("attente_seuil(): thread %d\n", *my_id);

  pthread_mutex_lock(&verrou_compte);

  struct timeval now;
  struct timespec timeout;

  int rt;
  gettimeofday(&now,NULL);


  timeToWait.tv_sec = now.tv_sec+5;
  timeToWait.tv_nsec = (now.tv_usec+1000UL*300)*1000UL;


  while (rc != ETIMEDOUT) {
    printf ("attente_seuil() : attente signalisation de la condition\n");
    rc = pthread_cond_timedwait(&condition_seuil, &verrou_compte; &timeout);
    printf("attente_seuil() : thread %d, compte %d condition recue\n", *my_id, compte);
  }

  if(rc == ETIMEDOUT) printf("TIMED OUT\n");

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

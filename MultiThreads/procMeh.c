#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

sem_t *ptsema;
void * fonction(){
  printf("Fils - Posix TID : %ld\n",getpid() );
  sleep(1);
  sem_wait(ptsema);
  printf("Debut P\n" );
  sleep(10);
  printf("fin P\n" );
  exit(0);
}
int main(int argc, char* argv[]){

  ptsema = sem_open("/meh", O_CREAT, 0600, 0);
  pid_t retour;

  if((retour=fork()) == -1){perror("\nEchec de fork");exit(2);}
  if((retour=fork()) == -1){perror("\nEchec de fork");exit(2);}
  if(retour == 0)        fonction();
  printf("proc Père Posix TID : %ld\n",getpid());
  sleep(5);
  sem_post(ptsema);
  sleep(2);
  sem_post(ptsema);
  for (int i = 0; i < 2; i++) wait(NULL);
  sem_close(ptsema);
  system("ls -l /dev/shm");
  sem_unlink("/meh");
  exit(0);
}

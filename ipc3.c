#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/sem.h>
#include <string.h>
struct sigaction action;

int main(int argc, char *argv[]){
  key_t cle;
  struct sembuf operation;
  int semid;
  if(argc != 3){
    fprintf(stderr,"syntaxe!%s <ref_cle> <nbr>\n",argv[0] );
    exit(1);
  }

  if((cle = ftok(argv[1], atoi(argv[2]))) == -1){
    perror("problème de clé ! \n");
    exit(2);
  }

  // SEMAPHORE
  if((semid = semget(cle, 1, 0)) == -1){
    perror("ERROR ACCESS SEM");
    exit(1);
  }

  printf("T2 : attente du sémaphore, operation P \n");

  operation.sem_num = 0;
  operation.sem_op = -1;
  operation.sem_flg = 0;

  if(semop(semid, &operation, 1) == -1){
    perror("impossible de décrémenter le semaphore. \n");
    exit(3);
  }

  printf("T2 : Début section critique 5 secondes . . .  \n");
  sleep(10);
  printf("FIN T2\n");

  semctl(semid, 0, IPC_RMID);

  exit(0);
}

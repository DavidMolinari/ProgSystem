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
#define couleur(param) printf("\033[%sm",param)
#define max 10
int semid;


void fct_signalint(int sig){
  printf("SIGINT\n" );
  semctl(semid, 0, IPC_RMID);
  semctl(semid, 1, IPC_RMID);
}


int P(int semid, int ns){
  struct sembuf oper;
  oper.sem_num = ns;
  oper.sem_op = -1;
  oper.sem_flg = 0;

  if(semop(semid, &oper, 1) == -1){
    perror("\nImpossible de décrémenter le sémaphore !\n");
    exit(3);
  }
}

int V(int semid, int ns){
  struct sembuf oper;
  oper.sem_num = ns;
  oper.sem_op = 1;
  oper.sem_flg = 0;
  if(semop(semid, &oper, 1) == -1){
    perror("\nImpossible d'incrémenter le sémaphore !\n");
    exit(4);
  }
}

int main(int argc, char *argv[]){

int *tMax =  [4, 2, 1, 3, 6];
int *tDispo =  [1,1, 0, 1, 2];

  semctl(semid, 0, IPC_RMID);

  exit(0);


}

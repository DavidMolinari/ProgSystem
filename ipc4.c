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
    perror("\nImpossible de décrémenter le sémaphore !\n");
    exit(4);
  }
}

int main(int argc, char *argv[]){
  printf("Meeeeeeeeeeeeeeeh\n");

}

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
#define PHILO 5
int semid;
int mainPid;
void penser(int i){
  printf("%d pense.\n", i+1);
  sleep(rand()%10);
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

int PP(int semid, int ns, int ns2){
  struct sembuf oper[2];
  oper[0].sem_num = ns;
  oper[0].sem_op = -1;
  oper[0].sem_flg = 0;
  oper[1].sem_num = ns2;
  oper[1].sem_op = -1;
  oper[1].sem_flg = 0;
  if(semop(semid, oper, 1) == -1){
    perror("\nImpossible de décrémenter le sémaphore !\n");
    exit(3);
  }
}
int VV(int semid, int ns,  int ns2){
  struct sembuf oper[2];
  oper[0].sem_num = ns;
  oper[0].sem_op = 1;
  oper[0].sem_flg = 0;
  oper[1].sem_num = ns2;
  oper[1].sem_op = 1;
  oper[1].sem_flg = 0;
  if(semop(semid, oper, 1) == -1){
    perror("\nImpossible d'incrémenter le sémaphore !\n");
    exit(4);
  }
}



void manger(int philo){
  //printf("...PREND FOURCHETTES...\n");
  //P(semid, philo);
  //P(semid, (philo+1)%PHILO);
  PP(semid, philo, (philo+1)%PHILO);
  //printf("...COMMENCE A MANGER...\n");
  sleep(1+rand()%4);
  printf("NB FOURCHETTES : %d\n",semctl(semid, 0, GETVAL, 0)+semctl(semid, 1, GETVAL, 1)+semctl(semid, 3, GETVAL, 3)+@semctl(semid, 2, GETVAL, 2)+semctl(semid, 4, GETVAL, 4));
  printf("PHILOSOPHE NUM : %d MANGE\n",philo+1 );
  //printf("...A FINI DE MANGER...\n");
  //V(semid, philo);
  //V(semid, (philo+1)%PHILO);
  VV(semid, philo, (philo+1)%PHILO);
}
void philosophe(int numero){
  while(1){
    penser(numero);
    manger(numero);
  }
}



int main(int argc, char *argv[]){

  int i, val;
  mainPid = getpid();
  if((semid=semget(IPC_PRIVATE, PHILO, 0666)) == -1){
    exit(1);
    perror("\nErreur de création de sémaphores");
  }

  for ( i = 0; i < PHILO; i++) {
    semctl(semid, i , SETVAL, 1);
  }
  for ( i = 0; i < PHILO; i++) {
    if(fork() == 0) philosophe(i);
  }
  pause();


}

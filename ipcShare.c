#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
int *ptrv;
#define couleur(param) printf("\033[%sm",param)
int shmid;
int semid;
int *lect = 0;
#define NB 5


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
void lecteur(int i){
  while (1) {
    P(semid, 0);
    lect++;
    if((*lect) == 1) P(semid, 1);
    V(semid, 0);
    couleur("31");
    printf("Lecteur   [%d] Lit          : %d\n",i, *ptrv);
    sleep(2);
    P(semid, 0);
    lect--;
    if((*lect) == 0) V(semid, 1);
    V(semid, 0);
  }
}
void redacteur(int i){
  while (1) {
    P(semid, 2);
    P(semid, 1);
    (*ptrv)++;
    couleur("32");
    printf("Redacteur [%d] incrémente à : %d\n",i,*ptrv );
    V(semid, 1);
    V(semid, 2);
    sleep(2);
  }

}


int  main() {
  printf("meh\n");
  int i, status;
  pid_t retour;
  if((shmid = shmget(IPC_PRIVATE, sizeof(int), 0666)) == -1) {perror("SHMEH");exit(-1);}

  if((semid=semget(IPC_PRIVATE, 3, 0666)) == -1){exit(1);perror("\nErreur de création de sémaphores");}

  semctl(semid, 0 , SETVAL, 1);
  semctl(semid, 1 , SETVAL, 1);
  semctl(semid, 2 , SETVAL, 1);

  ptrv = (int *)shmat(shmid, NULL, 0);
  lect = (int *)shmat(shmid, NULL, 0);


  (*ptrv) = 0;
  (*lect) = 0;


  for (int i = 1; i <= NB; i++) {
    if((retour=fork()) == -1){ perror("\nEchec de fork");exit(2);}
    if(retour == 0){
      if(i < 3){ lecteur(i); exit(0);}
      else{ redacteur(i); exit(0);}
    }
  }
  for (int i = 1; i <=NB; i++) wait(&status);
  shmdt(ptrv);
  shmctl(shmid,IPC_RMID,0);
}

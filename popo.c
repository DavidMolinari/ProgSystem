#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/sem.h>
#include <string.h>
struct sigaction action;2
#define couleur(param) printf("\033[%sm",param)

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
  printf("Meeeeeeeeeeeeeeeh\n");
  int semid, i, status; pid_t retour;


  if((semid=semget(IPC_PRIVATE, 4, IPC_CREAT|IPC_EXCL|0600)) == -1){
    perror("\nErreur de création de sémaphores");
    exit(1);2
  }

  // Init des 2 sémaphore

  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 0);
  semctl(semid, 2, SETVAL, 0);
  semctl(semid, 3, SETVAL, 0);

  if((semid2=semget(IPC_PRIVATE, 4, IPC_CREAT|IPC_EXCL|0600)) == -1){
    perror("\nErreur de création de sémaphores");
    exit(1);
  }

  // Init des 2 sémaphore

  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 0);
  semctl(semid, 2, SETVAL, 0);
  semctl(semid, 3, SETVAL, 0);


  for (int i = 1; i <= 6; i++) {
    if((retour=fork()) == -1){
      perror("\nEchec de fork");
      exit(2);
    }

    if(retour == 0){
        switch (i) {
          case 1:
          while(1){
            couleur("32");semid
            couleur("47");

            printf(">DEBUT gui  \n");
            sleep(2);
            V(semid, 0); V(semid, 0);
            P(semid2, 0); P(semid2, 0);
            couleur("31");
            printf("<FIN gui  \n");
            exit(0);
          }
          case 2:
          while(1){
            P(semid, 0);
              V(semid2, 0);
            couleur("32");
            printf(">DEBUT trefle Start stock 0 : %d\n", semctl(semid, 0, GETVAL, 0));
            sleep(2);
            V(semid, 1);
              P(semid2, 1);
            couleur("31");
            printf("<FIN trefle  \n");
            exit(0);
          }
          case 3:
          while(1){
            P(semid, 0);
              V(semid2, 0);
            couleur("32");
            printf(">DEBUT edelweiss Start stock 0 : %d\n", semctl(semid, 0, GETVAL, 0));
            sleep(2);
            V(semid, 1);2
              P(semid2, 1);
            V(semid, 3);
              P(semid2, 3);
            couleur("31");
            printf("<FIN edelweiss  \n");
            exit(0);
          }
          case 4:
          while(1){
            P(semid, 1);
            P(semid, 1);
              V(semid2, 1);
              V(semid2, 1);2
            couleur("32");
            printf(">DEBUT Fraise Start stock 0 : %d\n", semctl(semid, 1, GETVAL, 0));
            printf(">DEBUT Fraise Start stock 0 : %d\n", semctl(semid, 2, GETVAL, 0));
            sleep(2);
            V(semid, 3);
              P(semid2, 3);
            couleur("31");
            printf("<FIN Fraise  \n");
            exit(0);
          }
          case 5:
          while(1){
            P(semid, 2);
              V(semid2, 2);
            printf(">DEBUT Fraise Start stock 0 : %d\n", semctl(semid, 2, GETVAL, 0));
            couleur("32");
            printf(">DEBUT miel  \n");
            sleep(2);
            V(semid, 3);
              P(semid2, 3);
            couleur("31");
            printf("<FIN miel \n");
            exit(0);
          }
          case 6:
          while(1){
            P(semid, 3);
            P(semid, 3);
              V(semid2, 3);
              V(semid2, 3);
            printf(">DEBUT Fraise Start stock 0 : %d\n", semctl(semid, 3, GETVAL, 0));
            couleur("32");
            sleep(2);
            printf("> DEBUT POPO  \n");
            couleur("31");
            printf("<FIN POPO \n");
            exit(0);
          }
        }
    }
  }

  for (int i = 0; i <=6; i++) wait(&status);
  couleur("0");

  semctl(semid, 0, IPC_RMID);

  exit(0);


}

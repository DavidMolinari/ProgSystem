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


  if((semid=semget(IPC_PRIVATE, 2, IPC_CREAT|IPC_EXCL|0600)) == -1){
    perror("\nErreur de création de sémaphores");
    exit(1);
  }

  // Init des 2 sémaphore

  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 0);


  for (int i = 1; i <= 5; i++) {
    if((retour=fork()) == -1){
      perror("\nEchec de fork");
      exit(2);
    }
    if(retour == 0){
      switch (i) {
        case 1:
          couleur("32");
          printf(">DEBUT DE T1  \n");
          sleep(3);
          V(semid, 0); V(semid, 0); V(semid, 0); 
          couleur("31");
          printf("<FIN DE T1  \n");
          exit(0);
        case 2:
          P(semid, 0);
          couleur("32");
          printf(">DEBUT DE T2  \n");
          sleep(20);
          V(semid, 1);
          couleur("31");
          printf("<FIN DE T2  \n");
          exit(0);
        case 3:
          P(semid, 0);
          couleur("32");
          printf(">DEBUT DE T3  \n");
          sleep(1);
          V(semid, 1);
          couleur("31");
          printf("<FIN DE T3  \n");
          exit(0);
        case 4:
          P(semid, 0);
          V(semid, 1);
          couleur("32");
          printf(">DEBUT DE T4  \n");
          sleep(2);
          couleur("31");
          printf("<FIN DE T4  \n");
          exit(0);
        case 5:
            P(semid, 1);
            P(semid, 1);
            P(semid, 1);
            couleur("32");
            printf(">DEBUT DE T5  \n");
            sleep(2);
            couleur("31");
            printf("<FIN DE T5  \n");
            exit(0);
      }
    }
  }

  for (int i = 0; i <=5; i++) wait(&status);
  couleur("0");

  semctl(semid, 0, IPC_RMID);

  exit(0);


}

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

  sigset_t ens1; int sig;

  sigemptyset(&ens1);
  sigaddset(&ens1, SIGINT);
  sigaddset(&ens1, SIGQUIT);
  sigaddset(&ens1, SIGUSR1);
  sigprocmask(SIG_SETMASK, &ens1, NULL);


  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 10);

  for (int i = 1; i <= 2; i++) {
    if((retour=fork()) == -1){
      perror("\nEchec de fork");
      exit(2);
    }
    if(retour == 0){
      switch (i) {
        case 1:
        while(1){
          couleur("32");
          printf("> [ Producteur ]                              START \n");
          sleep(1);
          P(semid, 1);
          V(semid, 0);
          char m = "▀";
          printf("STOCK : " );
          for (int i = 1; i <=semctl(semid, 0, GETVAL, 0); i++) printf("▀ ");
          printf("=> %d \n> [ Producteur ]                              STOP \n", semctl(semid, 0, GETVAL, 0));
        }
        case 2:
        while(1){
          couleur("31");
          printf("> [ Consommateur ]                            START \n");
          P(semid, 0);
          V(semid, 1);
          sleep(3);
          printf("STOCK : " );
          for (int i = 1; i <=semctl(semid, 0, GETVAL, 0); i++) printf("▀ ");
          printf("=> %d \n> [ Consommateur ]                            STOP \n", semctl(semid, 0, GETVAL, 0));

        }
      }
    }
  }

  for (int i = 1; i <=2; i++) wait(&status);
  couleur("0");

  semctl(semid, 0, IPC_RMID);

  exit(0);


}

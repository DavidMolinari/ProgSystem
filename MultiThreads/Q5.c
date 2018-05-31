#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  sigset_t ens1, ens2; int sig;

  pid_t pid, pidfils;
  int retour;
  switch (pid = fork()) {
    case (pid_t)-1:
      perror("NAUFRAGE . . .");
      exit(2);
    case (pid_t) 0:
    sigemptyset(&ens1);
    sigaddset(&ens1, SIGINT);
    sigaddset(&ens1, SIGQUIT);
    sigaddset(&ens1, SIGUSR1);
    sigprocmask(SIG_SETMASK, &ens1, NULL);
    sleep(30);
    sigpending(&ens2);
    printf("\nSignaux pendants : \n");
    for (size_t i = 1; i < NSIG; i++)
      if(sigismember(&ens2, i)) printf("%d\n",i);

    sigemptyset(&ens1);
    printf("Deblocage !\n");
    sigprocmask(SIG_SETMASK, &ens1, NULL);
    default:
    while(1){
      pidfils = wait(&retour);
      kill(pidfils, SIGUSR1);
    }
      // pidfils = wait(&retour);
      // printf("MORT DU FILS PID=%d\n",pidfils);
  }
  if(WIFEXITED(retour)) { printf("Retour : %d\n",WEXITSTATUS(retour) ); exit(0);}
  if(WIFSIGNALED(retour)) { printf("Kill : %d\n",WTERMSIG(retour) ); exit(0);}


  }

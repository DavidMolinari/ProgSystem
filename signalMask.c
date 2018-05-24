#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){

  sigset_t ens1, ens2; int sig;

  sigemptyset(&ens1);
  sigaddset(&ens1, SIGINT);
  sigaddset(&ens1, SIGQUIT);
  sigaddset(&ens1, SIGUSR1);
  sigprocmask(SIG_SETMASK, &ens1, NULL);
  printf("Masque pendant 30s\n");
  sleep(30);
  sigpending(&ens2);
  printf("\nSignaux pendants : \n");
  for (size_t i = 1; i < NSIG; i++)
    if(sigismember(&ens2, i)) printf("%d\n",i);

  sigemptyset(&ens1);
  printf("Deblocage !\n");
  sigprocmask(SIG_SETMASK, &ens1, NULL);
  sleep(15);
  printf("THE END\n");
  exit(0);
}

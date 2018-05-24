#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


sigset_t ens;
struct sigaction action;

void handler(int sig){
  int i ;
  printf("Entrée dans le handler\n");
  printf("Avec le signal %d\n", sig);
  sigprocmask(SIG_BLOCK, NULL, &ens);
  printf("Signaux masqués :");
  for (int i = 1; i < NSIG; i++)
    if(sigismember(&ens, i)) printf("%d\n",i );

  putchar('\n');

  if(sig == SIGINT){
    action.sa_handler=SIG_DFL;
    sigaction(SIGINT, &action, NULL);
  }
  printf("OUT\n");
  }


int main(){

  action.sa_handler = handler;
  action.sa_flags = 0;
  sigemptyset(&action.sa_mask);
  sigaction(SIGQUIT, &action, NULL);

  sigaddset(&action.sa_mask, SIGQUIT);
  sigaction(SIGINT, &action, NULL);

  while(1) sleep(1);

}

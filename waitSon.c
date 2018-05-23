#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  pid_t pid, pidfils;
  int retour;
  switch (pid = fork()) {
    case (pid_t)-1:
      perror("NAUFRAGE . . .");
      exit(2);
    case (pid_t) 0:
      printf("PROCESSUS FILS PID=%d\n",getpid());
      sleep(5);
      exit(33);
    default:
      pidfils = wait(&retour);
      printf("MORT DU FILS PID=%d\n",pidfils);
  }
  if(WIFEXITED(retour)) { printf("Retour : %d\n",WEXITSTATUS(retour) ); exit(0);}
  if(WIFSIGNALED(retour)) { printf("Kill : %d\n",WTERMSIG(retour) ); exit(0);}


  }

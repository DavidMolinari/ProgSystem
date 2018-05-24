#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
struct sigaction action;

int main(){

  action.sa_handler = SIG_IGN;
  action.sa_fags = 0;
  sigemptyset(&action.sa_mask);
  sigaction(SIGCHLD, &action, NULL);

  pid_t pid, pidBis;
  int status;
  switch (pid = fork()) {
    case (pid_t) 0:
      while(1) sleep(1);
    default:
      printf("PID TO KILL%d\n",pid );
      sleep(20);
      if(kill(pid, 0) == -1){
        printf("Processus fils %d inexistant\n", pid);
        exit(1);
      }else {
        printf("ENVOIE DE SIGUSR1 A %d\n", pid);
        kill(pid, SIGUSR1);
      }
    //pidBis = wait(&status);
    printf("KILLED MY SON %d - status = %d\n",pidBis, status );
  }
exit(0);
}

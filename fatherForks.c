#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
  int dad = 0, status; // papa
  for (int i = 0; i < 1000; i++) {
    if(dad == 0){
      dad = fork();
      if(dad == 0) dad = 1; else dad = 0;
      if(dad == 0) wait(&status);
      else
      printf("PROCESSUS : %d PID=%d - CREE PAR LE PAPA: %d\n",i+1,getpid(), getppid());
    }
  }
  return -1;
}

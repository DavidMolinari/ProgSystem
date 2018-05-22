#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int dad = 0, status; // papa
  for (int i = 0; i < 5; i++) {
    if(dad == 0){
      dad = fork();
      if(dad == 0) dad = 1; else dad = 0;
      if(dad == 0) wait(&status);
      else 
       printf("%d - %d\n",getpid(), getppid());
    }
  }
}

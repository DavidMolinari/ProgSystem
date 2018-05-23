#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

  int ret, a = 17, status;
  ret = fork();
  int pid = getpid();


  if(ret != 0) {
    while(1){
      printf("Je suis le père : %d\n",a);
      printf("pid papa : %d\n",pid);
      a = 0;
      wait(&status);
    }
  } else {
    while(1) {
      sleep(1);
      printf("Je suis le fils : %d\n",a );
      printf("pid fils : %d\n",pid );
    }
  }
}

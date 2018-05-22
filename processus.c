#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){

  int ret, a = 17;
  ret = fork();
  int pid = getpid();

  if(ret != 0) {
    printf("Je suis le père : %d\n",a);
    printf("pid papa : %d\n",pid);

    a = 0;
  } else {
    printf("Je suis le fils : %d\n",a );
    printf("pid fils : %d\n",pid );
  }

}

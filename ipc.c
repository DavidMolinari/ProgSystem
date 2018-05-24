#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
struct sigaction action;

int main(){
  key_t cle;
  struct sembuf operation;
  int semid;
  if(argc != 3){
    fprintf(stderr,"syntaxe!%s <ref_cle> <nbr>\n",argv[0] );
    exit(1);
  }

  if((cle = ftok(argv[1], atoi(argv[2]))) == -1){
    perror("problème de clé ! \n");
    exit(2)
  }

  exit(0);
}

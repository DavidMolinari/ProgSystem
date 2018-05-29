#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct sigaction action;

int  main() {
  key_t key; int flag, id; char *buf;
  flag=0;
  if((key = ftok("/tmp/maclef",12)) == -1) {
    perror("Probleme de cle ");
    exit(2);
  }

  if ((id=shmget(key,512,flag))<0) exit(1);
  if ((buf=shmat(id,0,0))<0)       exit(2);
  printf("Contenu : %s \n", buf);
  shmdt(buf);
  shmctl(id,IPC_RMID,0);
  exit(0);
}

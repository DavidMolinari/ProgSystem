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

int main(){
  key_t key; int flag, id; char *buf;

  flag=IPC_CREAT|0600;
  
  if((key = ftok("/tmp/maclef", 12)) == -1){
    perror("problème de clé ! \n");
    exit(2);
  }

  if((id=shmget(key, 512, flag)) < 0) exit(1);
  if((buf=shmat(id, 0, 0)) < 0) exit(2);
  strcpy(buf, "Bonjour");
  sleep(50);
  shmdt(buf);
  exit(0);
}

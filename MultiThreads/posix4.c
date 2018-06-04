#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void erreur(char * message) {
  perror(message);
  exit(1);
}

int main() {
  pid_t fils;
  int fdmq;
  fdmq=mq_open("/mamq",O_CREAT|O_RDWR,0600,NULL);
  if(fdmq==-1) erreur("mq_open ...");
  if((fils=fork())==-1) erreur("Fork ...");
  if(fils==0) {
    unsigned prio=0; char buffer[8192];
    sleep(10);
    if(mq_receive(fdmq,buffer,8192,&prio)==-1)
    erreur("mq_receive...");
    printf("Msg 1: %d- %s\n",prio,buffer);prio=0;
    if(mq_receive(fdmq,buffer,8192,&prio)==-1)
    erreur("mq_receive...");
    printf("Msg 1: %d- %s\n",prio,buffer);
    exit(0);
  }
  printf("Le pere envoi ...\n");
  if(mq_send(fdmq,"Bonjour ...",12, 5)==-1)
  erreur("mq_send...");
  if(mq_send(fdmq,"Urgent  ...",12,30)==-1)
  erreur("mq_send...");
  wait(NULL);
  mq_close(fdmq);
  system("ls -l /dev/mqueue");
  mq_unlink("/mamq");
  exit(0);
}

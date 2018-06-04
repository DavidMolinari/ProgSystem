#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>



sem_t *ptsema;
void * fonction(){
  printf("Fils - Posix TID : %ld\n",getpid() );
  sleep(1);
  sem_wait(ptsema);
  printf("Debut P\n" );
  sleep(10);
  printf("fin P\n" );
  exit(0);
}
int main(int argc, char* argv[]){

  pid_t fils;
  int fdmem;
  char * zone;
  fdmem = shm_open("/mymem", O_CREAT|O_RDWR, 0600);
  if(fdmem == -1) perror("shm_open ...");

  if(ftruncate(fdmem, 1024)==-1) perror("ftruncate ...");
  zone = mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fdmem, 0);
  if(zone == MAP_FAILED) perror("map ...");


  if((fils=fork()) == -1){perror("\nEchec de fork");exit(2);}
  if(fils == 0){
    sleep(10);
    printf("Zone : %s\n",zone );
    exit(0);
  }

  printf("Le père recopie\n" );
  strcpy(zone, "Bonjour . . . ");
  wait(NULL);
  close(fdmem);
  system("ls -l /dev/shm");
  sem_unlink("/mymem");
  exit(0);
}

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
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


int main(int argc, char* argv[]){

  // Open de la source arg1

  unsigned char* buf[50];
  int c = open(argv[1], O_RDONLY);
  // Open create
  int d = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0777);
  int s;
  while((s = read(c, buf, 50)) != 0){
    write(d, buf,s);
  }
  close(c);
  close(d);

  exit(0);

}

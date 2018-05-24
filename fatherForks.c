#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
  for (size_t i = 0; i < 8; i++)  fork();
  execlp("ping", "ping", "10.9.187.10", NULL);
}

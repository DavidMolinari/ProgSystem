#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
  pid_t pid, pidfils;
  int retour;
  char buffer[1024];
  while(strcasecmp(buffer, "exit") != 0){
    printf("[prompt]>");
    fgets(buffer, 1024, stdin);
    if(buffer[strlen(buffer)-1] == '\n')
    buffer[strlen(buffer)-1 ]= '\0';
    switch (pid = fork()) {
      case (pid_t)-1:
      perror("SRY MARCHE PAS . . .");
      exit(2);
      case (pid_t) 0:
      execlp(buffer, buffer, NULL);
      if(strcasecmp(buffer, "exit") != 0)
        fprintf(stderr, "CONNAIT PAS ... \n");
      exit(1);
      default:
      pidfils = wait(&retour);
    }
  }

}

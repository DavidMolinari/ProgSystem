#include <stdlib.h>
#include <stdio.h>

char aa[1024*1024];

int main(int argc, char *argv[]){
  char bb = malloc(1);
  char *cc =  (char*)malloc(1024*1024);


  printf("%p\n",aa );
  printf("%p\n",bb );
  printf("%p\n",cc );
  pause();


}

//push test
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <math.h>    
#include <pthread.h>   


int main(int argc, char **argv) {
printf("HELLO WORLD\n");
int option;
  int samples;
  char argument[256];
  char *o_value;
  int *n_value;

  int i = 0;
  while ((option = getopt(argc, argv, "E:L:f:e")) != -1){
      switch (option){
        case 'E':
            printf("f character found\n");
            break;
        case 'L':
            printf("L Character found\n");
            break;
        case 'f':
            printf("f Character found\n");
            break;
        case 'e':
            printf("e character found\n");
            break;

      }
    
  }
return 0;
}
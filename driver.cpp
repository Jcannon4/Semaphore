//push test
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <math.h>    
#include <pthread.h>  

#include "io.h"

ProductType drive_local;
ConsumerType drive_consumer;

int main(int argc, char **argv) {
   
    int option;
    int ethel_pace, lucy_pace, cfb_rate, esc_rate = 0;
    int i = 0;
  
  while ((option = getopt(argc, argv, "E:L:f:e:")) != -1){
      switch (option){
        case 'E':
            ethel_pace = atoi(optarg);
            printf("Ethel's pace is %d \n", ethel_pace);
            break;
        case 'L':
            lucy_pace = atoi(optarg);
            printf("Lucy's pace is %d \n", lucy_pace);
            break;
        case 'f':
            cfb_rate = atoi(optarg);
            printf("CFB rate is %d\n", cfb_rate);
            break;
        case 'e':
            esc_rate = atoi(optarg);
            printf("Escargot rate is %d\n", esc_rate);
            break;
        default:
            printf("Illegal Flag or missing argument: %c\n" , optopt);
            exit(10);
      }

    pthread_t consumer_lucy, consumer_ethel, producer_cfb, producer_esc;

    
    //CREATE CONSUMER THREADS
    //CREATE PRODUCER THREADS

    //JOIN THREADS


  }
return 0;
}
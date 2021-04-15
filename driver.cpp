//push test
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <pthread.h>  

#include "io.h"
#include "belt.h"
#include "consumer.h"
#include "producer.h"

ProductType drive_local;
ConsumerType drive_consumer;

int main(int argc, char **argv) {
   
    int option;
    int ethel_pace, lucy_pace, cfb_rate, esc_rate = 0;
    Belt *conveyor = new Belt(100);
    pthread_t main_thread[4];
  
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

  }
  Producer *snail_producer = new Producer(conveyor, esc_rate, "snail");
    Producer *FROG = new Producer(conveyor, esc_rate, "frog");
    //Thread CFB
    //then ESC
    //CREATE LUCY 
    //THEN ETHEL
    pthread_create(&main_thread[0], NULL, &produce, (void * )snail_producer);
    pthread_join(main_thread[0], NULL);
    printf("EXECUTE AFTER THREAD");
return 0;
}
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
  Producer *frog_producer = new Producer(conveyor, cfb_rate, 0);
  Producer *snail_producer = new Producer(conveyor, esc_rate, 1);
  Consumer *lucy = new Consumer(conveyor, lucy_pace, "Lucy");
  Consumer *ethel = new Consumer(conveyor, ethel_pace, "Ethel");
    
    //Thread CFB
    //then ESC
    //CREATE LUCY 
    //THEN ETHEL
    pthread_create(&main_thread[0], NULL, produce, (void * )snail_producer);
    pthread_create(&main_thread[1], NULL, produce, (void * )frog_producer);
    pthread_create(&main_thread[2], NULL, consume, (void * )lucy);
    pthread_create(&main_thread[3], NULL, consume, (void * )ethel);

    printf("EXECUTE AFTER THREAD BEFORE EXIT CALL\n");
    //MAYBE
    //PTHREAD_EXIT(NULL)
    pthread_join(main_thread[0], NULL);
    pthread_join(main_thread[1], NULL);
    pthread_join(main_thread[2], NULL);
    pthread_join(main_thread[3], NULL);

return 0;
}
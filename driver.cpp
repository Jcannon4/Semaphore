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
#include "production.h"

int main(int argc, char **argv) {
   
    int option;
    int  cfb_rate, esc_rate, ethel_pace, lucy_pace;

    //Default values for speed    
    cfb_rate = esc_rate = ethel_pace = lucy_pace = option = 0;
    //Initialize our conveyor belt which will be shared between all objects
    Belt *conveyor = new Belt(100);
    conveyor->report = new int*[2];
    //loop to set conveyor belt array values to 0
    for (int i=0 ; i < 2; i++){
        conveyor->onBelt[i] = 0;
        conveyor->produced[i] = 0;
        conveyor->report[i] = new int[2];
        for(int j =0; j<2; j++){
            conveyor->report[i][j] = 0;
        }
    }

//Parse arguments  
  while ((option = getopt(argc, argv, ":E:L:f:e:")) != -1){
      switch (option){
        case 'E':
            ethel_pace = atoi(optarg);
            break;
        case 'L':
            lucy_pace = atoi(optarg);
            break;
        case 'f':
            cfb_rate = atoi(optarg);
            break;
        case 'e':
            esc_rate = atoi(optarg);
            break;
      }
  }
//Create an array of threads
pthread_t main_thread[4];

//First create our two candy producer objects
//First argument is the belt that all producers and consumers will share
//Second argument is the respective speed of production or consumption
//Third argument is the id from produciton.h file
Producer *frog_producer = new Producer(conveyor, cfb_rate, FrogBite);
Producer *snail_producer = new Producer(conveyor, esc_rate, Escargot);
Consumer *lucy = new Consumer(conveyor, lucy_pace, Lucy);
Consumer *ethel = new Consumer(conveyor, ethel_pace, Ethel);

//Create four threads, the functions produce, and consume can be found 
//in the producer.cpp and consumer.cpp files
pthread_create(&main_thread[0], NULL, produce, (void * )snail_producer);
pthread_create(&main_thread[1], NULL, produce, (void * )frog_producer);
pthread_create(&main_thread[2], NULL, consume, (void * )lucy);
pthread_create(&main_thread[3], NULL, consume, (void * )ethel);

//Join all the threads
pthread_join(main_thread[0], NULL);
pthread_join(main_thread[1], NULL);
pthread_join(main_thread[2], NULL);
pthread_join(main_thread[3], NULL);

//Set barrier preventing the last action from firing
sem_wait(&(conveyor->barrier));
//Once barrier is posted then the production report can be printed
io_production_report(conveyor->produced, conveyor->report);

//Kill off semaphores for the sake of our CPU consumption
conveyor->killSem();
return 0;
}
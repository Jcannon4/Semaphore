
#include "io.h"
#include "producer.h"
#include <semaphore.h>
#include <unistd.h>
//Semaphore logic being called by pthreads

Producer::Producer(Belt *belt, int rate, int candy) {
    Producer::candy = candy;
    Producer::rate = rate;
    Producer::conveyor = belt;
}

void *produce (void *args){
    printf("PRODUCE BEING CALLED\n");
    Producer *produce = (Producer*) args;
    int rate = produce -> rate;
    printf("VALUE : %d\n", rate);
    while (true){
        sem_wait(&produce->conveyor->available_slots);
        //buffer access
        sem_wait(&produce->conveyor->mutex);
        
        produce->conveyor->push(produce->candy);
        sleep(2);
        sem_post(&produce->conveyor->mutex);
        sem_post(&produce->conveyor->unconsumed);
        
    }
    
    return NULL;
}
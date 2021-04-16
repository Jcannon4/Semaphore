#include "io.h"
#include "consumer.h"
#include <unistd.h>
//Semaphore logic being called by pthreads

Consumer::Consumer(Belt *belt, int pace, string name) {
    Consumer::name = name;
    Consumer::pace = pace;
    Consumer::conveyor = belt;
}

void *consume(void *consumer){
    printf("CONSUME BEING CALLED\n");
    Consumer *consume = (Consumer *) consumer;
    printf("SPEED: %d\n", consume->pace);
    while(true){
        
        sem_wait(&consume->conveyor->unconsumed);
        sem_wait(&consume->conveyor->mutex);
        if(consume->conveyor->total >= consume->conveyor->max ){
            printf("we have reach our consumption limit\n");
            if(false){
                //TODO io.c functions
            }
            //Change boolean value
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            return nullptr;
        }
        
        int curCandy = consume->conveyor->pop();
        if (curCandy){
            consume->conveyor->snails--;
            printf("SNAIL CONSUMEED:\t%d\n", consume->conveyor->snails);
        } else {
            consume->conveyor->ribbits--;
            printf("FROG CONSUMED\t%d\n", consume->conveyor->ribbits);
        }

        consume->conveyor->total++;
        
        
        sem_post(&consume->conveyor->mutex);
        sem_post(&consume->conveyor->available_slots);
        if(curCandy == 0){
            sem_post(&consume->conveyor->cfb_limit);
        }
        printf("----TOTAL-----\n\t%d\n", consume->conveyor->total);
        sleep(2);
    }
}
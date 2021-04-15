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
        consume->conveyor->pop();
        sleep(2);
        sem_post(&consume->conveyor->mutex);
        sem_post(&consume->conveyor->available_slots);
    }
}
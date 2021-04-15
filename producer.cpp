
#include "io.h"
#include "producer.h"
//Semaphore logic being called by pthreads

Producer::Producer(Belt *belt, int rate, string candy) {
    Producer::candy = candy;
    Producer::rate = rate;
    Producer::conveyor = belt;
}

void *produce (void *args){
    printf("PRODUCE BEING CALLED\n");
    Producer *produce = (Producer*) args;
    int rate = produce -> rate;
    printf("VALUE : %d\n", rate);
    return NULL;
}
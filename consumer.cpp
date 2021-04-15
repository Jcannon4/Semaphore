#include "io.h"
#include "consumer.h"
//Semaphore logic being called by pthreads

Consumer::Consumer(Belt *belt, int pace, string name) {
    Consumer::name = name;
    Consumer::pace = pace;
    Consumer::conveyor = belt;
}

void consume (){
    printf("CONSUME BEING CALLED\n");
}
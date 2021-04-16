
#include "io.h"
#include "producer.h"
#include "production.h"
#include <semaphore.h>
#include <unistd.h>
//Semaphore logic being called by pthreads

ProductType assembly_line;

Producer::Producer(Belt *belt, int rate, int candy) {
    Producer::candy = candy;
    Producer::rate = rate;
    Producer::conveyor = belt;
}

void *produce (void *args){
    //printf("PRODUCE BEING CALLED\n");
    Producer *produce = (Producer*) args;
    //0 = FROG
    //1 = ESCARGOT
    while (true){
        if(produce->candy == 0)
        {
            sem_wait(&produce->conveyor->cfb_limit);
        }

        sem_wait(&produce->conveyor->available_slots);
        sem_wait(&produce->conveyor->mutex);

        if(produce->conveyor->total >= produce->conveyor->max)
        {
            sem_post(&produce->conveyor->mutex);
            sem_post(&produce->conveyor->unconsumed);
            return nullptr;
        }
        
        bool isPlaced = produce->conveyor->push(produce->candy);
        if(produce->candy == 0){
            produce->conveyor->ribbits++;
            // produce->conveyor->produced[0] = produce->conveyor->ribbits;
            // produce->conveyor->onBelt[0]++;
            printf("RUNNING FROG: %d", produce->conveyor->ribbits);
            //printf("Just added frog\n");
        } else {
            produce->conveyor->snails++;
            // produce->conveyor->produced[1] = produce->conveyor->snails;
            // produce->conveyor->onBelt[1]++;
            printf("RUNNING SNAIL: %d", produce->conveyor->snails);
            //printf("Just added snail\n");
        }
        // int onBelt[] = {produce->conveyor->ribbits, produce->conveyor->snails};
        // int produced[] = {produce->conveyor->ethel_frog + produce->conveyor->lucy_frog , produce->conveyor->ethel_snail + produce->conveyor->lucy_snail};
        // io_add_type(assembly_line, onBelt, produced);

        
        //printf("Belt contains \nfrogs: %d\t snails: %d\n", produce->conveyor->ribbits, produce->conveyor->snails);
        printf("FROG %d : SNAIL : %d", produce->conveyor->ribbits, produce->conveyor->snails);
        sem_post(&produce->conveyor->mutex);
        sem_post(&produce->conveyor->unconsumed);
        usleep(produce->rate );
    }
    
    return NULL;
}

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
    
    Producer *produce = (Producer*) args;
    //0 = FROG
    //1 = ESCARGOT
    while (true){
        
    
        // }
        //Semaphore is 3
        // if(produce->candy == Escargot && produce->rate > 10000){
        //     produce->rate = 0;
        // } 

        usleep(produce->rate *1000);
        
        if(produce->candy == FrogBite){
            
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
        //Pushing candy id number onto our belt
        bool isPlaced  = produce->conveyor->push(produce->candy);
        
        //Check if the candy was succesfully placed
        if(isPlaced){

            produce->conveyor->total++;
            
            
            //check if frogs
            if(produce->candy == FrogBite){
                //increment total # of frogs made
                produce->conveyor->ribbits++;
                produce->conveyor->onBelt[FrogBite]++;
                produce->conveyor->produced[FrogBite]++;
               
                
                io_add_type(FrogBite, produce->conveyor->onBelt, produce->conveyor->produced);
                //printf("Produced size : %d\n", produce->conveyor->produced[0] + produce->conveyor->produced[1]);
                
                //Check if current total is the max
                //check if current amount of frogs == 3
                if(produce->conveyor->total >= produce->conveyor->max){
                    
                    sem_post(&produce->conveyor->mutex);
                    sem_post(&produce->conveyor->unconsumed);
                    
                    return nullptr;
                } 

            } //Candy is a snail
            else {
                //Increase snail counter
                produce->conveyor->snails++;
                produce->conveyor->onBelt[Escargot]++;
                produce->conveyor->produced[Escargot]++;

                //printf("Produced size : %d\n", produce->conveyor->produced[0] + produce->conveyor->produced[1]);
                
                io_add_type(Escargot, produce->conveyor->onBelt, produce->conveyor->produced);
                //Double check we arent at the max
                if(produce->conveyor->total >= produce->conveyor->max){
                    
                    sem_post(&produce->conveyor->mutex);
                    sem_post(&produce->conveyor->unconsumed);
                    //printf("EXITINg at bottom producer\n");
                    return nullptr;
                }
            }
            //Unblock threads upon completion
            sem_post(&produce->conveyor->mutex);
            sem_post(&produce->conveyor->unconsumed);
            
        }
       
    }
    
    //return NULL;
}
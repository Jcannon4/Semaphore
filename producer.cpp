
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
    
    while (true){
        //Make program wait based on argument given integer
        usleep(produce->rate *1000);
        //check if candy is a crunchy frog bite
        if(produce->candy == FrogBite){
            //Decrease the frog limit semaphore, will be posted by the consumption thread
            sem_wait(&produce->conveyor->cfb_limit);
        }
        //Decrease semaphores for the slots on the conveyor belt, and mutual exclusion.
        sem_wait(&produce->conveyor->available_slots);
        sem_wait(&produce->conveyor->mutex);
        
        //Check if the production counter is at the max
        if(produce->conveyor->production_counter >= produce->conveyor->max)
        {
            //If were at the production limit then release semaphore holds
            sem_post(&produce->conveyor->mutex);
            sem_post(&produce->conveyor->unconsumed);
            return nullptr;
        }
        //Pushing candy id number onto our belt
        bool isPlaced  = produce->conveyor->push(produce->candy);
        
        //Check if the candy was succesfully placed
        if(isPlaced){
            //Increase the total produced counter
            produce->conveyor->production_counter++;
    
            //check if frogs
            if(produce->candy == FrogBite){
                
                
                produce->conveyor->onBelt[FrogBite]++; //increase amount of frogs on conveyor belt
                produce->conveyor->produced[FrogBite]++; //increase total amount of frogs made
               
                io_add_type(FrogBite, produce->conveyor->onBelt, produce->conveyor->produced);
                
                //Check if current production_counter is the max
                if(produce->conveyor->production_counter >= produce->conveyor->max){
                    
                    sem_post(&produce->conveyor->mutex); //Release mutual exclusion hold
                    sem_post(&produce->conveyor->unconsumed); //Theres a candy on the belt, so consumption hold is up
                    //END THREAD SINCE WERE AT THE MAX
                    return nullptr;
                } 

            } //Candy is a snail
            else {
                
                produce->conveyor->onBelt[Escargot]++; //increase amount of snails on the conveyor belt
                produce->conveyor->produced[Escargot]++; //increase total amount of snails produced
                io_add_type(Escargot, produce->conveyor->onBelt, produce->conveyor->produced);
                
                //Check if were currently at the limit for production
                if(produce->conveyor->production_counter >= produce->conveyor->max){
                    //if so release holds for consumption thread and exit thread
                    sem_post(&produce->conveyor->mutex);
                    sem_post(&produce->conveyor->unconsumed);
                    return nullptr;
                }
            }
            //Unblock threads upon completion
            sem_post(&produce->conveyor->mutex);
            sem_post(&produce->conveyor->unconsumed);
            
        }
    }
    
}
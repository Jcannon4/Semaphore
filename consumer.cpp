#include "io.h"
#include "consumer.h"
#include "production.h"
#include <unistd.h>
//Semaphore logic being called by pthreads

Consumer::Consumer(Belt *belt, int pace, int name) {
    Consumer::name = name;
    Consumer::pace = pace;
    Consumer::conveyor = belt;
}

void *consume(void *consumer){
    
    Consumer *consume = (Consumer *) consumer;
    
    while(true){
        
        usleep(consume->pace * 1000);
        sem_wait(&consume->conveyor->unconsumed);
        sem_wait(&consume->conveyor->mutex);

        if(consume->conveyor->consumption_counter >= consume->conveyor->max ){
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            return nullptr;
        }

        int curCandy = consume->conveyor->pop();
        //Check that candy has been consumed
        if(curCandy >= 0){
            //Increase total consumpiton counter
            consume->conveyor->consumption_counter++;
            //check for frogbite
            if (consume->name == Lucy){
                
                //Track Lucy's frogs
                if(curCandy == FrogBite){
                    consume->conveyor->ribbits--; 
                    consume->conveyor->onBelt[FrogBite]--;
                    consume->conveyor->report[Lucy][FrogBite]++;
                    int l_consume[2] = {consume->conveyor->report[Lucy][FrogBite], consume->conveyor->report[Lucy][Escargot]};
                    io_remove_type(Lucy, FrogBite, consume->conveyor->onBelt, l_consume);
                    
                } //Lucy has consumed a frog
                else{
                    consume->conveyor->snails--;
                    consume->conveyor->onBelt[Escargot]--;
                    consume->conveyor->report[Lucy][Escargot]++;
                    int l_consume[2] = {consume->conveyor->report[Lucy][FrogBite], consume->conveyor->report[Lucy][Escargot]};
                    io_remove_type(Lucy, Escargot, consume->conveyor->onBelt, l_consume);
                }
                
            } //Check that the this is Ethel
            else if (consume->name == Ethel){
               //decrement snail count
                
                //Ethel has consumed a frogbite
                if(curCandy == FrogBite){
                   consume->conveyor->ribbits--; 
                    consume->conveyor->onBelt[FrogBite]--;
                    
                    consume->conveyor->report[Ethel][FrogBite]++;
                    int e_consume[2] = {consume->conveyor->report[Ethel][FrogBite], consume->conveyor->report[Ethel][Escargot]};
                    io_remove_type(Ethel, FrogBite, consume->conveyor->onBelt, e_consume);

                }//Ethel has consumed a snail
                else {
                    consume->conveyor->snails--;
                    //Remove snail from belt
                    consume->conveyor->onBelt[Escargot]--;
                   
                    consume->conveyor->report[Ethel][Escargot]++;
                    int e_consume[2] = {consume->conveyor->report[Ethel][FrogBite], consume->conveyor->report[Ethel][Escargot]};
                    io_remove_type(Ethel, Escargot, consume->conveyor->onBelt, e_consume);
                    
                }
                
            }
            
        }
        
        if(consume->conveyor->consumption_counter == consume->conveyor->max){
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            sem_post(&consume->conveyor->barrier);
            return nullptr;
        } 
            
        sem_post(&consume->conveyor->mutex);
        sem_post(&consume->conveyor->available_slots);
        
        
       if(curCandy == FrogBite){
           sem_post(&consume->conveyor->cfb_limit);
       }
        
    }
    
}
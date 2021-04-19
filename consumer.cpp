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
        //First make the CPU wait the alotted amount of time
        usleep(consume->pace * 1000);

        
        sem_wait(&consume->conveyor->unconsumed); //unconsumed is posted from production 
        sem_wait(&consume->conveyor->mutex); //mutex is share between all threads and ensures only one runs


        if(consume->conveyor->consumption_counter >= consume->conveyor->max ){
            //if consumption is at 100, then post semaphores and return thread
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            return nullptr;
        }

        int curCandy = consume->conveyor->pop(); //If no candy is on belt, then a negative value
        //Check for available candy from conveyor belt
        if(curCandy >= 0){
            //Increase total consumpiton counter
            consume->conveyor->consumption_counter++;

            //check if current consumer is Lucy
            if (consume->name == Lucy){
                
                //Track Lucy's frogs
                if(curCandy == FrogBite){
                    
                    consume->conveyor->onBelt[FrogBite]--; //Decrease the current count of frogs on the conveyor belt
                    consume->conveyor->report[Lucy][FrogBite]++; //Increase lucys consumed frog count
                    //Create a new array of lucys updated totals, for the sake of the remove type io
                    int l_consume[2] = {consume->conveyor->report[Lucy][FrogBite], consume->conveyor->report[Lucy][Escargot]};
                    io_remove_type(Lucy, FrogBite, consume->conveyor->onBelt, l_consume);
                    
                } //Lucy has consumed a snail
                else{
                    
                    consume->conveyor->onBelt[Escargot]--; //Decrease current count of snails on the belt
                    consume->conveyor->report[Lucy][Escargot]++; //increase lucys total count of snails
                    //new array of lucys updated values
                    int l_consume[2] = {consume->conveyor->report[Lucy][FrogBite], consume->conveyor->report[Lucy][Escargot]};
                    io_remove_type(Lucy, Escargot, consume->conveyor->onBelt, l_consume);
                }
                
            } //Check that the this is Ethel
            else if (consume->name == Ethel){
               
                
                //Ethel has consumed a frogbite
                if(curCandy == FrogBite){
                    
                    consume->conveyor->onBelt[FrogBite]--; //Remove frog from belt
                    consume->conveyor->report[Ethel][FrogBite]++; //increase ethels consumptions of frogs
                    int e_consume[2] = {consume->conveyor->report[Ethel][FrogBite], consume->conveyor->report[Ethel][Escargot]};
                    io_remove_type(Ethel, FrogBite, consume->conveyor->onBelt, e_consume);

                }//Ethel has consumed a snail
                else {
                    //Remove snail from belt
                    consume->conveyor->onBelt[Escargot]--;
                    //Increase ethels consumption of snails
                    consume->conveyor->report[Ethel][Escargot]++;
                    int e_consume[2] = {consume->conveyor->report[Ethel][FrogBite], consume->conveyor->report[Ethel][Escargot]};
                    io_remove_type(Ethel, Escargot, consume->conveyor->onBelt, e_consume); 
                }
            }
        //Check if this is the last iteration of consumption
        //Release semaphores and the barrier for the report
        if(consume->conveyor->consumption_counter == consume->conveyor->max){
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            sem_post(&consume->conveyor->barrier);
            return nullptr;
        } 
        //NOT the last iteration of consumption, release mutual exclusion
        //AND let production know that there is one more available spot to put a candy onto the belt
        sem_post(&consume->conveyor->mutex);
        sem_post(&consume->conveyor->available_slots);
        
        //If frogbite is consumed, let the conveyor belt know it can produce another one.
       if(curCandy == FrogBite){
           sem_post(&consume->conveyor->cfb_limit);
       }
        
    }
    
    }
}
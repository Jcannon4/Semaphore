#include "io.h"
#include "consumer.h"
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
        
        sem_wait(&consume->conveyor->unconsumed);
        sem_wait(&consume->conveyor->mutex);
        if(consume->conveyor->total >= consume->conveyor->max ){
            printf("we have reach our consumption limit\n");
            if(consume->conveyor->last){
                
                //TODO io.c functions

            }
            //Change boolean value
            consume->conveyor->last++;
            sem_post(&consume->conveyor->mutex);
            sem_post(&consume->conveyor->available_slots);
            return nullptr;
        }
        
        int curCandy = consume->conveyor->pop();
        if (curCandy){
            consume->conveyor->snails--;
        } else {
            consume->conveyor->ribbits--;
        }
        //Snail
        if(curCandy){
            //Ethel Snail
            if(consume->name){
                consume->conveyor->ethel_snail++;
            }
            //Lucy Snail
            else if (consume->name == 0){
                consume->conveyor->lucy_snail++;
            }
        }
        //Frog
        else if(curCandy == 0){
            //Ethel Frod
            if(consume->name){
                consume->conveyor->ethel_frog++;
            }
            //Lucy frog
            else if (consume->name == 0){
                consume->conveyor->lucy_frog++;
            }
        }
        

        consume->conveyor->total++;
        
        
        sem_post(&consume->conveyor->mutex);
        sem_post(&consume->conveyor->available_slots);
        if(curCandy == 0){
            sem_post(&consume->conveyor->cfb_limit);
        }
        printf("Total: %d\nEthel Frog: %d\tLucy Frog: %d\n EthelSnail: %d\t LucySnail: %d\n", consume->conveyor->total, consume->conveyor->ethel_frog, consume->conveyor->lucy_frog, consume->conveyor->ethel_snail, consume->conveyor->lucy_snail);
        int grandTotal = consume->conveyor->ethel_frog + consume->conveyor->lucy_frog + consume->conveyor->ethel_snail + consume->conveyor->lucy_snail;
        printf("GRANDTOTAL : %d\n", grandTotal);
        usleep(consume->pace);
    }
}
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <semaphore.h>


#ifndef BELT_H
#define BELT_H

using namespace std;

class Belt {
    public : 
    int production_counter;
    int consumption_counter;
    int max;
    std::queue<int> *belt;
    int onBelt[2];
    int produced[2];
    int **report;
    sem_t mutex , unconsumed, cfb_limit, available_slots, barrier;
    
    Belt(int limit);
    void killSem();
    int pop();
    bool push(int candy);
    
};




#endif
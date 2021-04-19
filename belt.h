#include <stdlib.h>
#include <iostream>
#include <queue>
#include <semaphore.h>


#ifndef BELT_H
#define BELT_H

using namespace std;

class Belt {
    public : 
    int ribbits;
    int snails;
    int total;
    int consumption_counter;
    int max;
    int ethel_snail;
    int ethel_frog;
    int lucy_frog;
    int lucy_snail;
    
    std::queue<int> *belt;

    int onBelt[2];

    int produced[2];
    int consumed[2];

    int **report;

    sem_t mutex , unconsumed, cfb_limit, available_slots, barrier;
    
    Belt(int limit);
    void killSem();
    int pop();
    bool push(int candy);
    
};




#endif
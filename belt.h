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
    int max;
    int ethel_snail;
    int ethel_frog;
    int lucy_frog;
    int lucy_snail;
    int last =0;
    std::queue<int> *belt;

    int onBelt[2] = {0,0};
    
    int produced[2];

    int consumed[2][2];

    sem_t mutex , unconsumed, cfb_limit, available_slots;
    
    Belt(int limit);
    void killSem();
    int pop();
    bool push(int candy);
    
};




#endif
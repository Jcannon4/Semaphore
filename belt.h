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
    std::queue<int> *belt;
    sem_t mutex , unconsumed, cfb_limit, available_slots;
    
    Belt(int limit);
    void killSem();
    int pop();
    bool push(int candy);
    
};




#endif
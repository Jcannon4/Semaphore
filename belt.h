#include <stdlib.h>
#include <iostream>
#include <semaphore.h>


#ifndef BELT_H
#define BELT_H

using namespace std;

class Belt {
    public : 
    int ribbits;
    int snails;
    int max;

    sem_t mutex, empty, full, cfb_limit;
    
    Belt(int limit);
    int pop();
    bool push(int time);
};



#endif
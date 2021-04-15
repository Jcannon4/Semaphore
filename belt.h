#include <stdlib.h>
#include <iostream>
#include <semaphore.h>

#ifndef BELT_H
#define BELT_H

using namespace std;

class Belt {
    public : 
    int onBelt[10];
    int ribbits;
    int snails;
    int max;

    Belt();
    int pop();
    bool push(int time);
};



#endif
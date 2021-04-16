#include <iostream>
#include <string>
#include <stdio.h>
#include "belt.h"

class Belt;
class Consumer {
    public :
    int pace;
    Belt *conveyor;
    int name;
    Consumer(Belt *belt, int pace, int name);

};

void *consume(void *consumer);
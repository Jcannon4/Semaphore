#include <iostream>
#include <stdio.h>
#include "belt.h"

class Belt;
class Producer {
    public :
    int rate;
    Belt *conveyor;
    int candy;
    Producer(Belt *belt, int rate, int candy);

};

void *produce(void *args);

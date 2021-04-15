#include <iostream>
#include <string>
#include <stdio.h>
#include "belt.h"

class Belt;
class Producer {
    public :
    int rate;
    Belt *conveyor;
    string candy;
    Producer(Belt *belt, int rate, string candy);

};

void *produce(void *args);

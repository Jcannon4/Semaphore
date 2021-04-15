#include <iostream>
#include <string>
#include <stdio.h>
#include "belt.h"

class Belt;
class Consumer {
    public :
    int pace;
    Belt *conveyor;
    string name;
    Consumer(Belt *belt, int pace, string name);

};

void *consume(void *consumer);
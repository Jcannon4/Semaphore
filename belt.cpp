#include "belt.h"


using namespace std;

Belt::Belt(int limit) {
    Belt::ribbits = 0;
    Belt::snails = 0;
    Belt::total = 0;
    Belt::max = limit;
    
    Belt::belt = new std::queue<int>();

    sem_init(&(Belt::mutex), 0 , 1);
    sem_init(&(Belt::available_slots), 0, 10);
    sem_init(&(Belt::cfb_limit), 0, 3);
    sem_init(&(Belt::unconsumed), 0, 0);
}

bool Belt::push(int candy){
    if((Belt::belt->size()) > 10) {
        return false;
    }
    //0 = Frog
    //1 = Escargot
    printf("PUSHER MAN\n");
    Belt::belt->push(candy);
    if(candy == 0){
        Belt::ribbits++;
        printf("Total Frog count is %d\n", Belt::ribbits);
    } else {
        Belt::snails++;
        printf("Total snail count is %d\n", Belt::snails);
    }
}

int Belt::pop() {
    int desired;
    if(!belt->empty()){
        printf("POPPING OFF!\n");
        desired = belt->front();
        belt->pop();
    }   
    return desired;
    // if(desired == 0 ){
    //     Belt::ribbits--;
    //     printf("Frog consumed : %d\n", Belt::ribbits);
    // } else {
    //     Belt::snails--;
    //     printf("Escargot Consumed: %d\n", Belt::snails);
    // }
}
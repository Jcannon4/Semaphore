#include "belt.h"


using namespace std;

Belt::Belt(int limit) {
    Belt::ribbits = 0;
    Belt::snails = 0;
    Belt::total = 0;
    Belt::max = limit;
    Belt::last = 0;
    Belt::ethel_snail,ethel_frog,lucy_frog,lucy_snail = 0;

    Belt::belt = new std::queue<int>();

    sem_init(&(Belt::mutex), 0 , 1);
    sem_init(&(Belt::available_slots), 0, 10);
    sem_init(&(Belt::cfb_limit), 0, 3);
    sem_init(&(Belt::unconsumed), 0, 0);
}

void Belt::killSem(){
    sem_destroy(&(Belt::available_slots));
    sem_destroy(&(Belt::cfb_limit));
    sem_destroy(&(Belt::unconsumed));
    sem_destroy(&(Belt::mutex));
}

bool Belt::push(int candy){
    //printf("conveyor belt size: %lu\n", Belt::belt->size());
    if((Belt::belt->size()) < 10) {
        Belt::belt->push(candy);
        return true;
    //0 = Frog
    //1 = Escargot
    }else {return false;}
   
}

int Belt::pop() {
    int desired;
    if(!belt->empty()){
       // printf("POPPING OFF!\n");
        desired = belt->front();
        belt->pop();
    }   
    return desired;
   
}
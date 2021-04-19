#include "belt.h"
#include "production.h"


using namespace std;

Belt::Belt(int limit) {
    //Counters to track progress of proudcers and consumers
    Belt::consumption_counter = 0;
    Belt::production_counter = 0;
    //max is our breaking limit
    Belt::max = limit;
    //Acutal queue that will hold candies
    Belt::belt = new std::queue<int>();

    //Semaphores that will ensure our unique program constraints
    sem_init(&(Belt::mutex), 0 , 1);
    sem_init(&(Belt::available_slots), 0, 10);
    sem_init(&(Belt::cfb_limit), 0, 3);
    sem_init(&(Belt::unconsumed), 0, 0);
    sem_init(&(Belt::barrier), 0, 0);
}

//Kills the semaphores at the end of the program
void Belt::killSem(){
    sem_destroy(&(Belt::available_slots));
    sem_destroy(&(Belt::cfb_limit));
    sem_destroy(&(Belt::unconsumed));
    sem_destroy(&(Belt::mutex));
    sem_destroy(&(Belt::barrier));
}
//Returns a boolean value depending if theres space to add another candy to the belt
bool Belt::push(int candy){
    
    //Only push a candy onto the queue if theres less than 10 candies
    if((Belt::belt->size()) <= 10) {
        Belt::belt->push(candy);
        return true;
    }
    //otherwise return false
        return false;
}

int Belt::pop() {
    //Defaault is negative
    int desired = -1;
    //Check that there is a candy in the queue
    if(belt->size() > 0){
        //Grab value of next coming candy and remove it from the conveyor belt
        desired = belt->front();
        belt->pop();
    }   
    //Return its value
    return desired;
   
}
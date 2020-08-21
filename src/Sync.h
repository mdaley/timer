#ifndef TIMER_SYNC_H
#define TIMER_SYNC_H

#include <mutex>

class Sync {
public:
    Sync(std::mutex* mutex_, std::condition_variable* condVar_, unsigned int interval_) :
            mutex{mutex_}, condVar{condVar_}, state{false}, interval{interval_} {};
    std::mutex* mutex;
    std::condition_variable* condVar;
    bool state;
    unsigned int interval;
};


#endif //TIMER_SYNC_H

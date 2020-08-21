#ifndef TIMER_SYNC_H
#define TIMER_SYNC_H

#include <mutex>

class Sync {
public:
    unsigned long id;
    std::shared_ptr<std::mutex*> mutex;
    std::shared_ptr<std::condition_variable*> condVar;
    std::shared_ptr<std::atomic<bool>> state;
    std::shared_ptr<std::atomic<unsigned int>> interval;
};


#endif //TIMER_SYNC_H

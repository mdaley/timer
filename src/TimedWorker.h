#ifndef TIMER_TIMED_WORKER_H
#define TIMER_TIMED_WORKER_H

#include <iostream>
#include <memory>
#include <thread>
#include <plog/Log.h>
#include "Sync.h"

class TimedWorker {
private:
    std::mutex mutex_;
    std::condition_variable condVar_;
    std::atomic<bool> running_{false};
    std::atomic<bool> ready_{false};

    void workLoop();
protected:
    virtual void work() {};
public:
    void start();
    void stop();
    void trigger();
};

#endif //TIMER_TIMED_WORKER_H

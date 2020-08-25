#ifndef TIMER_ROOTTIMER_H
#define TIMER_ROOTTIMER_H

#include <thread>
#include <iostream>
#include <plog/Log.h>
#include "RandomGenerator.h"
#include "RwConcurrentUnorderedMap.h"
#include "Sync.h"
#include "TimedWorker.h"

class RootTimer {
private:
    RandomGenerator generator;
    unsigned int baseIntervalNs;
    std::atomic<bool> isRunning{false};

    RwConcurrentUnorderedMap<unsigned long, TimedWorker*> workers;
    //RwConcurrentUnorderedMap<unsigned long, std::shared_ptr<Sync>> timerSyncs;
    //std::shared_timed_mutex timerSyncsMutex;

    void timerLoop();

public:
    RootTimer(unsigned int baseIntervalNs);
    void start();
    void stop();
    //std::shared_ptr<Sync> obtainSync(unsigned int interval);
    void addWorker(TimedWorker* worker);
};

#endif //TIMER_ROOTTIMER_H

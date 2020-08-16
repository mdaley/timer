#ifndef TIMER_ROOTTIMER_H
#define TIMER_ROOTTIMER_H

#include <thread>
#include <iostream>
#include <plog/Log.h>

class RootTimer {
private:
    unsigned int baseIntervalNs;
    std::atomic<bool> isRunning;

    void timerLoop();

public:
    RootTimer(unsigned int baseIntervalNs);
    void start();
    void stop();
};


#endif //TIMER_ROOTTIMER_H

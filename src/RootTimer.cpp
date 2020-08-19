#include "RootTimer.h"

RootTimer::RootTimer(unsigned int baseIntervalNs) {
    this->baseIntervalNs = baseIntervalNs;
}

void RootTimer::timerLoop() {
    while(this->isRunning.load()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(baseIntervalNs));
        PLOG_DEBUG << "Loop";
    }

    PLOG_DEBUG << "Root timer loop finished";
}

void RootTimer::start() {
    this->isRunning.store(true);
    PLOG_DEBUG << "Starting root timer loop";
    auto thread = std::thread(&RootTimer::timerLoop, this);
    thread.detach();
    PLOG_DEBUG << "Root timer loop started";
}

void RootTimer::stop() {
    this->isRunning.store(false);
}

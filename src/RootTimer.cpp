#include "RootTimer.h"

RootTimer::RootTimer(unsigned int baseIntervalNs) {
    this->isRunning.store(false);
    this->baseIntervalNs = baseIntervalNs;
}

void RootTimer::timerLoop() {
    while(this->isRunning.load()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(baseIntervalNs));
        std::cout << "Loop" << std::endl;
    }

    std::cout << "Timer loop finished." << std::endl;
}

void RootTimer::start() {
    this->isRunning.store(true);
    std::cout << "Start" << std::endl;
    auto thread = std::thread(&RootTimer::timerLoop, this);
    thread.detach();
    std::cout << "Started" << std::endl;
}

void RootTimer::stop() {
    this->isRunning.store(false);
}

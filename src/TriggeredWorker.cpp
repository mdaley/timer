#include "TriggeredWorker.h"

TriggeredWorker::~TriggeredWorker() {
    stop();
    thread_.join();
}

void TriggeredWorker::workLoop() {
    PLOGD << "workLoop started...";

    while(true) {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this]{
            return ready_ | !running_; });
        ready_ = false;

        if (!running_) {
            break;
        }

        PLOGD << "Calling work()...";
        work();

        lock.unlock();
        condVar_.notify_one();
    }

    PLOGD << "Worker thread completed.";
}

void TriggeredWorker::start() {
    PLOGD << "Worker start...";
    running_ = true;
    thread_ = std::thread(&TriggeredWorker::workLoop, this);
}

void TriggeredWorker::stop() {
    PLOGD << "Worker stop.";
    std::unique_lock<std::mutex> lock(mutex_);
    running_ = false;
    lock.unlock();
    condVar_.notify_one();
}

void TriggeredWorker::trigger() {
    PLOGD << "Trigger.";
    std::unique_lock<std::mutex> lock(mutex_);
    ready_ = true;
    lock.unlock();
    condVar_.notify_one();
}

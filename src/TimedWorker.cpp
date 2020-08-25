#include "TimedWorker.h"

void TimedWorker::workLoop() {
    PLOGD << "workLoop started...";

    while(true) {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this]{
            bool ready = this->ready_;
            bool running = this->running_;
            return ready | !running; });
        this->ready_ = false;

        if (!this->running_) {
            break;
        }

        PLOGD << "Calling work()...";
        work();

        lock.unlock();
        condVar_.notify_one();
    }

    PLOGD << "Worker thread completed.";
}

void TimedWorker::start() {
    PLOGD << "Worker start...";
    this->running_ = true;
    auto thread = std::thread(&TimedWorker::workLoop, this);
    thread.detach();
}

void TimedWorker::stop() {
    PLOGD << "Worker stop.";
    this->running_ = false;
}

void TimedWorker::trigger() {
    PLOGD << "Trigger.";
    std::unique_lock<std::mutex> lock(mutex_);
    ready_ = true;
    lock.unlock();
    condVar_.notify_one();
}

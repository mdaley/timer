#include "TimedWorker.h"

void TimedWorker::workLoop() {
    std::cout << "workLoop started." << std::endl;
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

        std::cout << "Working..." <<std::endl;
        work();

        lock.unlock();
        condVar_.notify_one();
    }
}

void TimedWorker::start() {
    std::cout << "Worker start" << std::endl;
    this->running_ = true;
    auto thread = std::thread(&TimedWorker::workLoop, this);
    thread.detach();
}

void TimedWorker::stop() {
    this->running_ = false;
}

void TimedWorker::trigger() {
    std::lock_guard<std::mutex> lock(mutex_);
    ready_ = true;
    condVar_.notify_one();
}

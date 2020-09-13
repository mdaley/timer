#include "TriggeredWorker.h"

TriggeredWorker::~TriggeredWorker() {
    stop();
    thread_.join();
}

void TriggeredWorker::workLoop() {
    PLOGD << "workLoop started...";

    while(true) {
        bool state;
        queue.wait_dequeue(state);

        if (!state) {
            running_ = false;
            break;
        }

        PLOGD << "Calling work()...";
        work();
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
    queue.enqueue(false);
}

void TriggeredWorker::trigger() {
    PLOGD << "Trigger.";
    queue.enqueue(true);
}

bool TriggeredWorker::isRunning() {
    return running_;
}

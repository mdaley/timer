#ifndef TIMER_TRIGGERED_WORKER_H
#define TIMER_TRIGGERED_WORKER_H

#include <thread>
#include <plog/Log.h>
#include "readerwriterqueue.h"

namespace mc = moodycamel;

class TriggeredWorker {
private:
    mc::BlockingReaderWriterQueue<bool> queue{100};
    bool running_{false};

    std::thread thread_;

    void workLoop();
protected:
    virtual void work() {};
public:
    virtual ~TriggeredWorker();
    void start();
    void stop();
    void trigger();
    bool isRunning();
};

#endif //TIMER_TRIGGERED_WORKER_H

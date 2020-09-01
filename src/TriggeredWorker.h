#ifndef TIMER_TRIGGERED_WORKER_H
#define TIMER_TRIGGERED_WORKER_H

#include <thread>
#include <plog/Log.h>

class TriggeredWorker {
private:
    std::mutex mutex_;
    std::condition_variable condVar_;
    bool running_{false};
    bool ready_{false};

    std::thread thread_;

    void workLoop();
protected:
    virtual void work() {};
public:
    virtual ~TriggeredWorker();
    void start();
    void stop();
    void trigger();
};

#endif //TIMER_TRIGGERED_WORKER_H

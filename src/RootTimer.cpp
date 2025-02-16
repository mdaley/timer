#include "RootTimer.h"

RootTimer::RootTimer(unsigned int baseIntervalNs) {
    this->baseIntervalNs = baseIntervalNs;
}

void RootTimer::timerLoop() {
    const auto triggerFn = [](TriggeredWorker* worker){
        worker->trigger();
    };

    while(this->isRunning.load()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(baseIntervalNs));
        //workers.iterateLocked(triggerFn);
    }

    PLOGD << "Root timer loop finished";
}

void RootTimer::start() {
    this->isRunning.store(true);
    PLOGD << "Starting root timer loop";
    auto thread = std::thread(&RootTimer::timerLoop, this);
    thread.detach();
    PLOGD << "Root timer loop started";
}

void RootTimer::stop() {
    PLOGD << "Stopping root timer loop.";
    this->isRunning.store(false);
}

void RootTimer::addWorker(TriggeredWorker *worker) {
    //this->workers.emplace(generator.randomULong(), worker);
    worker->start();
}

/*std::shared_ptr<Sync> RootTimer::obtainSync(unsigned int interval) {
    Sync sync;

    sync.id = generator.randomULong();
    std::mutex mutex;
    std::condition_variable cv;
    sync.mutex = std::make_shared<std::mutex*>(&mutex);
    sync.condVar = std::make_shared<std::condition_variable*>(&cv);
    sync.interval = std::make_shared<std::atomic<unsigned int>>(interval);
    sync.state = std::make_shared<std::atomic<bool>>(false);

    this->timerSyncs.emplace(sync.id, std::make_shared<Sync>(sync));
    return this->timerSyncs.at(sync.id);
}*/

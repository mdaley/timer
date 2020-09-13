#include "catch.hpp"
#include "TriggeredWorker.h"
#include <thread>

TEST_CASE("Simple timed worker performs work when triggered") {
    static std::atomic<int> twt_count{0};

    class SimpleTriggeredWorker : public TriggeredWorker {
    protected:
        void work() override {
            PLOGD << "Incrementing counter.";
            twt_count.fetch_add(1);
        }
    };

    SimpleTriggeredWorker worker;

    worker.start();
    CHECK(worker.isRunning());

    for (int i = 0; i < 1000; i++) {
        worker.trigger();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CHECK(twt_count == 1000);

    worker.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CHECK(!worker.isRunning());
}

TEST_CASE("Start and immediately stop a worker works, with no work done") {
    static std::atomic<bool> workDone{false};

    class NullTriggeredWorker : public TriggeredWorker {
    protected:
        void work() override {
            workDone.store(true);
        }
    };

    NullTriggeredWorker worker;

    worker.start();
    worker.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CHECK(!workDone);
}

TEST_CASE("Existing work completes before worker stops") {
    static std::atomic<bool> workFinished{false};

    class SlowWorker : public TriggeredWorker {
    protected:
        void work() override {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            workFinished.store(true);
            PLOGI << "work done";
        }
    };

    SlowWorker worker;

    worker.start();
    worker.trigger();
    worker.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    PLOGI << "result " << workFinished;
    CHECK(workFinished.load());
}
 // work throws
 // state maintained between calls
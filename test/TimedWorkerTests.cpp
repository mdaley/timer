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

    for (int i = 0; i < 1000; i++) {
        worker.trigger();
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CHECK(twt_count == 1000);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    worker.stop();
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

    // worker starts and then waits in the loop
    worker.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    worker.stop();

    CHECK(!workDone);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST_CASE("On stop work being done completes then worker stops") {
    static std::atomic<bool> workFinished{false};

    class HangsForeverWorker : public TriggeredWorker {
    protected:
        void work() override {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            workFinished.store(true);
        }
    };

    HangsForeverWorker worker;

    // worker starts and then waits in the loop
    worker.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    worker.stop();

    CHECK(workFinished);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
 // work throws
 // state maintained between calls
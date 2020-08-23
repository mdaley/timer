#include "catch.hpp"
#include "TimedWorker.h"
#include <iostream>
#include <thread>

std::atomic<int> count{0};

class SimpleTimedWorker : public TimedWorker {
protected:
    void work() override {
        std::cout << "WORK" << std::endl;
        count.fetch_add(1);
    }
};

TEST_CASE("Test TimedWorker works correctly") {
    CHECK(true);

    SimpleTimedWorker worker;

    std::cout << "Starting worker" <<std::endl;

    worker.start();

    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.trigger();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    CHECK(count == 6);
}
#include "catch.hpp"
#include "TimedWorker.h"
#include <thread>



TEST_CASE("Simple timed worker performs work when triggered") {
    static std::atomic<int> twt_count{0};

    class SimpleTimedWorker : public TimedWorker {
    protected:
        void work() override {
            PLOGD << "Incrementing counter.";
            twt_count.fetch_add(1);
        }
    };

    SimpleTimedWorker worker;

    worker.start();

    for (int i = 0; i < 1000; i++) {
        worker.trigger();
        std::this_thread::sleep_for(std::chrono::microseconds(20));
    }

    CHECK(worker.errorCount() == 0);
    CHECK(twt_count == 1000);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    worker.stop();
}

 // work throws
 // state maintained between calls
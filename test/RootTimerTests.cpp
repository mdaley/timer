#include <RootTimer.h>
#include <unordered_map>
#include "catch.hpp"

/*std::atomic<int> count{0};

class SimpleTimedWorker2 : public TimedWorker {
protected:
    void work() override {
        PLOGD << "Work.";
        count.fetch_add(1);
    }
};

TEST_CASE("Root timer obtain sync") {
    RootTimer rootTimer(1000000000);

    SimpleTimedWorker2 worker;
    //SimpleTimedWorker2 worker2;
    rootTimer.addWorker(&worker);
    //rootTimer.addWorker(&worker2);

    rootTimer.start();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    rootTimer.stop();

    std::this_thread::sleep_for(std::chrono::seconds(5));
}*/
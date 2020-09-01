#include <unordered_map>
#include <shared_mutex>
#include <Sync.h>
//#include "RwConcurrentUnorderedMap.h"
#include "catch.hpp"
/*
TEST_CASE("Sync can be stored in map, getting from map refers to same instance") {
    std::mutex mu1;
    std::mutex mu2;
    std::condition_variable cv1;
    std::condition_variable cv2;

    Sync sync1;
    sync1.mutex = std::make_shared<std::mutex*>(&mu1);
    sync1.condVar = std::make_shared<std::condition_variable*>(&cv1);
    sync1.interval = std::make_shared<std::atomic<unsigned int>>(7);
    sync1.state = std::make_shared<std::atomic<bool>>(false);

    std::shared_ptr<Sync> fg = std::make_shared<Sync>(sync1);
    RwConcurrentUnorderedMap<int, std::shared_ptr<Sync>> m;
    std::shared_timed_mutex mut;

    m.emplace(1, fg);

    Sync s = *(m.at(1).get());

    // the mutex pointer stored in sync1 is to the same object as is stored in a Sync value returned from the map.
    CHECK(s.mutex.get() == sync1.mutex.get());

    // if a value is changed in sync1 then, it is reflected in the value retrieved in the sync retrieved from the map.
    CHECK(*(s.interval.get()) == 7);
    CHECK(*(sync1.interval.get()) == 7);

    *(s.interval.get()) = 2;

    CHECK(*(s.interval.get()) == 2);
    CHECK(*(sync1.interval.get()) == 2);

    // this is because interval in fact points to the same memory location
    CHECK(s.interval.get() == sync1.interval.get());

    // the mutex is likewise shared, lock it and it can't be locked via value obtained from map.
    (*(s.mutex.get()))->lock();

    bool canLock = (*(sync1.mutex.get()))->try_lock();
    CHECK(canLock == false);

    // and the other way around...
    (*(s.mutex.get()))->unlock();
    (*(sync1.mutex.get()))->lock();
    canLock = (*(s.mutex.get()))->try_lock();
    CHECK(canLock == false);

    // getting via at() is fine because out of range values fail.
    CHECK(m.size() == 1);
    bool oor{false};
    try {
        Sync notThere = *(m.at(17).get());
    } catch(std::out_of_range o) {
        oor = true;
    }
    CHECK(oor == true);
    CHECK(m.size() == 1);

    // trying to get something from the map that isn't there using square brackets is bad! So don't do it.
    CHECK(m.size() == 1);
    Sync notThere = m[17];
    CHECK(m.size() == 2);
}*/
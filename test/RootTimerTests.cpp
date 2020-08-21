#include <RootTimer.h>
#include <map>
#include <Sync.h>
#include "catch.hpp"

TEST_CASE("Add children syncs works, children syncs can be retrieved") {
    RootTimer rt(1000);

    std::mutex mu1;
    std::mutex mu2;
    std::condition_variable cv1;
    std::condition_variable cv2;
    Sync sync1(&mu1, &cv1, 1);
    Sync sync2(&mu2, &cv2, 1);

    /*sync1.interval = std::make_shared<unsigned int>(7);

    std::map<int, Sync> m;

    m.emplace(1, sync1);

    Sync s = m.at(1);
    std::cout << *(s.interval.get()) << std::endl;

    *(s.interval.get()) = 2;

    std::cout << *(sync1.interval.get()) << std::endl;

    */
    std::map<int, std::shared_ptr<Sync>> m;

    std::mutex mu;
    m.emplace(1, std::make_shared<Sync>(sync1));
    m.emplace(2, std::make_shared<Sync>(sync1));

    std::cout << sync1.interval << std::endl;

    std::shared_ptr<Sync> z = m.at(1);
    z.get()->interval = 7;

    std::cout << sync1.interval << std::endl;
}
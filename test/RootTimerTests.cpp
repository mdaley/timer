#include <RootTimer.h>
#include <unordered_map>
#include <shared_mutex>
#include <Sync.h>
#include "RwConcurrentUnorderedMap.h"
#include "catch.hpp"

TEST_CASE("Root timer obtain sync") {
    RootTimer rootTimer(1000000000);

    auto sync = rootTimer.obtainSync(1);
    std::cout << *(sync.get()->interval.get()) << std::endl;
}
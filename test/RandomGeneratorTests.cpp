#include "catch.hpp"
#include "RandomGenerator.h"
#include <unordered_set>

TEST_CASE("Random unsigned longs can be generated") {
    RandomGenerator generator;

    std::unordered_set<unsigned long> values;

    for (int i = 0; i < 1000000; i++) {
        values.emplace(generator.randomULong());
    }

    // 1 million unsigned longs added and no collisions. Seems random to me.
    CHECK(values.size() == 1000000);
}
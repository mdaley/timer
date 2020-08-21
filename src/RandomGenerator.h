#ifndef TIMER_RANDOMGENERATOR_H
#define TIMER_RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
private:
    std::mt19937_64 eng;
    std::uniform_int_distribution<unsigned long> distribution;
public:
    RandomGenerator() {
        std::random_device rd;
        eng = std::mt19937_64(rd());
    }
    unsigned long randomULong() {
        return distribution(eng);
    }
};


#endif //TIMER_RANDOMGENERATOR_H

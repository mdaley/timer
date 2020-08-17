#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <libconfig.h++>
#include <plog/Log.h>

class Config {
private:
    libconfig::Config cfg;

    const int DEFAULT_ROOT_TIMER_INTERVAL_NS = 1000000000;
    unsigned int _rootTimerIntervalNs = DEFAULT_ROOT_TIMER_INTERVAL_NS;
    const plog::Severity DEFAULT_LOGGING_LEVEL = plog::warning;
    plog::Severity _loggingLevel = DEFAULT_LOGGING_LEVEL;
public:
    bool load(const char* fileName);
    unsigned int rootTimerIntervalNs() const { return _rootTimerIntervalNs; }
    plog::Severity loggingLevel() const { return _loggingLevel; }
};


#endif //TIMER_CONFIG_H

#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <iostream>
#include <libconfig.h++>
#include <plog/Log.h>

class Config {
private:
    libconfig::Config cfg;

    const int DEFAULT_ROOT_TIMER_INTERVAL_NS = 1000000000;
    unsigned int _rootTimerIntervalNs = DEFAULT_ROOT_TIMER_INTERVAL_NS;

    const std::string DEFAULT_LOG_FILE_NAME = "timer_log.log";
    std::string _logFileName = DEFAULT_LOG_FILE_NAME;

    const plog::Severity DEFAULT_LOGGING_LEVEL = plog::warning;
    plog::Severity _loggingLevel = DEFAULT_LOGGING_LEVEL;

    const bool DEFAULT_LOG_TO_CONSOLE = true;
    bool _logToConsole = DEFAULT_LOG_TO_CONSOLE;
public:
    bool load(const char* fileName);
    unsigned int rootTimerIntervalNs() const { return _rootTimerIntervalNs; }
    std::string logFileName() const { return _logFileName; }
    bool logToConsole() const { return _logToConsole; }
    plog::Severity loggingLevel() const { return _loggingLevel; }
};


#endif //TIMER_CONFIG_H

#include "catch.hpp"
#include "Config.h"

TEST_CASE("Config has default values") {
    Config cfg;
    CHECK(cfg.logToConsole() == true);
    CHECK(cfg.logFileName() == "timer_log.log");
    CHECK(cfg.loggingLevel() == plog::warning);
    CHECK(cfg.rootTimerIntervalNs() == 1000000000);
}

TEST_CASE("Config takes values from config file") {
    Config cfg;
    if (!cfg.load("../test/resources/config.cfg")) {

    }
    CHECK(cfg.logToConsole() == false);
    CHECK(cfg.logFileName() == "blah.log");
    CHECK(cfg.loggingLevel() == plog::debug);
    CHECK(cfg.rootTimerIntervalNs() == 12345);
}
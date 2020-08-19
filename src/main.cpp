#include "RootTimer.h"
#include "Config.h"
#include <thread>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

int main(int argc, char* argv[]) {

    Config cfg;

    if (argc != 2) {
        std::cout << "Configuration files not specified as first argument. Aborting..." << std::endl;
        return 1;
    }

    if (!cfg.load(argv[1])) {
        return 1;
    }


    plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::Logger<0>& logger = plog::init(cfg.loggingLevel(), cfg.logFileName().c_str());

    if (cfg.logToConsole()) {
        logger.addAppender(&consoleAppender);
    }

    PLOG_INFO << "Main start";

    RootTimer timer(cfg.rootTimerIntervalNs());
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    timer.stop();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    PLOG_INFO << "Main end";
    return 0;
}

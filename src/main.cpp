#include "RootTimer.h"
#include <thread>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <libconfig.h++>

int main() {
    plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, "timer_log.txt").addAppender(&consoleAppender);

    libconfig::Config cfg;
    PLOG_INFO << "Main start";

    RootTimer timer(1000000000);
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    timer.stop();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    PLOG_INFO << "Main end";
    return 0;
}

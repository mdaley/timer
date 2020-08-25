#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
plog::Logger<0>& logger = plog::init(plog::info, &consoleAppender);




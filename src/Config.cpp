#include "Config.h"

bool Config::load(const char* fileName) {
    try {
        cfg.readFile(fileName);
    } catch(const libconfig::FileIOException& fioe) {
        std::cout << "Could not load config file " << fileName << std::endl;
        return false;
    } catch(const libconfig::ParseException& pe) {
        std::cout << "Parse error loading config " << pe.getFile() << ":" << pe.getLine() << " - " << pe.getError() << std::endl;
        return false;
    }

    cfg.lookupValue("rootTimerIntervalNs", _rootTimerIntervalNs);
    cfg.lookupValue("logToConsole", _logToConsole);
    cfg.lookupValue("logFile", _logFileName);

    std::string loggingLevelStr;
    if (cfg.lookupValue("loggingLevel", loggingLevelStr)) {
        plog::Severity severity = plog::severityFromString(loggingLevelStr.c_str());
        if (severity != plog::none) {
            _loggingLevel = severity;
        }
    }

    return true;
}
#include "Config.h"

bool Config::load(const char* fileName) {
    try {
        cfg.readFile(fileName);
    } catch(const libconfig::FileIOException& fioe) {
        PLOGE << "Could not load config file " << fileName;
        return false;
    } catch(const libconfig::ParseException& pe) {
        PLOGE << "Parse error loading config " << pe.getFile() << ":" << pe.getLine() << " - " << pe.getError();
        return false;
    }

    cfg.lookupValue("rootTimerIntervalNs", _rootTimerIntervalNs);

    std::string loggingLevelStr;
    if (cfg.lookupValue("loggingLevel", loggingLevelStr)) {
        plog::Severity severity = plog::severityFromString(loggingLevelStr.c_str());
        if (severity != plog::none) {
            _loggingLevel = severity;
        }
    }

    return true;
}
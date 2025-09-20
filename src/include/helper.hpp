#pragma once
#include <string>
#include <iostream>

class Helper
{
private:
    /* data */
    struct logLevels {
        bool error = true;
        bool warning = true;
        bool info = true;
        bool debug = true;
        bool raw = true;
	}logLevel;
public:
    Helper(/* args */);
    ~Helper();

    void log(std::string logMsg);
    void logError(std::string logMsg);
    void logWarning(std::string logMsg);
    void logInfo(std::string logMsg);
    void logDebug(std::string logMsg);
    void logRaw(std::string logMsg, bool logLevel = true);
    void printArgs(int argc, const char *argv[]);
};

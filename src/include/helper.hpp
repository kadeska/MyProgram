#pragma once
#include <iostream>

class Helper
{
private:
    /* data */
public:
    Helper(/* args */);
    ~Helper();

    void log(std::string logMsg);
    void logError(std::string logMsg);
    void logWarning(std::string logMsg);
    void logInfo(std::string logMsg);
    void logDebug(std::string logMsg);
    void logRaw(std::string logMsg);
    void printArgs(int argc, const char *argv[]);
};



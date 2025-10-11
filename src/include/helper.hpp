#pragma once
#include <string>
#include <iostream>
#include <filesystem>

// Forward declarations
class IOmanager;
class inputManager;
class mapGenerator;

class Helper
{
private:
    struct logLevels {
        bool error = true;
        bool warning = true;
        bool info = true;
        bool debug = true;
        bool raw = true;
    } logLevel;
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

    std::filesystem::path logFile;
    std::filesystem::path serverLogFile;
    std::filesystem::path configFile;

    IOmanager* ioMan;
    inputManager* inputMan;
    mapGenerator* mapGen;
};

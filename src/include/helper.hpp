#pragma once
#include <string>
#include <iostream>
#include <filesystem>

#include "IOmanager.hpp"
#include "mapGenerator.hpp"


//#ifdef _WIN32
//#else
//// linux specific includes
//#ifdef USE_NCURSES
//#include <ncurses.h>
//#endif
//#endif


// Forward declarations
class IOmanager;
class inputManager;
class mapGenerator;
class EntityManager;
class EntityGenerator;

class Helper
{
private:
public:
    /*
WinConsoleColors struct contains ANSI escape codes for
coloring console output on Windows.
*/
    struct ConsoleColors {
        const std::string reset = "\033[0m";
        const std::string red = "\033[31m";
        const std::string yellow = "\033[33m";
        const std::string white = "\033[37m";
        const std::string green = "\033[32m";
    } consoleColors;



    struct LogLevels {
        bool error = true;
        bool warning = true;
        bool info = true;
        bool debug = true;
        bool raw = true;
    } logLevels;

    enum class LogType {
        CORE,
        GENERATOR,
        GAME
    } logType;

    enum class LogLevel {
        _ERROR,
        WARNING,
        INFO,
        DEBUG,
        RAW
    } logLevel;

    Helper(/* args */);
    ~Helper();

    bool inGame = false;

    /**
    Function to log a raw message without any formatting(RAW) or color. basicly a wrapper for std::cout.
    */
    void log(std::string logMsg);
    void logError(std::string logMsg);
    void logWarning(std::string logMsg);
    void logInfo(std::string logMsg);
    void logDebug(std::string logMsg);
    /**
     Function takes a string message and a log level enum.
     It uses the log level to determine what formatting to use,
	 and whether to output the message based on current log 
     level settings. Log level settings
     are in the LogLevels struct.
    */
    void log(std::string logMsg, LogLevel _logLevel);
    void printArgs(int argc, const char *argv[]);

    void logAsGenerator(std::string message);
    void logAsGame(std::string message);

    std::filesystem::path logFile;
    std::filesystem::path serverLogFile;
    std::filesystem::path configFile;

    IOmanager* ioMan;
    inputManager* inputMan;
    mapGenerator* mapGen;
    EntityManager* entityMan;
	EntityGenerator* entityGen;


    bool canLog(LogLevel _logLevel)
    {
        switch (_logLevel) {
        case LogLevel::_ERROR:
            return logLevels.error;
        case LogLevel::WARNING:
            return logLevels.warning;
        case LogLevel::INFO:
            return logLevels.info;
        case LogLevel::DEBUG:
            return logLevels.debug;
        case LogLevel::RAW:
            return logLevels.raw;
        default:
            return false; // or handle the error appropriately
        }
    }

    //LogLevel getLogLevels() { return logLevel; }

};

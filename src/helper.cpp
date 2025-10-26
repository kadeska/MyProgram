#include "include/helper.hpp"

/**
 *  The color sequences are composed of sequences of numbers separated
       by semicolons. The most common codes are:
          ┌────┬───────────────────────┐
          │    │                       │
          │ 0  │ to restore default    │
          │    │ color                 │
          ├────┼───────────────────────┤
          │    │                       │
          │ 1  │ for brighter colors   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 4  │ for underlined text   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 5  │ for flashing text     │
          ├────┼───────────────────────┤-----
          │    │                       │foreground/text color
          │ 30 │ for black foreground  │
          ├────┼───────────────────────┤
          │    │                       │
          │ 31 │ for red foreground    │
          ├────┼───────────────────────┤
          │    │                       │
          │ 32 │ for green foreground  │
          ├────┼───────────────────────┤
          │    │                       │
          │ 33 │ for yellow (or brown) │
          │    │ foreground            │
          ├────┼───────────────────────┤
          │    │                       │
          │ 34 │ for blue foreground   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 35 │ for purple foreground │
          ├────┼───────────────────────┤
          │    │                       │
          │ 36 │ for cyan foreground   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 37 │ for white (or gray)   │
          │    │ foreground            │
          ├────┼───────────────────────┤-------------
          │    │                       │background
          │ 40 │ for black background  │
          ├────┼───────────────────────┤
          │    │                       │
          │ 41 │ for red background    │
          ├────┼───────────────────────┤
          │    │                       │
          │ 42 │ for green background  │
          ├────┼───────────────────────┤
          │    │                       │
          │ 43 │ for yellow (or brown) │
          │    │ background            │
          ├────┼───────────────────────┤
          │    │                       │
          │ 44 │ for blue background   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 45 │ for purple background │
          ├────┼───────────────────────┤
          │    │                       │
          │ 46 │ for cyan background   │
          ├────┼───────────────────────┤
          │    │                       │
          │ 47 │ for white (or gray)   │
          │    │ background            │
          └────┴───────────────────────┘

 */

Helper::Helper(/* args */)
{
    // std::cout << "helper constructor" << std::endl;
    //logDebug("Helper constructor");
}

Helper::~Helper()
{
    // std::cout << "helper destructor" << std::endl;
    logDebug("Helper destructor");
}

void Helper::log(std::string logMsg)
{
    //std::cout << "[Log]" << " " << logMsg << std::endl;
    log(logMsg, LogLevel::RAW);
}

void Helper::logError(std::string logMsg)
{
    //std::cout << "\033[31m" << "[Error]" << " " << logMsg << "\033[0m" << std::endl;
    log(logMsg, LogLevel::_ERROR);
}

void Helper::logWarning(std::string logMsg)
{
    //std::cout << "\033[33m" << "[Warning]" << " " << logMsg << "\033[0m" << std::endl;
    log(logMsg, LogLevel::WARNING);
}

void Helper::logInfo(std::string logMsg)
{
    //std::cout << "\033[37m" << "[Info]" << " " << logMsg << "\033[0m" << std::endl;
	log(logMsg, LogLevel::INFO);
}

void Helper::logDebug(std::string logMsg)
{
    //std::cout << "\033[32m" << "[Debug]" << " " << logMsg << "\033[0m" << std::endl;
    log(logMsg, LogLevel::DEBUG);
}

void Helper::log(std::string logMsg, LogLevel _logLevel)
{
    if (!canLog(_logLevel)) return; // Check if logging is enabled for this level

    std::string prefix;

    // Set up the prefix and color based on the log level
    switch (_logLevel) {
    case LogLevel::_ERROR:
        prefix = consoleColors.red + "[Error] " + consoleColors.reset;
        break;
    case LogLevel::WARNING:
        prefix = consoleColors.yellow + "[Warning] " + consoleColors.reset;
        break;
    case LogLevel::INFO:
        prefix = consoleColors.white + "[Info] " + consoleColors.reset;
        break;
    case LogLevel::DEBUG:
        prefix = consoleColors.green + "[Debug] " + consoleColors.reset;
        break;
    case LogLevel::RAW:
        std::cout << logMsg;
        //std::printf(logMsg.c_str());
        return;
    default:
        return; // Should not reach here
    }

    std::cout << prefix << logMsg << std::endl; // Log message with prefix
    if (ioMan != nullptr) 
    {
        ioMan->printToLogFile(prefix + logMsg); // Also log to file
    }
	
}

void Helper::printArgs(int argc, const char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        /* code */
        // std::cout << "Given arguments" << "[" << i <<  "]" << " : " << argv[i] << std::endl;
        log("Given arguments [" + std::to_string(i) +  "] : " + std::string(argv[i]));
    }
}


void Helper::logAsGenerator(std::string message) {
    logDebug("[EntityGenerator] " + message);
}

void Helper::logAsGame(std::string message) 
{
	logDebug("[Game] " + message);
}
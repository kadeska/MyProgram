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
    logDebug("Helper constructor");
}

Helper::~Helper()
{
    // std::cout << "helper destructor" << std::endl;
    logDebug("Helper destructor");
}

void Helper::log(std::string logMsg)
{
    //std::cout << "[Log]" << " " << logMsg << std::endl;
    logRaw("[Log] " + logMsg + '\n');
}

void Helper::logError(std::string logMsg)
{
    //std::cout << "\033[31m" << "[Error]" << " " << logMsg << "\033[0m" << std::endl;
    logRaw("\033[31m [Error] " + logMsg + "\033[0m \n", logLevel.error);
}

void Helper::logWarning(std::string logMsg)
{
    //std::cout << "\033[33m" << "[Warning]" << " " << logMsg << "\033[0m" << std::endl;
    logRaw("\033[33m [Warning] " + logMsg + "\033[0m \n", logLevel.warning);
}

void Helper::logInfo(std::string logMsg)
{
    //std::cout << "\033[37m" << "[Info]" << " " << logMsg << "\033[0m" << std::endl;
	logRaw("\033[37m [Info] " + logMsg + "\033[0m \n", logLevel.info);
}

void Helper::logDebug(std::string logMsg)
{
    //std::cout << "\033[32m" << "[Debug]" << " " << logMsg << "\033[0m" << std::endl;
    logRaw("\033[32m [Debug] " + logMsg + "\033[0m \n", logLevel.debug);
}

void Helper::logRaw(std::string logMsg, bool logLevel)
{
    if (logLevel) {
        if (!inGame) 
        {
            std::cout << logMsg;
        }
        return;
    }
    //std::cout << "skip \n";
    
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
#include "include/helper.hpp"

Helper::Helper(/* args */)
{
    std::cout << "helper constructor" << std::endl;
}

Helper::~Helper()
{
    std::cout << "helper destructor" << std::endl;
}

void Helper::log(std::string logMsg)
{
    std::cout << "[Log]" << " " << logMsg << std::endl;
}

void Helper::logError(std::string logMsg)
{
    std::cout << "[Error]" << " " << logMsg << std::endl;
}

void Helper::logWarning(std::string logMsg)
{
    std::cout << "[Warning]" << " " << logMsg << std::endl;
}

void Helper::logInfo(std::string logMsg)
{
    std::cout << "[Info]" << " " << logMsg << std::endl;
}

void Helper::logRaw(std::string logMsg)
{
    std::cout << logMsg << std::endl;
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
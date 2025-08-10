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
    std::cout << "[log]" << " " << logMsg << std::endl;
}
void Helper::printArgs(int argc, const char *argv[]){
    for (int i = 0; i < argc; i++)
    {
        /* code */
        // std::cout << "Given arguments" << "[" << i <<  "]" << " : " << argv[i] << std::endl;
        log("Given arguments [" + std::to_string(i) +  "] : " + std::string(argv[i]));
    }
}
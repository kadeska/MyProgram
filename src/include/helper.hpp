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
    void printArgs(int argc, const char *argv[]);
};



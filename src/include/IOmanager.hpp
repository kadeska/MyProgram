#pragma once

#include <iostream>
#include <fstream>
#include <string> 
#include <cstring>
#include <vector>

#include "commands.hpp"



const unsigned int MAX_ARGS = 1;

/**
 * Input/Output data
 * 
 */
struct IO_Data {
    /* data */
    //// char *argv[MAX_ARGS + 1];
    //std::vector<std::string> commandLineArgs;
    //int argc;
    //// std::string availableArgs[MAX_ARGS + 10];
    //std::vector<std::string> availableArgs;
};

struct givenArgument {
    std::string argument = "";
    bool isValid = false;
};

enum class FileWriteMode {
    Overwrite,
    Append
};

class Helper;

class IOmanager {
public:
    //IOmanager() = default;
    /**
     * IOmanager(int argc, char const *argv[])
     * Accepts the given arguments and checks if there are too many arguments,
     * then passes to the helper log function to output.
     * 
     * This function checks if the proper amount of arguments were passed, 
     * and if so then this function will initialize the handling of the given commands.
     * If the proper amount of arguments are not given then the program will halt.
     * If there are no arguments given then the program will run without arguments. 
     */
    IOmanager(int argc, const char* argv[], Helper& helper_ref);
    
    /**
	 * read a config file containing config options and return true if file reads succesfully.
     * 
     * */ 
    bool readFileContent(std::string filename);

    /**
     * This function will check if the given argument(s) are valid.
     * Available arguments for use are stored in a file, named 'AvailableArgs.txt'.
     * File will be read on each check, in case file gets updated during runtime.
     * This function returns a command enum that represents the argument given.
     * 
     */
    command check();

    int test();
    bool writeFileFromExePath(const std::filesystem::path& relativePath, const std::string& contents, FileWriteMode mode);
    std::filesystem::path getExecutableDirectory();

private:
    // std::vector<std::string> commandLineArgs;
    // std::vector<std::string> availableArgs;

    /**
     * This bool is a flag determining if the correct number of arguments have 
     * been passed and we are ready to parse the availableargs file.
     */
    bool ready = false;

    IO_Data data;
    givenArgument givenArg;
    std::vector<givenArgument> givenArgs;
    
    Helper& helper;
};


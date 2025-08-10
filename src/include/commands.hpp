#pragma once

#include <string>

/**
 * This is an enum representation 
 * of the available commands.
 */
enum command {
    eNull,
    eNofile,
    eServer,
    eClient,
    eTest
};

/**
 * Hash function for taking a argument/command
 * as string and converts it to an enum.
 */
command hashit (std::string const& inString);


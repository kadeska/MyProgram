#pragma once

#include <string>


enum command {
    eNull,
    eServer,
    eClient,
    eTest
};

command hashit (std::string const& inString);


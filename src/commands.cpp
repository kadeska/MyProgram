#include "include/commands.hpp"

command hashit (std::string const& inString) {
    if (inString == "--server") return eServer;
    if (inString == "--client") return eClient;
    if (inString == "--test") return eTest;

    return eNull;
}
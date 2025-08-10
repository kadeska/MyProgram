#include <iostream>

#include "include/commands.hpp"
#include "include/IOmanager.hpp"
#include "include/helper.hpp"

int main(int argc, char const *argv[])
{
    // Initialize helper class
    Helper helper;

    // print out the cpp version 
    // std::cout << __cplusplus << std::endl;
    helper.logDebug("CPP Version: " + std::to_string(__cplusplus));
    
    

    // Initialize IOmanager
    IOmanager io_manager(argc, argv, helper);

    switch (io_manager.check())
    {
    case eNull:
        // If the check results are eNull then fail
        helper.logError("IOManager check failed.");
        break;
    
    case eClient:
    helper.logDebug("IOManager check succeeded.");
        break;
    case eServer:
    helper.logDebug("IOManager check succeeded.");
        break;
    case eTest:
    helper.logDebug("IOManager check succeeded.");
        break;
    default:
        // this case would only acure if there was un uncought valid command. 
        // Such as if I added a command in the AvailableArgs file but didnt 
        // update this function to catch the command.
        helper.log("[ERROR] Uncought valid command. Please update switch case statement in main function to catch the command");
        break;
    }



    // // if the check passes
    // if (io_manager.check() != eNull) {
    //     helper.log("[INFO] IOManager check completed successfully.");
    // } else {
    //     helper.log("[ERROR] IOManager check failed.");
    // }

    // helper.printArgs(argc, argv);
    
    return 0;
}



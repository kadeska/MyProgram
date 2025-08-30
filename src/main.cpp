#include <iostream>

#include "include/commands.hpp"
#include "include/IOmanager.hpp"

#include "include/timer.hpp"
#include "include/client.hpp"
#include "include/server.hpp"

#include "include/helper.hpp"

// #define ASIO_STANDALONE
#include <asio.hpp>

Helper helper;

enum Role { UNKNOWN, SERVER, CLIENT };

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: MyProgram <server|client>\n";
        return 1;
    }

    std::string role_str = argv[1];
    Role role = UNKNOWN;
    if (role_str == "server") {
        helper.logInfo("Starting server...");
        role = SERVER;
    } else if (role_str == "client") {
        helper.logInfo("Starting client...");
        role = CLIENT;
    }

    try {
        asio::io_context io_context;

        if (role == SERVER) {
            TcpServer server(io_context, helper);
            server.run();
        } else if (role == CLIENT) {
            TcpClient client(io_context, SERVER_HOST, CLIENT_PORT);
            // client.run();
            client.run("hello server.\n");
        } else {
            // std::cerr << "Unknown role specified. Use 'server' or 'client'.\n";
            helper.logError("Unknown role specified. Use 'server' or 'client'.\n");
            return 1;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // helper.logError("Exception: " + std::to_string(e.what()));
        return 1;
    }

    return 0;
}


// OLD \/-------------------------------------------------\/

// int main(int argc, char const *argv[])
// {
//     // Initialize helper class
//     // Helper helper;

//     // print out the cpp version 
//     // std::cout << __cplusplus << std::endl;
//     helper.logDebug("CPP Version: " + std::to_string(__cplusplus));
    
    

//     // Initialize IOmanager
//     IOmanager io_manager(argc, argv, helper);

//     switch (io_manager.check())
//     {
//     case eNull:
//         // If the check results are eNull then fail
//         helper.logError("IOManager check failed.");
//         break;

//     case eNofile:
//         helper.logDebug("Working with no args file.");
//         break;
    
//     case eClient:
//     helper.logDebug("IOManager check succeeded.");
//     // start client
//     try {
//         asio::io_context io_context;
//         Client client(io_context);
//         client.start("localhost", "daytime");

//         // Example of writing to the server after connection is established
//         // This is a simplified approach. In a real app, you would
//         // trigger this after receiving a connected signal or in a separate thread.
//         // For this example, we just add a delay.
//         asio::steady_timer t(io_context, asio::chrono::seconds(2));
//         t.async_wait([&client](const asio::error_code& /*e*/) {
//             client.write("Hello from the client!");
//         });

//         io_context.run();
//     } catch (std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }
//     // client(helper);
//     // read(helper);
//     // writeToServer();
//         break;

//     case eServer:
//     helper.logDebug("IOManager check succeeded.");
//     // start server
//     try {
//         asio::io_context io_context;
//         Server server(io_context, 13);
//         io_context.run();
//     } catch (std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }
//     // writeToClient("hello world");
//         break;

//     case eTest:
//     helper.logDebug("IOManager check succeeded.");
//     foo_async();
//     // foo_sync();
//     // client(argc, argv);
//         break;

//     default:
//         // this case would only acure if there was un uncought valid command. 
//         // Such as if I added a command in the AvailableArgs file but didnt 
//         // update this function to catch the command.
//         helper.log("[ERROR] Uncought valid command. Please update switch case statement in main function to catch the command");
//         break;
//     }



//     // // if the check passes
//     // if (io_manager.check() != eNull) {
//     //     helper.log("[INFO] IOManager check completed successfully.");
//     // } else {
//     //     helper.log("[ERROR] IOManager check failed.");
//     // }

//     // helper.printArgs(argc, argv);
    
//     return 0;
// }



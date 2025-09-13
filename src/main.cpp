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

bool client(asio::io_context& io_context);
int waitForInput(Helper helper);

bool waitLoop = false;

enum Role { UNKNOWN, SERVER, CLIENT };

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: MyProgram <server|client>\n";
        waitForInput(helper);
		//foo_sync();
		
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
            // client.run();
            client(io_context);
        } else {
            // std::cerr << "Unknown role specified. Use 'server' or 'client'.\n";
            helper.logError("Unknown role specified. Use 'server' or 'client'. Entering default mode.\n");
            // 
            waitForInput(helper);
			//waitForInput(helper);
            return 1;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // helper.logError("Exception: " + std::to_string(e.what()));
        return 1;
    }

    return 0;
}

bool client(asio::io_context& io_context){
    std::cout << "testing1" << std::endl;

    TcpClient client(io_context, SERVER_HOST, CLIENT_PORT);
    
    client.waitForInput(helper);
    client.run("hello server.\n");
	
    return true;
}

int waitForInput(Helper helper)
{
    std::cout << "testing" << std::endl;

    helper.logInfo("waiting");
    if (waitLoop == false) {
        waitLoop = true;
        helper.logInfo("Entering wait loop. Type 'exit' to quit.");
    }
    while (waitLoop) {
        helper.logInfo("Please enter something > ");
        std::string entry;
        std::getline(std::cin, entry);
        helper.logInfo("You entered: " + entry);
    }


    return 0;
}

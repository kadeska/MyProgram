#include <iostream>
#include <filesystem>

#include "include/commands.hpp"
#include "include/IOmanager.hpp"

#include "include/timer.hpp"
#include "include/client.hpp"
#include "include/server.hpp"

#include "include/helper.hpp"
#include "include/inputManager.hpp"

// SDL3 window
//#include "include/window.hpp"


// #define ASIO_STANDALONE
#include <asio.hpp>

//#include <SDL3/SDL.h>
//#include <SDL_main.h>


Helper helper;


bool client(asio::io_context& io_context);

const std::filesystem::path logFile = "data/log.txt";
const std::filesystem::path configFile = "data/config.ini";

enum Role { UNKNOWN, SERVER, CLIENT };

//int main(int argc, char* argv[]) {
//    // Your previous main() code here
//    if(!SDL_Init(SDL_INIT_VIDEO)) {
//        helper.logInfo("SDL initialized successfully.");
//    } else {
//        helper.logError(std::string("SDL initialization failed: ") + SDL_GetError());
//        return 1;
//	}
//    return 0;
//}

int main(int argc, const char* argv[]) {

	IOmanager ioMan(argc, argv, helper);
    //ioMan.test();
	
    if (ioMan.writeFileFromExePath(logFile, "Log file created.\n", FileWriteMode::Overwrite)) {
        std::cout << "Successfully created data/log.txt" << std::endl;
    }
    if (ioMan.writeFileFromExePath(configFile, "setting=value\nversion=1.0", FileWriteMode::Overwrite)) {
        std::cout << "Successfully created data/config.ini" << std::endl;
    }
    ioMan.readFileContent(configFile.string());
    ioMan.readFileContent(logFile.string());
    if (argc < 2) {
        //std::cerr << "Usage: MyProgram <server|client>\n";
		helper.logError("Not enough or no arguments provided.");
		helper.logError("Usage: MyProgram <server|client>. Entering default mode.");
        //printPrompt(helper);
        waitForInput(helper);
		//foo_sync();
		
        return 1;
    }

    std::string role_str = argv[1];
    Role role = UNKNOWN;
    if (role_str == "server") {
        helper.logInfo("Starting server...");
        role = SERVER;
    } 
    if (role_str == "client") {
        helper.logInfo("Starting client...");
        role = CLIENT;
    }
    if (role_str == "game") {
        helper.logInfo("Starting game...");
        /*Window window;
        if (window.init("My SDL3 Window", 800, 600)) {
            window.mainLoop();
            window.cleanup();
        }*/
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

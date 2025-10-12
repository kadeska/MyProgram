#include <iostream>
#include <filesystem>

#include "include/commands.hpp"
#include "include/IOmanager.hpp"

#include "include/timer.hpp"
#include "include/client.hpp"
#include "include/server.hpp"

#include "include/helper.hpp"
#include "include/inputManager.hpp"
#include "include/mapGenerator.hpp"
#include "include/entityGenerator.hpp"
#include "include/entityManager.hpp"

#include "include/player.hpp"

// SDL3 window
//#include "include/window.hpp"


// #define ASIO_STANDALONE
#include <asio.hpp>

//#include <SDL3/SDL.h>
//#include <SDL_main.h>


Helper* helper;

enum Role { UNKNOWN, SERVER, CLIENT };



static int init(int argc, const char* argv[]) {
    // wrap with try catch or check for nullptr
    helper = new Helper();
    helper->ioMan = new IOmanager(argc, argv, *helper);
    helper->mapGen = new mapGenerator(helper->ioMan, helper);
    helper->inputMan = new inputManager(helper, helper->ioMan, helper->mapGen);
    helper->entityMan = new EntityManager(helper);
    helper->entityGen = new EntityGenerator(helper->ioMan, helper);


    // maybe move to a fileManager class later

    helper->logFile = "data/log.txt";
	helper->serverLogFile = "data/server_log.txt";
    helper->configFile = "data/config.ini";

    if (helper->ioMan->writeFileFromExePath(helper->logFile, "Log file created.\n", FileWriteMode::Overwrite)) {
        std::cout << "Successfully created data/log.txt" << std::endl;
    }
    if (helper->ioMan->writeFileFromExePath(helper->configFile, "setting=value\nversion=1.0", FileWriteMode::Overwrite)) {
        std::cout << "Successfully created data/config.ini" << std::endl;
    }
    helper->ioMan->readFileContent(helper->configFile.string());
    helper->ioMan->readFileContent(helper->logFile.string());

    return 0;
}

static bool client(asio::io_context& io_context) {
    std::cout << "testing1" << std::endl;

    TcpClient client(io_context, SERVER_HOST, CLIENT_PORT);

    //client.waitForInput(*helper);
    client.run("hello server.\n");

    return true;
}

static int processArgs(int argc, const char* argv[]) {
    // process args here

    std::string role_str = argv[1];
    Role role = UNKNOWN;
    if (role_str == "server") {
        helper->logInfo("Starting server...");
        role = SERVER;
    }
    if (role_str == "client") {
        helper->logInfo("Starting client...");
        role = CLIENT;
    }
    if (role_str == "game") {
        helper->logInfo("Starting game...");
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
        }
        else if (role == CLIENT) {
            // client.run();
            client(io_context);
        }
        else {
            // std::cerr << "Unknown role specified. Use 'server' or 'client'.\n";
            helper->logError("Unknown role specified. Use 'server' or 'client'. Entering default mode.\n");
            // 
            helper->inputMan->waitForInput();
            //waitForInput(helper);
            return 1;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // helper.logError("Exception: " + std::to_string(e.what()));
        return 1;
    }
    return 0;
}

// cleaned  up main function 
int main(int argc, const char* argv[]) {
    // initialize
    if (init(argc, argv)) {
        std::cerr << "Failed to initialize." << std::endl;
        return 1;
    }

    // test function
    //ioMan.test();


    auto playerEntity = helper->entityGen->generateEntity("Player 1", EntityTypes::PLAYER);
    helper->entityMan->addEntity(std::move(playerEntity));

    // Refactored for loop to use unique_ptr correctly
    for (int i = 0; i < 5; i++) {
        // 1. Call generateEntity, which now returns a unique_ptr
        auto enemyEntity = helper->entityGen->generateEntity("enemy " + std::to_string(i), EntityTypes::ENEMY);

        // 2. Add the entity to the manager by moving its ownership
        helper->entityMan->addEntity(std::move(enemyEntity));
    }

    // if no arguments provided, enter default mode(standby for input)
    if (argc < 2) {
        //std::cerr << "Usage: MyProgram <server|client>\n";
        helper->logError("Not enough or no arguments provided.");
        helper->logError("Usage: MyProgram <server|client>. Entering default 'standby' mode.");
        //printPrompt(helper);
        helper->inputMan->waitForInput();
        //foo_sync();

        return 1;
    }

    processArgs(argc, argv);
    return 0;
}
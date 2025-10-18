#include "inputManager.hpp"

#include "mapGenerator.hpp"
#include "helper.hpp"

#include "IOmanager.hpp"
#include "client.hpp"
#include "server.hpp"
#include "game.hpp"



bool waitLoop = false;
bool modeSelection = false;


void InputManager::initInputManager(Helper* _helper, IOmanager* _ioManager, MapGenerator* _mapGen)
{
    helper = _helper;
    ioManager = _ioManager;
	mapGen = _mapGen;
}


int InputManager::waitForInput()
{
    //std::cout << "Waiting for input..." << std::endl;
    helper->logInfo("Waiting for input... Type 'exit' to quit.");

    //helper.logInfo("waiting");
    if (waitLoop == false) {
        waitLoop = true;
        helper->logDebug("Entering wait loop.");
        printPrompt();
    }
    while (waitLoop) {
        helper->log("Please enter something > ", Helper::LogLevel::RAW);
        std::string entry;
        // Flush the output stream to ensure the prompt is displayed immediately
        std::cout << std::flush;
        // Use std::getline to read the entire line of user input, including spaces
        std::getline(std::cin, entry);
        if (!processInput(entry)) 
        {
            // go into mode selection.
            helper->logInfo("...");
			selectMode();
        }
        
    }


    return 0;
}



bool InputManager::processInput(std::string& input)
{
    // if (input == "") {}
    if (input == "exit") {
        helper->logInfo("Exiting wait loop.");
        waitLoop = false;
        return false;
    }
    if (input == "map") {
        //helper->logInfo("Generating random map...");
        // Generate and display a random map (for demonstration purposes, we'll just print a message)
		mapGen->generateMap(10, 10);
        //mapGen->printMap();
		return true;
    }
    if (input == "server") { 
        helper->logInfo("Launching server...");
        asio::io_context io_context;
        TcpServer server(io_context, helper);
        server.run();
    }
    if (input == "client") { 
        helper->logInfo("Launching client");
        asio::io_context io_context;
        TcpClient client(io_context, SERVER_HOST, CLIENT_PORT);
        client.run("hello server.\n");
    }
    if (input == "spawn-entity") {
        helper->logInfo("Spawning entity not implemented yet.");
		//entityMan->addEntity(entityGen->generateEntity("Player1", EntityTypes::PLAYER));
    }

	if (input == "game") { 
        helper->logInfo("Launching game...");
        /*Window window;
        if (window.init("My SDL3 Window", 800, 600)) {
            window.mainLoop();
            window.cleanup();
        }*/
		Game* game = new Game(helper, ioManager, this, helper->entityMan, helper->entityGen, mapGen);
        game->run();
    }

    else {
        helper->logInfo("You entered: " + input);
        return true;
    }

	return false;
}

int InputManager::printPrompt()
{
    helper->logInfo("______________________");
    helper->logInfo("Welcome to my program.");
    helper->logInfo("______________________");
    helper->logInfo("");
    helper->logInfo("To print a rendomly generated map enter 'map'.");
    helper->logInfo("To exit this enter 'exit'.");
    helper->logInfo("");
    return 0;
}

void InputManager::selectMode()
{
	modeSelection = true;
	helper->logInfo("Mode selection not fully implemented yet.");
    while (modeSelection) 
    {
        helper->log("Select mode (server/client/default) > ", Helper::LogLevel::RAW);
        std::string entry;
        // Flush the output stream to ensure the prompt is displayed immediately
        std::cout << std::flush;
        // Use std::getline to read the entire line of user input, including spaces
        std::getline(std::cin, entry);
        if (entry == "server") {
            helper->logInfo("Server mode selected. (Not implemented yet)");
            modeSelection = false;
            waitLoop = false;
        }
        if (entry == "client") {
            helper->logInfo("Client mode selected. (Not implemented yet)");
            modeSelection = false;
            waitLoop = false;
        }
        if (entry == "default") { helper->logInfo("Entering default mode."); waitForInput(); }
        if (entry == "exit") {
            helper->logInfo("Exiting mode selection.");
            modeSelection = false;
            waitLoop = false;
        }
        else {
            helper->logWarning("Invalid mode. Please enter 'server', 'client', 'default', or 'exit'.");
		}
    }

}
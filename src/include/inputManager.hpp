#pragma once

#include <iostream>
#include <string>



//#include "game.hpp"

// Forward declarations instead of includes
class Helper;
class IOmanager;
class MapGenerator;

class InputManager {
public:
    void initInputManager(Helper* _helper, IOmanager* _ioManager, MapGenerator* _mapGen);

    int waitForInput();

    bool update();
    void stopWaiting();
    bool isWaiting();
    bool processInput(std::string& input);
    int printPrompt();
    void selectMode();

    Helper* helper;
    IOmanager* ioManager;
    MapGenerator* mapGen;
};

#pragma once

#include <iostream>
#include <string>

// Forward declarations instead of includes
class Helper;
class IOmanager;
class mapGenerator;

class inputManager {
public:
    void initInputManager(Helper* _helper, IOmanager* _ioManager, mapGenerator* _mapGen);

    int waitForInput();

    bool update();
    void stopWaiting();
    bool isWaiting();
    bool processInput(std::string& input);
    int printPrompt();
    void selectMode();

    Helper* helper;
    IOmanager* ioManager;
    mapGenerator* mapGen;
};

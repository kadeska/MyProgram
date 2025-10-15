#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <windows.h> // Include for Win32 API functions

// Include all your other necessary header files here
#include "IOmanager.hpp"
#include "inputManager.hpp"
#include "EntityManager.hpp"
#include "EntityGenerator.hpp"
#include "helper.hpp"
#include "mapGenerator.hpp"

class Game {
private:
    // Pointers to your existing manager classes
    Helper* helper;
    IOmanager* ioMan;
    inputManager* inputMan;
    EntityManager* entityMan;
    EntityGenerator* entityGen;

    // Time variables for game loop
    float dt;
    int level;
    bool isRunning;
    const float fixed_delta_time;
    float time_accumulator;
    std::chrono::high_resolution_clock::time_point last_frame_time;
    const int max_updates_per_frame;

    // Double buffering variables for Windows Console
    std::vector<CHAR_INFO> backBuffer;
    COORD bufferSize;
    SMALL_RECT writeRegion;
    HANDLE hConsoleOutput;

    // Private helper methods
    void initConsoleBuffer(int width, int height);

public:
    Game(Helper* _helper, IOmanager* _ioMan, inputManager* _inputMan,
        EntityManager* _entityMan, EntityGenerator* _entityGen);
    ~Game();
    void update();
    void render();
    void run();
	void clear() { system("cls"); }
};

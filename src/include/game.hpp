#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h> // Include for Win32 API functions
#else
// linux specific includes
#include <ncurses.h>  // Include ncurses library
#endif



// Include all your other necessary header files here
#include "IOmanager.hpp"
#include "inputManager.hpp"
#include "entityManager.hpp"
#include "entityGenerator.hpp"
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


#ifdef _WIN32
    // Double buffering variables for Windows Console
    std::vector<CHAR_INFO> backBuffer;
    COORD bufferSize;
    SMALL_RECT writeRegion;
    HANDLE hConsoleOutput;
#else
    // Double buffering variables for Linux Console
    std::vector<char> backBuffer;
    int bufferWidth;
    int bufferHeight;
#endif


    

    // Private helper methods
    void initConsoleBuffer(int width, int height);

public:
    Game(Helper* _helper, IOmanager* _ioMan, inputManager* _inputMan,
        EntityManager* _entityMan, EntityGenerator* _entityGen);
    ~Game();
    void update();
    void render();
    void run();


#ifdef _WIN32
    //windows
    void clear() { system("cls"); }
#else
    // linux
	void clear() { system("clear"); }
#endif

	
};

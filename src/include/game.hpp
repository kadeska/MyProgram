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
    InputManager* inputMan;
    EntityManager* entityMan;
    EntityGenerator* entityGen;
	MapGenerator* mapGen;

    // Time variables for game loop
    float dt;
    int level;
    bool isRunning;
    const float fixed_delta_time;
    float time_accumulator;
    std::chrono::high_resolution_clock::time_point last_frame_time;
    const int max_updates_per_frame;


    // Rework buffer

//#ifdef _WIN32
//    // Double buffering variables for Windows Console
//    std::vector<CHAR_INFO> backBuffer;
//    COORD bufferSize;
//    SMALL_RECT writeRegion;
//    HANDLE hConsoleOutput;
//#else
//    // Double buffering variables for Linux Console
//    std::vector<char> backBuffer;
//    int bufferWidth;
//    int bufferHeight;
//#endif


    // New buffer
    //std::vector<std::vector<Tile>> mapBuffer;
    // buffer width and height
    //int bufferWidth, bufferHeight;
	int mapWidth, mapHeight;
    //Tile tile;


public:
    Game(int _mapWidth, int _mapHeight, Helper* _helper, IOmanager* _ioMan, InputManager* _inputMan,
        EntityManager* _entityMan, EntityGenerator* _entityGen, MapGenerator* _mapGen);
    ~Game();
    void initEntities();
    void initBuffer(int width, int height);
    void update();
    void render();
    void run();
    void checkInput();
    std::vector<int> getPlayerSpawnLocation();
	bool movePlayer(int _X, int _Y);


    // the previous tile type before the player moved
    char nextTileType;
    // the current tile type
    char curTileType;


#ifdef _WIN32
    //windows
    void clear() { system("cls"); }
#else
    // linux
	void clear() { system("clear"); }
#endif

	
};

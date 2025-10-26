#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <random>


#include "IOmanager.hpp"
#include "helper.hpp"
#include "Tile.hpp"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // For CHAR_INFO struct
#else
// linux specific includes
#endif




class MapGenerator {
private:
    IOmanager* ioMan;
    
    const std::string mapFile = "data/map.txt";
    // seed increases chances of solid tile. Higher seed = more solid tiles.
    // e.g. seed = 1 means all tiles are solid, seed = 10 means 1 in 10 tiles are empty.
    uint16_t seed = 2;
    uint16_t lootChance = 10; // percentage
    

    // Store the map internally as a 2D array of chars
    //std::vector<std::string> internalMap;

    // map dimensions
    int mapSizeX, mapSizeY;
	// map represented as 2D vector of Tile structs
    std::vector<std::vector<Tile>> map;
    // use a string for buffer.
    std::string mapBuffer;


    //struct _tile {
    //    char type = ' '; // e.g. '.', '#', 'L' (loot)
    //    bool isWalkable = false;
    //} tile;
    


public:
    Helper* helper;
    MapGenerator(IOmanager* _ioManager, Helper* _helper);
    ~MapGenerator();

    

    int playerSpawnY;
    int playerSpawnX;


    struct TileList {
        Tile solid = Tile('#', true);
        Tile empty = Tile('.', false);
        Tile loot = Tile('L', false);
        Tile player = Tile('P', true);
    } tileList;


    /**
     * @brief Generates a 2D map using a cellular automata algorithm.
     *
     * This function creates a new map with the specified dimensions,
     * initially populating it with random floor and wall tiles. It then
     * applies a smoothing algorithm to create more organic, cave-like
     * structures before preparing the final map for use. It also writes
     * a padded version of the map to a file during the initial generation.
     *
     * @param width The width of the map to generate.
     * @param height The height of the map to generate.
     */
    void generateMap(int width, int height);
    // Modified `printMap` to use a `CHAR_INFO` buffer

#ifdef _WIN32
    void assignMapToBuffer(std::vector<std::vector<Tile>>& buffer, int bufferWidth, int bufferHeight);
#else
// linux specific function
	void renderMapToBuffer(std::vector<char>& buffer, int bufferWidth, int bufferHeight);
#endif

    

    // Returns the tileType struct containing the tile characters.
    //_tileType getTileType() { return tileType; }


    char getTileType(int x, int y) 
    {
        if (x < 0 || y < 0 || x >= mapSizeX || y >= mapSizeY)
        {
            return ' ';
        }
        
        return map[x][y].tile; 
    }

    void setTile(int x, int y, Tile _tile) { map[y][x] = _tile; }
    std::vector<std::vector<Tile>> getMap();
    std::string getMapBuffer();
	// Can be used to set the map buffer, or clear it by default.
	void setMapBuffer(std::string _mapBuffer = "") { mapBuffer = _mapBuffer; }
    void sendMapToBuffer();
	int getMaxX() { return mapSizeX; }
    int getMaxY() { return mapSizeY; }


};

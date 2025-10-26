#include "include/mapGenerator.hpp"
#include <random>
#include <string>



// Added constants to make the code easier to configure.
const int INITIAL_WALL_CHANCE = 49; // Represents a % chance of being a wall.
const int SMOOTHING_ITERATIONS = 2;
const int SMOOTHING_THRESHOLD = 5; // A tile becomes a wall if it has 5 or more solid neighbors.

MapGenerator::MapGenerator(IOmanager* _ioManager, Helper* _helper)
    : ioMan(_ioManager), helper(_helper) {
    // Constructor logic if needed
	//map = std::vector<std::vector<Tile>>(10, std::vector<Tile>(10, Tile('.', false)));
}

MapGenerator::~MapGenerator() {
    // Destructor logic if needed
    //map = nullptr;
}

/**
 * @brief Generates a 2D map using a cellular automata algorithm.
 *
 * @param width The width of the map to generate.
 * @param height The height of the map to generate.
 */
void MapGenerator::generateMap(int width, int height) {
    mapSizeX = width;
    mapSizeY = height;


    // --- Setup for Randomization ---

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> initialDist(1, 100);

	// --- Initialize the internal map ---
    map = std::vector<std::vector<Tile>>(mapSizeX, std::vector<Tile>(mapSizeY, Tile('.', false)));


    //map = std::vector<std::vector<Tile>>();
    //map.resize(mapSizeX * mapSizeY);


    //internalMap.clear();
    //internalMap.resize(height, std::string(width, ' '));
    helper->logInfo("Generating map of size: " + std::to_string(width) + "x" + std::to_string(height));

    // --- STEP #01: Initial map randomization with borders ---
    helper->logInfo("STEP #01 : Initial Randomization");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                map[x][y] = tileList.solid;
            }
            else {
                map[y][x] = (initialDist(gen) <= INITIAL_WALL_CHANCE) ? tileList.solid : tileList.empty;
            }
        }
    }

    // --- STEP #02: Cellular automata smoothing ---
    helper->logInfo("STEP #02 : Smoothing Floor");
    for (int i = 0; i < SMOOTHING_ITERATIONS; ++i) {
        std::vector<std::vector<Tile>> tempMap = map; // Use a temporary map for each smoothing pass
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                int solidNeighbors = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;
                        if (tempMap[y + dy][x + dx].tile == tileList.solid.tile) {
                            solidNeighbors++;
                        }
                    }
                }
                if (solidNeighbors >= SMOOTHING_THRESHOLD) {
                    map[y][x] = tileList.solid;
                }
                else {
                    map[y][x] = tileList.empty;
                }
            }
        }
    }

    // --- STEP #03: Generating Loot ---
    helper->logInfo("STEP #03 : Generating Loot");
    std::uniform_int_distribution<> lootDist(1, 1000);
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            if (map[y][x].tile == tileList.empty.tile) {
                if (lootDist(gen) <= lootChance) {
                    map[y][x] = tileList.loot;
                }
            }
        }
    }

    // --- STEP #04: Spawning Player ---
    helper->logInfo("STEP #04 : Spawning Player");
    map[playerSpawnX][playerSpawnY] = tileList.player;
}


//#ifdef _WIN32
// Windows
/**
 * @brief Assigns the map to a buffer for display.
 *
 * @param buffer The buffer to render.
 * @param bufferWidth The width of the buffer.
 * @param bufferHeight The height of the buffer.
 */
void MapGenerator::assignMapToBuffer(std::vector<std::vector<Tile>>& buffer, int bufferWidth, int bufferHeight) 
{

    if (bufferWidth < mapSizeX || bufferHeight < mapSizeY) {
        throw std::out_of_range("Buffer dimensions are too small for the map.");
    }

    for (int x = 0; x < mapSizeX; x++) 
    {
        for (int y = 0; y < mapSizeY; y++) 
        {
            buffer[x][y] = map[x][y];
        }
    }
}
//#else
//// linux
///**
// * @brief Renders the map to a buffer for display.
// *
// * @param buffer The character buffer to render to.
// * @param bufferWidth The width of the buffer.
// * @param bufferHeight The height of the buffer.
// */
//void MapGenerator::renderMapToBuffer(std::vector<char>& buffer, int bufferWidth, int bufferHeight) {
//    int mapHeight = internalMap.size();
//    int mapWidth = internalMap.empty() ? 0 : internalMap[0].length();
//    for (int y = 0; y < bufferHeight; ++y) {
//        for (int x = 0; x < bufferWidth; ++x) {
//            if (y < mapHeight && x < mapWidth) {
//                buffer[y * bufferWidth + x] = internalMap[y][x];
//            }
//            else {
//                buffer[y * bufferWidth + x] = ' ';
//            }
//        }
//    }
//}
//#endif


std::string MapGenerator::getMapBuffer() { return mapBuffer; }

void MapGenerator::sendMapToBuffer()
{
    for (int x = 0; x < mapSizeX; x++) 
    {
        for (int y = 0; y < mapSizeY; y++) 
        {
            //char tileChar = map[x][y].tile;
            //helper->logAsGenerator("tileChar: " + tileChar);
            mapBuffer += map[x][y].tile;// tileChar;
        }
        mapBuffer += '\n';
    }
}

std::vector<std::vector<Tile>> MapGenerator::getMap() { return map; }

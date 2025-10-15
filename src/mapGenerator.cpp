#include "include/mapGenerator.hpp"

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h> // For CHAR_INFO struct



mapGenerator::mapGenerator(IOmanager* _ioManager, Helper* _helper)
    : ioMan(_ioManager), helper(_helper)
{
}

mapGenerator::~mapGenerator()
{
}

/**
 * @brief Generates a 2D map using a cellular automata algorithm.
 *
 * This function creates a new map with the specified dimensions,
 * initially populating it with random floor and wall tiles. It then
 * applies a smoothing algorithm to create more organic, cave-like
 * structures before preparing the final map for use.
 *
 * @param width The width of the map to generate.
 * @param height The height of the map to generate.
 */
void mapGenerator::generateMap(int width, int height)
{
    // Create a random device and generator (ideally, these should be class members for efficiency)
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, seed - 1);

    // Clear any previously generated map data before starting a new one.
    internalMap.clear();

    helper->logInfo("Generating map of size " + std::to_string(width) + "x" + std::to_string(height));

    // --- STEP #01: Initial map randomization ---
    helper->logInfo("STEP #01 : Generating Floor");

    // Use a temporary string to hold the un-padded map data, including newlines.
    // This is used for the cellular automata smoothing logic.
    std::string tempMap;

    // Iterate through each cell of the map to randomly assign tiles.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Randomly choose between an 'empty' tile ('.') and a 'solid' tile ('#').
            // The 'seed' variable controls the probability of a tile being solid.
            //char tile = (rand() % seed == 0) ? getTileType().empty : getTileType().solid;
            

            char tile = (dist(gen) == 0) ? getTileType().empty : getTileType().solid;
			// Introduce loot tiles ('L') based on the lootChance percentage.
            if (tile == getTileType().empty) {
                std::uniform_int_distribution<> lootDist(1, 100);
                if (lootDist(gen) <= lootChance) {
                    tile = getTileType().loot;
                }
			}

            tempMap += tile;
        }
        tempMap += '\n'; // Add newline to tempMap for correct indexing later.
    }

    // --- STEP #02: Cellular automata smoothing ---
    helper->logInfo("STEP #02 : Smoothing Floor");

    // Initialize the new map as a copy of the temporary one,
    // which contains the raw tile data plus newlines for each row.
    std::string newMap = tempMap;

    // The smoothing algorithm only needs to check inner tiles,
    // so we skip the borders (1 to height-2 and 1 to width-2).
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int solidNeighbors = 0;

            // Check the 8 surrounding neighbors in the un-padded tempMap.
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue; // Skip the tile itself.

                    // Calculate the index in the 1D string, accounting for the newline character at the end of each row.
                    size_t neighborIndex = (y + dy) * (width + 1) + (x + dx);

                    if (tempMap[neighborIndex] == getTileType().solid) {
                        solidNeighbors++;
                    }
                }
            }

            // Determine the current tile's index in the 1D string, accounting for newlines.
            size_t currentIndex = y * (width + 1) + x;

            // Apply the smoothing rule: if 5 or more neighbors are solid, the tile becomes solid.
            if (solidNeighbors >= 4) {
                newMap[currentIndex] = getTileType().empty;
            }
            else if (solidNeighbors >= 5) {
                newMap[currentIndex] = getTileType().loot;
            }
            else {
                newMap[currentIndex] = getTileType().solid;
            }
        }
    }

	

    

    // --- Placeholder for remaining steps ---
    helper->logInfo("STEP #03 : Generating Loot");
    helper->logInfo("STEP #04 : Spawning Player");

    // Set player start position to top-left corner (0,0) for now.
	// -------------------------------------------
    newMap[0] = getTileType().player;

    // --- Final step: Format the final map data and store ---
    internalMap.resize(height);
    for (int y = 0; y < height; ++y) {
        internalMap[y] = newMap.substr(y * (width + 1), width);
    }
}

void mapGenerator::renderMapToBuffer(std::vector<CHAR_INFO>& buffer, int bufferWidth, int bufferHeight)
{
    // Ensure the map fits within the buffer
    int mapHeight = internalMap.size();
    int mapWidth = internalMap.empty() ? 0 : internalMap[0].length();

    for (int y = 0; y < bufferHeight; ++y) {
        for (int x = 0; x < bufferWidth; ++x) {
            CHAR_INFO& cell = buffer[y * bufferWidth + x];
            if (y < mapHeight && x < mapWidth) {
                cell.Char.AsciiChar = internalMap[y][x];
                cell.Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            }
            else {
                cell.Char.AsciiChar = ' ';
                cell.Attributes = FOREGROUND_GREEN;
            }
        }
    }
}

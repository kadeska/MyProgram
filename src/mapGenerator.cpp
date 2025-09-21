#include "include/mapGenerator.hpp"

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
 * structures before preparing the final map for use. It also writes
 * a padded version of the map to a file during the initial generation.
 *
 * @param width The width of the map to generate.
 * @param height The height of the map to generate.
 */
void mapGenerator::generateMap(int width, int height)
{
    // Clear any previously generated map data before starting a new one.
    currentMap.clear();

    helper->logInfo("Generating map of size " + std::to_string(width) + "x" + std::to_string(height));
    helper->logInfo("Map will be saved to: " + mapFile);
    helper->logInfo("");

    // --- STEP #01: Initial map randomization ---
    helper->logInfo("STEP #01 : Generating Floor");

    // Use a temporary string to hold the un-padded map data, including newlines.
    // This is used for the cellular automata smoothing logic.
    std::string tempMap;

    // Overwrite the file with an empty string to start fresh.
    ioMan->writeFileFromExePath(mapFile, "", FileWriteMode::Overwrite);

    // Iterate through each cell of the map to randomly assign tiles.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Randomly choose between an 'empty' tile ('.') and a 'solid' tile ('#').
            // The 'seed' variable controls the probability of a tile being solid.
            char tile = (rand() % seed == 0) ? getTileType().empty : getTileType().solid;
            tempMap += tile;

            // Write a padded version (tile followed by a space) to the file.
            ioMan->writeFileFromExePath(mapFile, std::string(1, tile) + " ", FileWriteMode::Append);
            std::cout << tile << ' ';
        }
        tempMap += '\n'; // Add newline to tempMap for correct indexing later.
        ioMan->writeFileFromExePath(mapFile, "\n", FileWriteMode::Append);
        std::cout << std::endl;
    }

    //helper->logDebug("Initial Map Data (un-padded):\n" + tempMap);

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
            if (solidNeighbors >= 5) {
                newMap[currentIndex] = getTileType().solid;
            }
            else {
                newMap[currentIndex] = getTileType().empty;
            }
        }
    }

    // --- STEP #03: Format the final map data ---
    currentMap.clear();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Read from the smoothed map and add a space for visual padding.
            currentMap += newMap[y * (width + 1) + x];
            currentMap += ' ';
        }
        currentMap += '\n';
    }

    //helper->logDebug("Current Map Data:\n" + currentMap);

    // --- Placeholder for remaining steps ---
    helper->logInfo("STEP #03 : Generating Loot");
    //helper->logDebug("Current Map Data:\n" + currentMap);
    helper->logInfo("STEP #04 : Spawning Player");
}

void mapGenerator::printMap()
{
    helper->logDebug("Current Map Data:\n" + currentMap);
}

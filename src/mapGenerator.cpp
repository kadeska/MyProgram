#include "include/mapGenerator.hpp"

mapGenerator::mapGenerator(IOmanager* _ioManager, Helper* _helper)
	: ioMan(_ioManager), helper(_helper)
{
}

mapGenerator::~mapGenerator()
{
}

void mapGenerator::generateMap(int width, int height)
{
    // Clear current map data
    currentMap.clear();

    helper->logInfo("Generating map of size " + std::to_string(width) + "x" + std::to_string(height));
    helper->logInfo("Map will be saved to: " + mapFile);
    helper->logInfo("");
    helper->logInfo("STEP #01 : Generating Floor");

    // Use a temporary string to hold the un-padded map data, including newlines
    std::string tempMap;

    ioMan->writeFileFromExePath(mapFile, "", FileWriteMode::Overwrite);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Randomly choose between '.' and '#'. Seed increases chances of '#'
            char tile = (rand() % seed == 0) ? getTileType().empty : getTileType().solid;
            tempMap += tile;
            ioMan->writeFileFromExePath(mapFile, std::string(1, tile) + " ", FileWriteMode::Append); // Write padded version to file
            std::cout << tile << ' ';
        }
        tempMap += '\n'; // Add newline to tempMap
        ioMan->writeFileFromExePath(mapFile, "\n", FileWriteMode::Append);
        std::cout << std::endl;
    }

    helper->logDebug("Initial Map Data (un-padded):\n" + tempMap);

    helper->logInfo("STEP #02 : Smoothing Floor");

    // Initialize newMap as a copy of tempMap, which already includes borders and newlines
    std::string newMap = tempMap;

    // The smoothing loop should only iterate over the inner tiles
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int solidNeighbors = 0;

            // Check 8 neighbors in the un-padded tempMap
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;

                    // Correct index calculation for map with newlines
                    size_t neighborIndex = (y + dy) * (width + 1) + (x + dx);

                    if (tempMap[neighborIndex] == getTileType().solid) {
                        solidNeighbors++;
                    }
                }
            }

            // Correct index calculation for map with newlines
            size_t currentIndex = y * (width + 1) + x;

            if (solidNeighbors >= 5) {
                newMap[currentIndex] = getTileType().solid;
            }
            else {
                newMap[currentIndex] = getTileType().empty;
            }
        }
    }

    // Now, format the final smoothed map with spaces for display/logging
    currentMap.clear();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            currentMap += newMap[y * (width + 1) + x];
            currentMap += ' ';
        }
        // Add newline
        currentMap += '\n';
    }

    helper->logDebug("Current Map Data:\n" + currentMap);
    helper->logInfo("STEP #03 : Generating Loot");
    helper->logDebug("Current Map Data:\n" + currentMap);
    helper->logInfo("STEP #04 : Spawning Player");
}

void mapGenerator::printMap()
{
}

#include "include/mapGenerator.hpp"

mapGenerator::mapGenerator(IOmanager* ioManager)
    : ioMan(ioManager)
{
}

mapGenerator::~mapGenerator()
{
}

void mapGenerator::generateMap(int width, int height)
{
    ioMan->writeFileFromExePath(mapFile, "", FileWriteMode::Overwrite);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Randomly choose between '.' and '#'. Seed increases chances of '#'
            char tile = (rand() % seed == 0) ? getTileType().empty : getTileType().solid;
            // write to a file
            ioMan->writeFileFromExePath(mapFile, std::string(1, tile + " "), FileWriteMode::Append);

            std::cout << tile << ' ';
        }
        std::cout << std::endl;
        ioMan->writeFileFromExePath(mapFile, "\n", FileWriteMode::Append);
    }
}

void mapGenerator::printMap()
{
}

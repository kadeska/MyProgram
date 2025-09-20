#pragma once
#include <iostream>
#include <string>
#include <filesystem>

#include "IOmanager.hpp"
#include "helper.hpp"


class mapGenerator {
    private:
		IOmanager* ioMan;
		Helper* helper;
		const std::string mapFile = "data/map.txt";
		// seed increases chances of solid tile. Higher seed = more solid tiles.
		// e.g. seed = 1 means all tiles are solid, seed = 10 means 1 in 10 tiles are empty.
		uint16_t seed = 4;
		uint16_t lootChance = 10; // percentage

		std::string currentMap = "";

		struct _tile {
			char type = ' '; // e.g. '.', '#', 'L' (loot)
			bool isWalkable = false;
		}tile;
		struct _tileType {
			char solid = '#';
			char empty = '.';
			char loot = 'L';
			char player = 'P';
		}tileType;


	public:
	mapGenerator(IOmanager* _ioManager, Helper* _helper);
	~mapGenerator();
	void generateMap(int width, int height);
	void printMap();

	// Returns the tileType struct containing the tile characters.
	_tileType getTileType() { return tileType; }
};
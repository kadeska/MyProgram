#pragma once


// Usage: Tile(char _tile, bool _isSolid)
// A struct representing a tile in the game
//contains data such as the character representing 
// the tile, and whether the tile is solid (impassable) or not.
// Has a constructor for easy initialization.
//
// In the future, additional properties can be added to this struct.
// I may add properties such as "isDestructible", "isInteractive",
// "containsItem", etc., depending on game requirements.
struct Tile {
	// the character that is used to display the tile
    char tile;
	// whether the tile is solid (impassable) or not
    bool isSolid;

	// Initializer constructor
    Tile(char _tile, bool _isSolid) : tile(_tile), isSolid(_isSolid) {}
};
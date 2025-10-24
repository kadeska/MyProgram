#pragma once

struct Tile {
    char tile;
    bool isSolid;

    Tile(char _tile, bool _isSolid) : tile(_tile), isSolid(_isSolid) {}
};
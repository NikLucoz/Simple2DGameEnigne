#pragma once

#include <string>

#include "engine/assets/tilemap/Tilemap.h"

class TileMapLoader
{
public:
    static TileMap load(const std::string& filePath);
};
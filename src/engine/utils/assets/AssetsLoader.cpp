#include "AssetsLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "engine/assets/Assets.h"

void AssetsLoader::loadAssetsFromFile(Assets &assets, const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open asset file: " + filePath);
    }

    std::string line = "";
    while (std::getline(file, line)) {
        auto tokens = splitBySpace(line);
        if (tokens.empty()) {
            continue;
        }

        const std::string& assetType = tokens[0];
        const std::string& assetName = tokens[1];
        const std::string& assetPath = tokens[2];

        if (assetType == "Texture") {
            assets.addTexture(assetName, assetPath);
        } else if (assetType == "Sound") {
            assets.addSound(assetName, assetPath);
        } else if (assetType == "Animation") {
            // TODO: Need to read additional tokens for animation frame count and animation speed
            // TODO: assets.addAnimation(assetName, animation);
        } else if (assetType == "Font") {
            assets.addFont(assetName, assetPath);
        } else {
            std::cerr << "Unknown asset type: " << assetType << std::endl;
        }
    }

    file.close();
}

std::vector<std::string> AssetsLoader::splitBySpace(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}



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
        if (line._Starts_with("//") || line.empty()) continue;

        auto tokens = splitBySpace(line);
        if (tokens.empty() || tokens[0][0] == '#') {
            continue;
        }

        const size_t requiredTokens = tokens[0] == "Animation" ? 5 : 3;
        if (tokens.size() < requiredTokens)
        {
            std::cerr << "Invalid asset definition: " << line << std::endl;
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
            const std::string& animationFrames = tokens[3];
            const std::string& animationSpeed = tokens[4];
            const std::string& animationIsLoopable = tokens[5];

            bool bIsLoopable = animationIsLoopable == "true" ? true : false;
            Animation animation(assetName, assets.getTexture(assetPath), std::stoi(animationFrames), std::stoi(animationSpeed), bIsLoopable);
            assets.addAnimation(assetName, animation);
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



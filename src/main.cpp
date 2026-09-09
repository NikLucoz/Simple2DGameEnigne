#include "main.h"
#include <iostream>
#include "engine/GameEngine.h"

int main() {
    try {
        GameEngine game_engine(1280, 720, "Game Engine");
        game_engine.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

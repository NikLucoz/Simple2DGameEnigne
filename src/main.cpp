#include "main.h"
#include "engine/Engine.h"
#include <iostream>

int main() {
    try {
        GameEngine engine(1024, 768, "Game Engine");
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#include <iostream>
#include "engine/GameEngine.h"
#include "engine/scenes/MainMenuScene.h"
#include "engine/scenes/ScenePlay.h"

int main() {
    try {
        GameEngine game_engine(1280, 720, "Game Engine");
        game_engine.init();
        game_engine.registerScene<MainMenuScene>("main_menu_scene");
        game_engine.registerScene<ScenePlay>("gameplay_scene", 1.0f);
        game_engine.changeScene("gameplay_scene");
        game_engine.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

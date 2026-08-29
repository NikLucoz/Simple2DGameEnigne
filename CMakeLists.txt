cmake_minimum_required(VERSION 3.16)
project(SFMLGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Define Output Directory Early ---
set(GAME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")

# --- Dependencies (resolved via vcpkg toolchain) ---
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

# --- Sources ---
set(SOURCES
        src/main.cpp
        src/main.h
        src/engine/Engine.cpp
        src/engine/Engine.h
        src/engine/entities/Entity.cpp
        src/engine/entities/Entity.h
        src/engine/entities/EntityManager.cpp
        src/engine/entities/EntityManager.h
        src/engine/components/Component.h
        src/engine/components/CTransform.h
        src/engine/utils/math/Vector2.cpp
        src/engine/utils/math/Vector2.h
        src/engine/utils/debug_ui/DebugUI.cpp
        src/engine/utils/debug_ui/DebugUI.h
)

# --- Target ---
add_executable(game_engine ${SOURCES})

target_include_directories(game_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(game_engine PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        ImGui-SFML::ImGui-SFML
)

# --- Output ---
set_target_properties(game_engine PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${GAME_OUTPUT_DIR}"
)

# --- Assets ---
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/assets/fonts DESTINATION ${GAME_OUTPUT_DIR})